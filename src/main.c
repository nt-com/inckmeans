/**
 * Test Program for Incremental kmeans Clustering
 * nt-com 2020
 **/

/**
 * @file main.c
 * @brief the main file for testing incremental kmeans
 */ 

/***************************************************************
 * LIBRARIES
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "kmeans.h"

/***************************************************************
 * MACROS
 ***************************************************************/
/** @brief how many points are used for the learning phase */
#define LEARNING_RUNS		10000
/** @brief how many points are categorized */
#define CATEGORIZE_RUNS	3000

/***************************************************************
 * GLOBALS
 ***************************************************************/
FILE* fp = NULL;

/***************************************************************
 * FUNCTION PROTOTYPES
 ***************************************************************/
/**
 * @brief writes the points and their category to a file
 * @param fp file pointer to the file
 * @param c a categorized point
 * @return void
 */
void write_data(FILE* fp, categorized_t *c);

/***************************************************************
 * MAIN
 ***************************************************************/
int main(int argc, char **argv) {

	uint32_t i = 0x00;
	uint32_t category = 0;
	uint32_t points_categorized[NUMBER_CENTROIDS] = { 0x00 };
	datapoint_t dp;
	categorized_t categorized_point;

	/* initialize kmeans with the manhattan metric */	
	kmeans_init(MANHATTAN);	
	/* initialize random cluster centers */
	kmeans_random_init();
	
	/* open a file to write categorized data to, for plotting later */
	fp = fopen("data/clustering.dat", "w");
	if(fp == NULL) {
		printf("error fopen: %s\n", strerror(errno));
	}

	/* in this phase the cluster centers are re-calculated */
	printf("Starting Learning Phase: \n");
	for(i = 0; i < LEARNING_RUNS; i++) {
		/* generate a random point, then cluster it */
		dp = kmeans_get_random_point();
		kmeans_cluster(&dp);
	}

	/* print some statistics about the learning phase */
	kmeans_stats(LEARNING_RUNS);

	/* now begin categorization of random points */
	printf("Starting Categorization Phase: \n");
	for(i = 0; i < CATEGORIZE_RUNS; i++) {
		categorized_point.datapoint = kmeans_get_random_point();
		category = kmeans_categorize(&categorized_point);
		points_categorized[category]++;
		write_data(fp, &categorized_point);
	}

	/* print statistics after categorization */
	for(i = 0; i < NUMBER_CENTROIDS; i++) {
		printf("Category %d contains %d/%d points\n", i, points_categorized[i], CATEGORIZE_RUNS);
	}

	/* properly close the data file */
	if(fclose(fp)) {
		printf("error fclose: %s\n", strerror(errno));
	}

	kmeans_deinit();

	return EXIT_SUCCESS;

}

/***************************************************************
 * FUNCTIONS
 ***************************************************************/
void write_data(FILE* fp, categorized_t *c) {

	/* NOTE: add assertion fp != NULL */

	uint32_t ui32_loop = 0;

	for(ui32_loop = 0; ui32_loop < DIMENSIONS; ui32_loop++) {
		fprintf(fp, "%.10f ", c->datapoint.coordinates[ui32_loop]);
	}

	fprintf(fp, "%d", c->category);

	fprintf(fp, "\n");

}

/***************************************************************
 * EOF
 ***************************************************************/
