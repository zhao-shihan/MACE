///////////////////////////////////////
//         Configs for           //
///////////////////////////////////////

#define NAME                 sample

#define TARGET_REGION        -25000<x&&x<25000 && -25000<y&&y<25000 && -5000<z&&z<5000
#define STEP_OF_PUSHING      1000 // um
// #define PERIODIC_BOUNDARY_X  
// #define PERIODIC_BOUNDARY_Y  
// #define PERIODIC_BOUNDARY_Z  

#define MUONIUM_LIFE         2.197 // us
#define MUONIUM_MASS         105.6584 // MeV/c^2
#define MEAN_FREE_PATH       0.5 // um
#define TEMPERATURE          300 // K

#define SOURCE               exp(-(x*x+y*y)*5e-9) // um^-3
#define SOURCE_X_MIN         -25000 // um
#define SOURCE_X_MAX         25000 // um
#define SOURCE_Y_MIN         -25000 // um
#define SOURCE_Y_MAX         25000 // um
#define SOURCE_Z_MIN         -5000 // um
#define SOURCE_Z_MAX         5000 // um

#define MUONIUM_NUM          1000000
#define BEGIN_TIME           0 // us
#define OUTPUT_STEP          5 // us
#define END_TIME             10 // us

#define SEED                 4357
#define WORKER_JOB_SIZE      1000

///////////////////////////////////////
//  Configs for  post processor  //
///////////////////////////////////////

// Analysis range.
//
#define POST_TARGET_X_MIN            -25000 // um
#define POST_TARGET_X_MAX            25000 // um
#define POST_TARGET_Y_MIN            -25000 // um
#define POST_TARGET_Y_MAX            25000 // um
#define POST_TARGET_Z_MIN            -5000 // um
#define POST_TARGET_Z_MAX            5000 // um

#define POST_WORLD_X_MIN             -40000 // um
#define POST_WORLD_X_MAX             40000 // um
#define POST_WORLD_Y_MIN             -40000 // um
#define POST_WORLD_Y_MAX             40000 // um
#define POST_WORLD_Z_MIN             -40000 // um
#define POST_WORLD_Z_MAX             40000 // um

// Position H3F configs.
//
#define POST_POS_N_BINS_X            100
#define POST_POS_N_BINS_Y            100
#define POST_POS_N_BINS_Z            100

// Position H2F configs.
//
#define POST_POS_N_XY_SLICE          5
#define POST_POS_XY_SLICE_DZ         100 // um
#define POST_POS_XY_SLICE_N_BINS_X   1000
#define POST_POS_XY_SLICE_N_BINS_Y   1000

#define POST_POS_N_YZ_SLICE          5
#define POST_POS_YZ_SLICE_DX         100 // um
#define POST_POS_YZ_SLICE_N_BINS_Y   1000
#define POST_POS_YZ_SLICE_N_BINS_Z   1000

#define POST_POS_N_XZ_SLICE          5
#define POST_POS_XZ_SLICE_DY         100 // um
#define POST_POS_XZ_SLICE_N_BINS_X   1000
#define POST_POS_XZ_SLICE_N_BINS_Z   1000

// Vertex of escape H3F configs.
//
#define POST_VTX_BINS_X              100
#define POST_VTX_BINS_Y              100
#define POST_VTX_BINS_Z              100

// Vertex of escape H2F configs
//
#define POST_VTX_N_XY_SLICE          5
#define POST_VTX_XY_SLICE_DZ         100 // um
#define POST_VTX_XY_SLICE_N_BINS_X   1000
#define POST_VTX_XY_SLICE_N_BINS_Y   1000

#define POST_VTX_N_YZ_SLICE          5
#define POST_VTX_YZ_SLICE_DX         100 // um
#define POST_VTX_YZ_SLICE_N_BINS_Y   1000
#define POST_VTX_YZ_SLICE_N_BINS_Z   1000

#define POST_VTX_N_XZ_SLICE          5
#define POST_VTX_XZ_SLICE_DY         100 // um
#define POST_VTX_XZ_SLICE_N_BINS_X   1000
#define POST_VTX_XZ_SLICE_N_BINS_Z   1000

// Decay of escape H3F configs.
//
#define POST_DEC_BINS_X              100
#define POST_DEC_BINS_Y              100
#define POST_DEC_BINS_Z              100

// Decay of escape H2F configs
//
#define POST_DEC_N_XY_SLICE          5
#define POST_DEC_XY_SLICE_DZ         1000 // um
#define POST_DEC_XY_SLICE_N_BINS_X   1000
#define POST_DEC_XY_SLICE_N_BINS_Y   1000

#define POST_DEC_N_YZ_SLICE          5
#define POST_DEC_YZ_SLICE_DX         1000 // um
#define POST_DEC_YZ_SLICE_N_BINS_Y   1000
#define POST_DEC_YZ_SLICE_N_BINS_Z   1000

#define POST_DEC_N_XZ_SLICE          5
#define POST_DEC_XZ_SLICE_DY         1000 // um
#define POST_DEC_XZ_SLICE_N_BINS_X   1000
#define POST_DEC_XZ_SLICE_N_BINS_Z   1000
