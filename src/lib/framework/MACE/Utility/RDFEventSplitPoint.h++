#pragma once

#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/DataType.h++"
#include "MACE/Extension/ROOTX/RDataFrame.h++"

#include "mpi.h"

#include "fmt/format.h"

#include <cassert>
#include <concepts>
#include <cstdio>
#include <string>
#include <unordered_set>
#include <vector>

namespace MACE::inline Utility {

template<std::integral T = int>
auto RDFEventSplitPoint(ROOTX::RDataFrame auto&& rdf, std::string eventIDBranchName = "EvtID") -> std::vector<unsigned> {
    std::vector<unsigned> eventSplitPoint;

    if (Env::MPIEnv::Instance().OnCommWorldMaster()) {
        unsigned index{};
        T lastEventID{-1};
        std::unordered_set<T> eventIDSet;
        rdf.Foreach(
            [&](T eventID) {
                assert(eventID >= 0);
                if (eventID != lastEventID) {
                    if (not eventIDSet.emplace(eventID).second) {
                        fmt::println(stderr, "Warning: Dataset is disordered (event {} has appeared previously)", eventID);
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
