#pragma once

#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/DataType.h++"

#include "ROOT/RDF/RInterface.hxx"

#include "mpi.h"

#include "fmt/format.h"

#include <cassert>
#include <cstdio>
#include <string>
#include <unordered_set>
#include <vector>

namespace MACE::inline Utility {

template<typename... Ts>
auto FindRDFEventSplitPoint(ROOT::RDF::RInterface<Ts...> rdf, std::string eventIDBranchName = "EvtID") -> std::vector<unsigned> {
    std::vector<unsigned> eventSplitPoint;

    if (Env::MPIEnv::Instance().OnCommWorldMaster()) {
        unsigned index{};
        int lastEventID{-1};
        std::unordered_set<int> eventIDSet;
        rdf.Foreach(
            [&](int eventID) {
                assert(eventID >= 0);
                if (eventID != lastEventID) {
                    if (not eventIDSet.emplace(eventID).second) {
                        fmt::println(stderr, "Dataset is unordered (event {} has appeared previously), result might be incorrect", eventID);
                    }
                    lastEventID = eventID;
                    eventSplitPoint.emplace_back(index);
                }
                ++index;
            },
            {std::move(eventIDBranchName)});
        eventSplitPoint.emplace_back(0);
    }

    auto eventSplitPointSize{eventSplitPoint.size()};
    MPI_Bcast(&eventSplitPointSize,                // buffer
              1,                                   // count
              MPIX::DataType(eventSplitPointSize), // datatype
              0,                                   // root
              MPI_COMM_WORLD);                     // comm
    eventSplitPoint.resize(eventSplitPointSize);

    MPI_Bcast(eventSplitPoint.data(), // buffer
              eventSplitPoint.size(), // count
              MPI_UNSIGNED,           // datatype
              0,                      // root
              MPI_COMM_WORLD);        // comm

    return eventSplitPoint;
}

} // namespace MACE::inline Utility
