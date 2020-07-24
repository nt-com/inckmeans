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
#include "preproc.h"
#include "eval.h"
#include "csv_reader.h"

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
 * TEST FUNCTION PROTOTYPES
 ***************************************************************/
void test_kmeans(void);
void test_preproc(void);

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

/**
 * @brief prints a text, followed by an array for example: x = [ 1.0 1.0 ]
 * @param v the vector/array to print
 * @param s the size of the array
 * @param str the text to print along with the array
 * @return void
 */
void print_float_array(float *v, uint32_t s, char *str);

/***************************************************************
 * MAIN
 ***************************************************************/
int main(int argc, char **argv) {

	test_kmeans();
	test_preproc();

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

void print_float_array(float *v, uint32_t s, char *str) {

	uint32_t ui32_loop = 0x00;

	printf("%s = [", str);
	for(ui32_loop = 0; ui32_loop < DIMENSIONS; ui32_loop++) {
		printf(" %.4f ", *(v+ui32_loop));
	}	printf("]\n");

}

/***************************************************************
 * TEST FUNCTIONS
 ***************************************************************/
void test_kmeans(void) {

	uint32_t i = 0x00;
	uint32_t category = 0;
	uint32_t points_categorized[NUMBER_CENTROIDS] = { 0x00 };
	datapoint_t dp;
	categorized_t categorized_point;

	/* initialize kmeans with the manhattan metric */	
	kmeans_t *instance = kmeans_init(MANHATTAN);	
	/* initialize random cluster centers */
	kmeans_random_init(instance);
	
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

		eval_timer_start();
		kmeans_cluster(instance, &dp);
		eval_timer_stop();
		eval_timer_result("Clustering a Point");

	}

	/* print some statistics about the learning phase */
	kmeans_stats(instance, LEARNING_RUNS);

	/* now begin categorization of random points */
	printf("Starting Categorization Phase: \n");
	for(i = 0; i < CATEGORIZE_RUNS; i++) {
		categorized_point.datapoint = kmeans_get_random_point();

		eval_timer_start();
		category = kmeans_categorize(instance, &categorized_point);
		eval_timer_stop();
		eval_timer_result("Categorizing a Point");

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

	kmeans_deinit(instance);

}

void test_preproc(void) {

	float test_vector_1[3] = { 1.0, 2.0, 3.0 };
	float test_vector_2[3] = { 1.0, 2.0, 3.0 };
	float test_vector_3[3] = { 1.0, 2.0, 3.0 };

	eval_timer_start();
	preproc_scale_minmax(&test_vector_1[0], 3);
	eval_timer_stop();
	eval_timer_result("Min-Max Scaling");

	eval_timer_start();
	preproc_scale_normalize(&test_vector_2[0], 3, PREPROC_NORM_L1);
	eval_timer_stop();
	eval_timer_result("Normalize (L1) Scaling");

	eval_timer_start();
	preproc_scale_normalize(&test_vector_3[0], 3, PREPROC_NORM_L2);
	eval_timer_stop();
	eval_timer_result("Normalize (L2) Scaling");

	print_float_array(&test_vector_1[0], 3, "TV1");
	print_float_array(&test_vector_2[0], 3, "TV2");
	print_float_array(&test_vector_3[0], 3, "TV3");

}

/***************************************************************
 * EOF
 ***************************************************************/
