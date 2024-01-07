namespace MACE::Env {

template<typename ACLI>
MPIEnv::MPIEnv(int argc, char* argv[], ACLI&& cli, VL verboseLevel, bool printWelcomeMessage) :
    BasicEnv{argc, argv, cli, verboseLevel, false},
    PassiveSingleton<MPIEnv>{},
    fCommWorldRank{
        [&argc, &argv] {
            // Initialize MPI
            MPI_Init(&argc,  // argc
                     &argv); // argv
            // Initialize rank in the world communicator
            int rank;
            MPI_Comm_rank(MPI_COMM_WORLD, // comm
                          &rank);         // rank
            return rank;
        }()},
    fCommWorldSize{
        [] {
            // Initialize size of the world communicator
            int size;
            MPI_Comm_size(MPI_COMM_WORLD, // comm
                          &size);         // size
            return size;
        }()},
    fCluster{
        [this] {
            using NameFixedString = FixedString<MPI_MAX_PROCESSOR_NAME>;
            // Member fCluster to be initialized
            std::remove_cv_t<decltype(fCluster)> cluster;
            // Each process get its processor name
            NameFixedString nodeNameSend;
            int nameLength;
            MPI_Get_processor_name(nodeNameSend.Data(), // name
                                   &nameLength);        // resultlen
            // Master collects processor names
            std::vector<NameFixedString> nodeNamesRecv;
            if (OnCommWorldMaster()) { nodeNamesRecv.resize(fCommWorldSize); }
            MPI_Request gatherNodeNamesRequest;
            MPI_Igather(nodeNameSend.CString(),        // sendbuf
                        NameFixedString::Occupation(), // sendcount
                        MPI_CHAR,                      // sendtype
                        nodeNamesRecv.data(),          // recvbuf
                        NameFixedString::Occupation(), // recvcount
                        MPI_CHAR,                      // recvtype
                        0,                             // root
                        MPI_COMM_WORLD,                // comm
                        &gatherNodeNamesRequest);      // request
            // Processor name list
            std::vector<int> nodeIDSend;
            int nodeIDRecv;
            int nodeCount;
            struct NodeInfoForMPI {
                int size;
                NameFixedString name;
            };
            constexpr int blockLengthOfNodeInfoForMPI[]{1, NameFixedString::Occupation()};
            const MPI_Aint displacementOfNodeInfoForMPI[]{offsetof(NodeInfoForMPI, size), offsetof(NodeInfoForMPI, name)};
            const MPI_Datatype typeOfNodeInfoForMPI[]{MPI_INT, MPI_CHAR};
            MPI_Datatype nodeInfoForMPI;
            MPI_Type_create_struct(2,                            // count
                                   blockLengthOfNodeInfoForMPI,  // array_of_block_lengths
                                   displacementOfNodeInfoForMPI, // array_of_displacements
                                   typeOfNodeInfoForMPI,         // array_of_types
                                   &nodeInfoForMPI);             // newtype
            MPI_Type_commit(&nodeInfoForMPI);
            MPI_Wait(&gatherNodeNamesRequest, // request
                     MPI_STATUS_IGNORE);      // status
            // Master find all unique processor names and assign node ID and count
            std::vector<NodeInfoForMPI> nodeList;
            if (OnCommWorldMaster()) {
                // key: node name, mapped: rank
                std::multimap<const NameFixedString&, int> nodeMap;
                for (int rank{};
                     auto&& name : std::as_const(nodeNamesRecv)) {
                    nodeMap.emplace(name, rank++);
                }

                std::vector<std::pair<std::vector<int>, const NameFixedString*>> rankNode;
                auto currentNodeName{&nodeMap.begin()->first};
                rankNode.push_back({{}, currentNodeName});
                for (auto&& [nodeName, rank] : std::as_const(nodeMap)) {
                    if (nodeName != *currentNodeName) {
                        currentNodeName = &nodeName;
                        rankNode.push_back({{}, currentNodeName});
                    }
                    rankNode.back().first.emplace_back(rank);
                }
                std::ranges::sort(rankNode);

                nodeIDSend.resize(fCommWorldSize);
                for (int nodeID{};
                     auto&& [rankList, nodeName] : std::as_const(rankNode)) {
                    nodeList.push_back({static_cast<int>(rankList.size()), *nodeName});
                    for (auto&& rank : rankList) {
                        nodeIDSend.at(rank) = nodeID;
                    }
                    ++nodeID;
                }
                nodeCount = ssize(rankNode);
            }
            // Scatter node ID
            MPI_Request scatterNodeIDRequest;
            MPI_Iscatter(nodeIDSend.data(),      // sendbuf
                         1,                      // sendcount
                         MPI_INT,                // sendtype
                         &nodeIDRecv,            // recvbuf
                         1,                      // recvcount
                         MPI_INT,                // recvtype
                         0,                      // root
                         MPI_COMM_WORLD,         // comm
                         &scatterNodeIDRequest); // request
            // Broadcast node count
            MPI_Bcast(&nodeCount,      // buffer
                      1,               // count
                      MPI_INT,         // datatype
                      0,               // root
                      MPI_COMM_WORLD); // comm
            // Master send unique node name list
            if (OnCommWorldWorker()) { nodeList.resize(nodeCount); }
            MPI_Bcast(nodeList.data(), // buffer
                      nodeList.size(), // count
                      nodeInfoForMPI,  // datatype
                      0,               // root
                      MPI_COMM_WORLD); // comm
            MPI_Type_free(&nodeInfoForMPI);
            // Assign to the list, convert node names to std::string
            cluster.node.reserve(nodeCount);
            for (auto&& [size, name] : std::as_const(nodeList)) {
                cluster.node.push_back({size, name});
                cluster.node.back().name.shrink_to_fit();
            }
            cluster.node.shrink_to_fit();
            // Assign local processor ID
            MPI_Wait(&scatterNodeIDRequest, // request
                     MPI_STATUS_IGNORE);    // status
            cluster.local = nodeIDRecv;
            // Return the cluster info
            return cluster;
        }()},
    fCommNode{
        [this] {
            MPI_Comm comm;
            // Constructs shared communicator
            MPI_Comm_split(MPI_COMM_WORLD, // comm
                           fCluster.local, // color
                           0,              // key
                           &comm);         // newcomm
            return comm;
        }()},
    fCommNodeRank{
        [this] {
            int rank;
            // Initialize rank ID in the local communicator
            MPI_Comm_rank(fCommNode, // comm
                          &rank);    // rank
            return rank;
        }()},
    fCommNodeSize{
        [this] {
            int size;
            // Initialize size of the local communicator
            MPI_Comm_size(fCommNode, // comm
                          &size);    // size
            return size;
        }()} {
    // Disable ROOT implicit multi-threading
    if (ROOT::IsImplicitMTEnabled()) {
        ROOT::DisableImplicitMT();
    }
    // Print startup message
    if (printWelcomeMessage and OnCommWorldMaster()) {
        PrintWelcomeMessageSplitLine();
        PrintWelcomeMessageBody(argc, argv);
        PrintWelcomeMessageSplitLine();
    }
}

} // namespace MACE::Env
