/**
 * Data Preprocessing
 * Header File
 * nt-com 2020
 **/

/**
 * @file preproc.h
 * @brief the header file for data preprocessing functions
 */

/**
 * NOTES:
 *	- add kmeans_instance pointers to docstrings.
 *
 */

#ifndef _PREPROC_H_
#define _PREPROC_H_

/***************************************************************
 * LIBRARIES
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <float.h>
#include <assert.h>

/***************************************************************
 * MACROS
 ***************************************************************/

/***************************************************************
 * TYPES / DATA STRUCTURES
 ***************************************************************/

/***************************************************************
 * GLOBALS
 ***************************************************************/
const enum { /* @norms */
	PREPROC_NORM_L1,
	PREPROC_NORM_L2
} e_preproc_norms;

/***************************************************************
 * FUNCTION PROTOTYPES
 ***************************************************************/
extern void preproc_scale_minmax(float *vector, uint32_t size);
/* see @norms*/
extern void preproc_scale_normalize(float *vector, uint32_t size, uint8_t norm);

extern void preproc_scale_standardize(float *vector, uint32_t size);

/***************************************************************
 * EOF
 ***************************************************************/	
#endif
