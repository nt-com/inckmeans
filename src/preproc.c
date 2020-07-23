/**
 * Data Preprocessing
 * Functions
 * nt-com 2020
 **/

/**
 * @file preproc.c
 * @brief the c file implementing preprocessing functions
 */

/***************************************************************
 * LIBRARIES
 ***************************************************************/
#include "preproc.h"

/***************************************************************
 * MACROS
 ***************************************************************/

/***************************************************************
 * TYPES
 ***************************************************************/

/***************************************************************
 * GLOBALS
 ***************************************************************/

/***************************************************************
 * INTERNAL FUNCTION PROTOTYPES
 ***************************************************************/
static void preproc_vector_minmax(float *vector, uint32_t size, float *min, float *max);

static float preproc_norm_l1(float *vector, uint32_t size);
static float preproc_norm_l2(float *vector, uint32_t size);

/***************************************************************
 * INTERNAL FUNCTIONS
 ***************************************************************/
static void preproc_vector_minmax(float *vector, uint32_t size, float *min, float *max) {
	
	assert(vector != NULL);
	
	uint32_t ui32_loop = 0x00;
	*min = FLT_MAX;
	*max = FLT_MIN;
	
	for(ui32_loop = 0; ui32_loop < size; ui32_loop++) {
		if(*(vector+ui32_loop) > *max) {
			*max = *(vector+ui32_loop); 
		} /* check maxvalue */
		if(*(vector+ui32_loop) < *min) {
			*min = *(vector+ui32_loop); 
		} /* check minvalue */
	} /* for */

}


/***************************************************************
 * EXTERNAL FUNCTIONS
 ***************************************************************/
extern void preproc_scale_minmax(double *vector, uint32_t size) {

	uint32_t ui32_loop = 0x00;
	float min = FLT_MAX;
	float max = FLT_MIN;
	float denom = 0.0;

	preproc_vector_minmax(vector, size, &min, &max);	
	denom = max-min;

	for(ui32_loop = 0; ui32_loop < size; ui32_loop++) {
		*(vector+ui32_loop) = ( *(vector+ui32_loop) - min )	/ denom;
	}
	
}

extern void preproc_scale_normalize(double *vector, uint32_t size, uint8_t norm) {

	uint32_t ui32_loop = 0x00;
	float denom = 0.0;	

	switch(norm) {
		case PREPROC_NORM_L1:
			denom = preproc_norm_l1(vector, size);
			break;
		case PREPROC_NORM_L2:
			denom = preproc_norm_l2(vector, size);
			break;
		default:
			printf("*PREPROC ERROR* invalid norm.\n");
			break;
	}

	for(ui32_loop = 0; ui32_loop < size; ui32_loop++) {
		*(vector+ui32_loop) /= denom;
	}
	
}


/***************************************************************
 * EOF
 ***************************************************************/
