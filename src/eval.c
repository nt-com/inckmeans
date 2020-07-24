/**
 * Evaluation
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
#include "eval.h"

/***************************************************************
 * MACROS
 ***************************************************************/

/***************************************************************
 * TYPES
 ***************************************************************/

/***************************************************************
 * GLOBALS
 ***************************************************************/
static struct timespec g_start_time;
static struct timespec g_end_time;

/***************************************************************
 * INTERNAL FUNCTION PROTOTYPES
 ***************************************************************/

/***************************************************************
 * INTERNAL FUNCTIONS
 ***************************************************************/

/***************************************************************
 * EXTERNAL FUNCTIONS
 ***************************************************************/
extern void eval_timer_start(void) {

	if(clock_gettime(CLOCK_MONOTONIC, &g_start_time) != 0) {
		printf("*eval_timer_start ERROR* %s\n", strerror(errno));
	}

}

extern void eval_timer_stop(void) {

	if(clock_gettime(CLOCK_MONOTONIC, &g_end_time) != 0) {
		printf("*eval_timer_stop ERROR* %s\n", strerror(errno));
	}

}

extern struct timespec eval_timer_result(char *s) {

	struct timespec result; 

	result.tv_sec = g_end_time.tv_sec - g_start_time.tv_sec;	
	result.tv_nsec = g_end_time.tv_nsec - g_start_time.tv_nsec;

	if(s != NULL) { 
		printf("{ %s }\t", s);
	}
	printf("*TIME EXPIRED* [ %lu seconds, %lu nanoseconds ]\n", result.tv_sec, result.tv_nsec);

	return result;	

}



/***************************************************************
 * EOF
 ***************************************************************/
