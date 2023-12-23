namespace MACE::Env {

template<typename ACLI>
MPIEnv::MPIEnv(int argc, char* argv[], ACLI&& cli, VL verboseLevel, bool printWelcomeMessage) :
    BasicEnv{argc, argv, cli, verboseLevel, false},
    PassiveSingleton<MPIEnv>{},
    fCommWorldRank{
        [&argc, &argv] {
            // Initialize MPI
            MPI_Init(&argc, &argv);
            // Initialize rank ID in the world communicator
            int rank;
            MPI_Comm_rank(MPI_COMM_WORLD, &rank);
            return rank;
        }()},
    fCommWorldSize{
        [] {
            // Initialize size of the world communicator
            int size;
            MPI_Comm_size(MPI_COMM_WORLD, &size);
            return size;
        }()},
    fCluster{
        [this] {
            using NameFixedString = FixedString<MPI_MAX_PROCESSOR_NAME>;
            // Member fCluster to be initialized
            std::remove_cv_t<decltype(fCluster)> cluster;
            // Each rank get its processor name
            NameFixedString nodeNameSend;
            int nameLength;
            MPI_Get_processor_name(nodeNameSend.Data(),
                                   &nameLength);
            // Master collects processor names
            std::vector<NameFixedString> nodeNamesRecv;
            if (AtCommWorldMaster()) { nodeNamesRecv.resize(fCommWorldSize); }
            MPI_Request gatherNodeNamesRequest;
            MPI_Igather(nodeNameSend.CString(),
                        NameFixedString::Occupation(),
                        MPI_CHAR,
                        nodeNamesRecv.data(),
                        NameFixedString::Occupation(),
                        MPI_CHAR,
                        0,
                        MPI_COMM_WORLD,
                        &gatherNodeNamesRequest);
            // Processor name list
            std::vector<stdx::array2i> nodeIDAndCountSend;
            stdx::array2i nodeIDAndCountRecv;
            struct NodeInfoForMPI {
                int size;
                NameFixedString name;
            };
            constexpr int blockLengthOfNodeInfoForMPI[]{1, NameFixedString::Occupation()};
            const MPI_Aint displacementOfNodeInfoForMPI[]{offsetof(NodeInfoForMPI, size), offsetof(NodeInfoForMPI, name)};
            const MPI_Datatype typeOfNodeInfoForMPI[]{MPI_INT, MPI_CHAR};
            MPI_Datatype nodeInfoForMPI;
            MPI_Type_create_struct(2,
                                   blockLengthOfNodeInfoForMPI,
                                   displacementOfNodeInfoForMPI,
                                   typeOfNodeInfoForMPI,
                                   &nodeInfoForMPI);
            MPI_Type_commit(&nodeInfoForMPI);
            std::vector<NodeInfoForMPI> nodeList;
            // Master find all unique processor names and assign node ID and count
            MPI_Wait(&gatherNodeNamesRequest,
                     MPI_STATUS_IGNORE);
            if (AtCommWorldMaster()) {
                nodeIDAndCountSend.reserve(fCommWorldSize);
                nodeList.reserve(fCommWorldSize);
                // Find unique name and assign node ID
                auto currentNodeID = 0;
                auto currentNodeName = std::as_const(nodeNamesRecv).data();
                for (auto&& name : std::as_const(nodeNamesRecv)) {
                    if (name != *currentNodeName) {
                        nodeList.push_back({static_cast<int>(std::distance(currentNodeName, &name)),
                                            *currentNodeName});
                        ++currentNodeID;
                        currentNodeName = &name;
                    }
                    nodeIDAndCountSend.push_back({currentNodeID, -1});
                }
                nodeList.push_back({static_cast<int>(std::distance(currentNodeName, std::to_address(nodeNamesRecv.cend()))),
                                    *currentNodeName});
                // Assign node count
                for (const int nodeCount = nodeList.size();
                     auto&& [_, nodeCountSend] : nodeIDAndCountSend) {
                    nodeCountSend = nodeCount;
                }
            }
            // Send node ID and count
            MPI_Scatter(std::as_const(nodeIDAndCountSend).data(),
                        1,
                        MPI_2INT,
                        nodeIDAndCountRecv.data(),
                        1,
                        MPI_2INT,
                        0,
                        MPI_COMM_WORLD);
            auto&& [nodeID, nodeCount] = nodeIDAndCountRecv;
            // Assign local processor ID
            cluster.local = nodeID;
            // Master send unique node name list
            if (AtCommWorldWorker()) { nodeList.resize(nodeCount); }
            MPI_Bcast(nodeList.data(),
                      nodeList.size(),
                      nodeInfoForMPI,
                      0,
                      MPI_COMM_WORLD);
            MPI_Type_free(&nodeInfoForMPI);
            // Assign to the list, convert node names to std::string
            cluster.node.reserve(nodeCount);
            for (auto&& [size, name] : std::as_const(nodeList)) {
                cluster.node.push_back({size, name});
                cluster.node.back().name.shrink_to_fit();
            }
            cluster.node.shrink_to_fit();
            // Return the cluster info
            return cluster;
        }()},
    fSharedComm{
        [this] {
            MPI_Comm comm;
            // Constructs shared communicator
            MPI_Comm_split(MPI_COMM_WORLD,
                           fCluster.local,
                           0,
                           &comm);
            return comm;
        }()},
    fSharedCommRank{
        [this] {
            int rank;
            // Initialize rank ID in the local communicator
            MPI_Comm_rank(fSharedComm, &rank);
            return rank;
        }()},
    fSharedCommSize{
        [this] {
            int size;
            // Initialize size of the local communicator
            MPI_Comm_size(fSharedComm, &size);
            return size;
        }()} {
    // Disable ROOT implicit multi-threading
    if (ROOT::IsImplicitMTEnabled()) {
        ROOT::DisableImplicitMT();
    }
    // Print startup message
    if (printWelcomeMessage and AtCommWorldMaster()) {
        PrintWelcomeMessageSplitLine();
        PrintWelcomeMessageBody(argc, argv);
        PrintWelcomeMessageSplitLine();
    }
}

} // namespace MACE::Env
