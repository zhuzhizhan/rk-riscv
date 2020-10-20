#ifndef _PSP_CONFIG_
#define _PSP_CONFIG_

/* TODO: change D_PSP_ERROR_CHECK to be determined by the build system */
#define D_PSP_ERROR_CHECK            0
#define D_PSP_NUM_OF_INTS_EXCEPTIONS E_EXC_LAST_CAUSE

/* Number of HW threads in the core */
#ifndef D_NUMBER_OF_HARTS
        #define D_PSP_NUM_OF_HARTS    1
#else
        #define D_PSP_NUM_OF_HARTS    D_NUMBER_OF_HARTS
#endif

#endif
