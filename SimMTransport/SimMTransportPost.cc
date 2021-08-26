#include "mpi.h"
#include "Post.C"
#include "PostConfig.hh"

#ifdef POST_TO_STR
#error "Conflict of #define POST_TO_STR."
#else
#define POST_TO_STR(str) #str
#endif
#ifdef POST_CFG_TO_STR
#error "Conflict of #define POST_CFG_TO_STR."
#else
#define POST_CFG_TO_STR(cfg) POST_TO_STR(cfg)
#endif 

void DoAnalysis(const TString& name);
void PrintUsage();

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    if (argc != 2 && argc != 3) {
        PrintUsage();
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    int nTotal = std::stoi(argv[1]);
    if (nTotal > 0) {
        int commRank; MPI_Comm_rank(MPI_COMM_WORLD, &commRank);
        int commSize; MPI_Comm_size(MPI_COMM_WORLD, &commSize);
        int begin = 0;
        for (int i = 0; i < commRank; ++i) {
            begin += nTotal / commSize;
            if (i < nTotal % commSize) { ++begin; }
        }
        int end = begin + nTotal / commSize;
        if (commRank < nTotal % commSize) { ++end; }
        std::cout << "Rank" << commRank << " is ready to process " << end - begin << " files." << std::endl;
        for (int i = begin; i < end; ++i) {
            const TString name(TString(POST_CFG_TO_STR(_NAME)) + "_rank" + i + ".root");
            DoAnalysis(name);
        }
    } else {
        if (argc != 3) {
            PrintUsage();
            MPI_Finalize();
            return EXIT_FAILURE;
        }
        DoAnalysis(argv[2]);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}

void DoAnalysis(const TString& name) {
    POST(
        name, "processed_" + name,

        POST_TARGET_X_MIN,
        POST_TARGET_X_MAX,
        POST_TARGET_Y_MIN,
        POST_TARGET_Y_MAX,
        POST_TARGET_Z_MIN,
        POST_TARGET_Z_MAX,

        POST_WORLD_X_MIN,
        POST_WORLD_X_MAX,
        POST_WORLD_Y_MIN,
        POST_WORLD_Y_MAX,
        POST_WORLD_Z_MIN,
        POST_WORLD_Z_MAX,

        POST_POS_N_BINS_X,
        POST_POS_N_BINS_Y,
        POST_POS_N_BINS_Z,

        POST_POS_N_XY_SLICE,
        POST_POS_XY_SLICE_DZ,
        POST_POS_XY_SLICE_N_BINS_X,
        POST_POS_XY_SLICE_N_BINS_Y,

        POST_POS_N_YZ_SLICE,
        POST_POS_YZ_SLICE_DX,
        POST_POS_YZ_SLICE_N_BINS_Y,
        POST_POS_YZ_SLICE_N_BINS_Z,

        POST_POS_N_XZ_SLICE,
        POST_POS_XZ_SLICE_DY,
        POST_POS_XZ_SLICE_N_BINS_X,
        POST_POS_XZ_SLICE_N_BINS_Z,

        POST_VTX_BINS_X,
        POST_VTX_BINS_Y,
        POST_VTX_BINS_Z,

        POST_VTX_N_XY_SLICE,
        POST_VTX_XY_SLICE_DZ,
        POST_VTX_XY_SLICE_N_BINS_X,
        POST_VTX_XY_SLICE_N_BINS_Y,

        POST_VTX_N_YZ_SLICE,
        POST_VTX_YZ_SLICE_DX,
        POST_VTX_YZ_SLICE_N_BINS_Y,
        POST_VTX_YZ_SLICE_N_BINS_Z,

        POST_VTX_N_XZ_SLICE,
        POST_VTX_XZ_SLICE_DY,
        POST_VTX_XZ_SLICE_N_BINS_X,
        POST_VTX_XZ_SLICE_N_BINS_Z,

        POST_DEC_BINS_X,
        POST_DEC_BINS_Y,
        POST_DEC_BINS_Z,

        POST_DEC_N_XY_SLICE,
        POST_DEC_XY_SLICE_DZ,
        POST_DEC_XY_SLICE_N_BINS_X,
        POST_DEC_XY_SLICE_N_BINS_Y,

        POST_DEC_N_YZ_SLICE,
        POST_DEC_YZ_SLICE_DX,
        POST_DEC_YZ_SLICE_N_BINS_Y,
        POST_DEC_YZ_SLICE_N_BINS_Z,

        POST_DEC_N_XZ_SLICE,
        POST_DEC_XZ_SLICE_DY,
        POST_DEC_XZ_SLICE_N_BINS_X,
        POST_DEC_XZ_SLICE_N_BINS_Z
    );
}

void PrintUsage() {
    std::cout <<
        "Usage: POST [num of root files. (e.g. xxx_rank0.root ~ xx_rankN.root, N+1 in total. Set 0 if need to specify file name.)] {[name]}\n"
        "Notice: Out of memory may occur when there are too many processes." << std::endl;
}

