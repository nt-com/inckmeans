/**
 * Incremental kmeans Algorithm
 * Header File
 * nt-com 2020
 **/

/**
 * @file kmeans.h
 * @brief the header file for the kmeans algorithm
 */

#ifndef _KMEANS_H_
#define _KMEANS_H_

/***************************************************************
 * LIBRARIES
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <float.h>

#include "kmeans_cfg.h"

/***************************************************************
 * MACROS
 ***************************************************************/
#define TRUE 1
#define FALSE 0

#define KMEANS_SUCCESS	0
#define KMEANS_FAILURE	1

/***************************************************************
 * TYPES / DATA STRUCTURES
 ***************************************************************/
/** @brief data structure to hold a datapoint */
typedef struct datapoint {
	float coordinates[DIMENSIONS];
} datapoint_t;

/** @brief data structure that holds information about incremental kmeans */
typedef struct kmeans {
	/* number of points attributed to a centroid */
	uint32_t noPoints[NUMBER_CENTROIDS];
	/* the coordinates of a centroid */
	datapoint_t centroids[NUMBER_CENTROIDS];
} kmeans_t;

/** @brief data structure that holds data about a categorized point */
typedef struct categorized {
	/* the point coordinates */
	datapoint_t datapoint;
	/* the category the point is attributed to */
	uint32_t category;
} categorized_t;

/** @brief for distance metric selection, more readable */
typedef enum DISTANCE_METRIC {
	MANHATTAN,
	EUCLIDEAN
} distance_metric_t;

/***************************************************************
 * GLOBALS
 ***************************************************************/

/***************************************************************
 * FUNCTION PROTOTYPES
 ***************************************************************/
/**
 * @brief creates a new instance of kmeans
 * @param metric selects the distance metric to use [MANHATTAN, EUCLIDEAN]
 * @return KMEANS_SUCCESS (0) on success, KMEANS_FAILURE (1) on failure
 */
extern uint8_t kmeans_init(uint8_t metric);

/**
 * @brief does a random initialization of the kmeans centroids
 * @return void
 */
extern void kmeans_random_init(void);

/**
 * @brief clusters a datapoint
 * @param dp datapoint to cluster
 * @return void
 */
extern void kmeans_cluster(datapoint_t *dp);

/**
 * @brief returns to which cluster a point is added
 * @param dp datapoint to cluster
 * @return cluster number
 */
extern uint32_t kmeans_categorize(categorized_t *c);

/**
 * @brief returns a random datapoint for testing
 * @param void
 * @return random datapoint
 */
extern datapoint_t kmeans_get_random_point(void);

/**
 * @brief get statistics about kmeans
 * @param void
 * @return void
 */
extern void kmeans_stats(uint32_t total_datapoints);

/**
 * @brief deinits kmeans
 * @param void
 * @return void
 */
extern void kmeans_deinit(void);


	
#endif
