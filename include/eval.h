/**
 * Evaluation
 * Header File
 * nt-com 2020
 **/

/**
 * @file eval.h
 * @brief the header file for the evaluation functions
 */

/**
 * NOTES:
 *	
 *
 */

#ifndef _EVAL_H_
#define _EVAL_H_

/***************************************************************
 * LIBRARIES
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <errno.h>

/***************************************************************
 * MACROS
 ***************************************************************/

/***************************************************************
 * TYPES / DATA STRUCTURES
 ***************************************************************/

/***************************************************************
 * GLOBALS
 ***************************************************************/

/***************************************************************
 * FUNCTION PROTOTYPES
 ***************************************************************/
extern void eval_timer_start(void);
extern void eval_timer_stop(void);
extern struct timespec eval_timer_result(char *s);

/***************************************************************
 * EOF
 ***************************************************************/	
#endif