/**
 * Incremental kmeans Algorithm
 * Configuration File
 * nt-com 2020
 **/

/**
 * @file kmeans_cfg.h
 * @brief the configuration for incremental kmeans
 */

#ifndef _KMEANS_CFG_H_
#define _KMEANS_CFG_H_

/** @brief dimensions of a point */
#define DIMENSIONS 3
/** @brief total number of centroids to use */
#define NUMBER_CENTROIDS 4
/** @brief verbose output of the algorithm */
/* #define VERBOSE 1 */

/** @brief maximal coordinate value of a datapoint */
#define MAX_COORDINATE_VALUE 1.0f

/** @brief data file location, holds clustered data */
#define DATA_FILE "../data/clustering.dat"

#endif
