/**
 * Incremental kmeans Algorithm
 * Functions
 * nt-com 2020
 **/

/**
 * @file kmeans.c
 * @brief the c file implementing incremental kmeans
 */

/***************************************************************
 * LIBRARIES
 ***************************************************************/
#include "kmeans.h"

/***************************************************************
 * MACROS
 ***************************************************************/

/***************************************************************
 * TYPES
 ***************************************************************/
typedef enum KMEANS_ERROR_CODES {
	KMEANS_OK,							// 0
	KMEANS_INVALID_METRIC		// 1
} KMEANS_ERROR_t;  

/***************************************************************
 * GLOBALS
 ***************************************************************/

/** @brief the points used as initial centroids, for later comparison */
static datapoint_t initial_centroids[NUMBER_CENTROIDS];

/** @brief holds internal error codes */
uint8_t KMEANS_ERROR = KMEANS_OK;

/***************************************************************
 * INTERNAL FUNCTION PROTOTYPES
 ***************************************************************/
/**
 * @brief generates a random datapoint
 * @param p the generated point
 * @return void
 */
static void gen_random_point(datapoint_t *p);

/**
 * @brief prints a datapoint to the screen
 * @param p the datapoint to print
 * @param s a string describing the point
 * @return void
 */
static void print_point(datapoint_t *p, char *s);

/**
 * @brief the manhattan distance metric
 * @param centroid_number the number of the centroid to calculate distance to
 * @param p the datapoint to get the metric for
 * @return the calculated distance
 */
static double manhattan_metric(kmeans_t *kmeans_instance, uint32_t centroid_number, datapoint_t *p);

/**
 * @brief the euclidean distance metric
 * @param centroid_number the number of the centroid to calculate distance to
 * @param p the datapoint to get the metric for
 * @return the calculated distance
 */
static double euclidean_metric(kmeans_t* kmeans_instance, uint32_t centroid_number, datapoint_t *p);

/**
 * @brief adds two points
 * @param p1 point 1
 * @param p2 point 2
 * @return the sum of p1 and p2
 */
static datapoint_t add_points(datapoint_t *p1, datapoint_t *p2);

/**
 * @brief subtracts two points
 * @param p1 point 1
 * @param p2 point 2
 * @return the difference of p1 and p2
 */
static datapoint_t sub_points(datapoint_t *p1, datapoint_t *p2);

/**
 * @brief multiplies a scalar with a point
 * @param scalar the scalar value
 * @param p2 the point 
 * @return product of scalar and p1 
 */
static datapoint_t scalar_prod_points(float scalar, datapoint_t *p2);

/**
 * @brief recalculates a centroid value according to a datapoint
 * @param centroid_number the number of the centroid to recalculate
 * @param dp datapoint to use for recalculation
 * @return the recalculated centroid value
 */
static datapoint_t recalc_centroid(kmeans_t *kmeans_instance, uint32_t centroid_number, datapoint_t *dp);
/**
 * @brief internal error handling
 * @return void
 */
static void kmeans_print_error(void);

/***************************************************************
 * INTERNAL FUNCTIONS
 ***************************************************************/
static void gen_random_point(datapoint_t *p) {

	uint32_t ui32_loop = 0x00;

	for(ui32_loop = 0; ui32_loop < DIMENSIONS; ui32_loop++) {
		p->coordinates[ui32_loop] = ( ((float)rand()) / ((float)RAND_MAX) * MAX_COORDINATE_VALUE);
	}
}

static void print_point(datapoint_t *p, char *s) {

	uint32_t ui32_loop = 0x00;
	printf("%s: ( ", s);
	for(ui32_loop = 0; ui32_loop < DIMENSIONS; ui32_loop++) {
		printf("%.2f  ", p->coordinates[ui32_loop]);
	}	printf(")\n");

}

static double manhattan_metric(kmeans_t *kmeans_instance, uint32_t centroid_number, datapoint_t *p) {

	uint32_t ui32_loop = 0;
	float distance = 0.0;

	for(ui32_loop = 0; ui32_loop < DIMENSIONS; ui32_loop++) {
		distance += fabs(kmeans_instance->centroids[centroid_number].coordinates[ui32_loop] - p->coordinates[ui32_loop]);
	}

	return distance;

}

static double euclidean_metric(kmeans_t *kmeans_instance, uint32_t centroid_number, datapoint_t *p) {

	uint32_t ui32_loop = 0;
	float distance = 0.0;
	float difference = 0.0;

	for(ui32_loop = 0; ui32_loop < DIMENSIONS; ui32_loop++) {
		/* subtract */
		difference = kmeans_instance->centroids[centroid_number].coordinates[ui32_loop] - p->coordinates[ui32_loop];
		/* square */
		difference = difference * difference;
		/* sum */
		distance += difference;
	}

	/* float square root over sum of doubled elements */
	distance = sqrtf(distance);

	return distance;

}


static datapoint_t add_points(datapoint_t *p1, datapoint_t *p2) {

	uint32_t ui32_loop = 0;
	datapoint_t result;	
	
	for(ui32_loop = 0; ui32_loop < DIMENSIONS; ui32_loop++) {
		result.coordinates[ui32_loop] = p1->coordinates[ui32_loop] + p2->coordinates[ui32_loop];
	}

	return result;

}

static datapoint_t sub_points(datapoint_t *p1, datapoint_t *p2) {

	uint32_t ui32_loop = 0;
	datapoint_t result;	
	
	for(ui32_loop = 0; ui32_loop < DIMENSIONS; ui32_loop++) {
		result.coordinates[ui32_loop] = p1->coordinates[ui32_loop] - p2->coordinates[ui32_loop];
	}

	return result;

}


static datapoint_t scalar_prod_points(float scalar, datapoint_t *p) {

	uint32_t ui32_loop = 0;
	datapoint_t result;	
	
	for(ui32_loop = 0; ui32_loop < DIMENSIONS; ui32_loop++) {
		result.coordinates[ui32_loop] = scalar * p->coordinates[ui32_loop];
	}

	return result;


}

static datapoint_t recalc_centroid(kmeans_t *kmeans_instance, uint32_t centroid_number, datapoint_t *dp) {

	datapoint_t temp;

	#ifdef VERBOSE
		printf("\n\n#RECALC CENTROID#\n\n");
		printf("#SUB# (x - centroid)\n");
	#endif
	temp = sub_points(dp, &kmeans_instance->centroids[centroid_number]);
	#ifdef VERBOSE
		print_point(dp, "current point");
		print_point(&kmeans_instance->centroids[centroid_number], "centroid");
		print_point(&temp, "subtraction result");
	#endif

	temp = scalar_prod_points((1.0/(float)(kmeans_instance->noPoints[centroid_number]) ), &temp);
	#ifdef VERBOSE
		printf("#SCALE#\n");	
		printf("(x - centroid) * %.2f\n", (1.0/(float)kmeans_instance->noPoints[centroid_number]));
		print_point(&temp, "scalar product result");
	#endif

	temp = add_points(&kmeans_instance->centroids[centroid_number], &temp);

	#ifdef VERBOSE
		printf("#ADD#\n");
		print_point(&kmeans_instance->centroids[centroid_number], "centroid");
		print_point(&temp, "addition result");
	#endif


	return temp;

}

static void kmeans_print_error(void) {

	/* only a prototype for the error function, can be expanded using this idea */
	switch(KMEANS_ERROR) {
		case KMEANS_INVALID_METRIC:	printf("Invalid Metric Value\n");
																break;
		default:										printf("Unknown Error\n");
																break;
	}

}

/***************************************************************
 * EXTERNAL FUNCTIONS
 ***************************************************************/
extern kmeans_t* kmeans_init(uint8_t metric) {

	KMEANS_ERROR = KMEANS_OK;

	uint32_t ui32_loop = 0;

	/* allocate memory for the kmeans type */ 
	kmeans_t *kmeans_instance = (kmeans_t*)malloc(sizeof(kmeans_t));
	assert(kmeans_instance != NULL);

	/* seed the random number generator */
	srand(time(0));

	/* make points added to a cluster zero for all centroids */
	for(ui32_loop = 0; ui32_loop < NUMBER_CENTROIDS; ui32_loop++) {
		kmeans_instance->noPoints[ui32_loop] = 0;
	}
	
	/* set distance metric */
	kmeans_instance->metric = NULL;

	/* if more metrics are added, used switch right away */
	switch(metric) {
		case MANHATTAN:	
			kmeans_instance->metric = &manhattan_metric;
			break;
		case EUCLIDEAN: 
			kmeans_instance->metric = &euclidean_metric;
			break;
		default:				
			KMEANS_ERROR = KMEANS_INVALID_METRIC;
			break;	
	} /* switch */

	if(KMEANS_ERROR) {
		kmeans_print_error();
		if(kmeans_instance != NULL) {
			free(kmeans_instance);
			kmeans_instance = NULL;
		} /* if instance is not NULL */
	}

	return kmeans_instance;

}

extern void kmeans_random_init(kmeans_t *kmeans_instance) {
	
	uint32_t ui32_loop = 0x00;
	datapoint_t random_point;

	for(ui32_loop = 0; ui32_loop < NUMBER_CENTROIDS; ui32_loop++) {
		gen_random_point(&random_point);
		kmeans_instance->centroids[ui32_loop] = random_point;
		initial_centroids[ui32_loop] = random_point;
		#ifdef VERBOSE
			print_point(&kmeans_instance->centroids[ui32_loop], "centroid set to: ");
		#endif
	}

}

extern void kmeans_cluster(kmeans_t *kmeans_instance, datapoint_t *dp) {

	uint32_t ui32_loop = 0;
	float min_distance = FLT_MAX;
	float current_distance = 0.0;
	uint32_t min_index = 0;

	for(ui32_loop = 0; ui32_loop < NUMBER_CENTROIDS; ui32_loop++) {
	 current_distance = kmeans_instance->metric(kmeans_instance, ui32_loop, dp);
		if(min_distance > current_distance) {
			min_distance = current_distance;
			min_index = ui32_loop;
		}
	}	

	#ifdef VERBOSE
		print_point(dp, "current point:");
		printf("added to cluster %d\n", min_index);
	#endif

	/* add point to cluster */
	kmeans_instance->noPoints[min_index]++;

	/* recalculate centroid */	
	kmeans_instance->centroids[min_index] = recalc_centroid(kmeans_instance, min_index, dp);
		
	#ifdef VERBOSE
		print_point(&kmeans_instance->centroids[min_index], "centroid moved to");
	#endif

}

extern uint32_t kmeans_categorize(kmeans_t *kmeans_instance, categorized_t *c) {

	uint32_t ui32_loop = 0;
	float min_distance = FLT_MAX;
	float current_distance = 0.0;
	uint32_t min_index = 0;

	#ifdef VERBOSE
		print_point(&c->datapoint, "point to categorize");
	#endif

	for(ui32_loop = 0; ui32_loop < NUMBER_CENTROIDS; ui32_loop++) {
	 current_distance = kmeans_instance->metric(kmeans_instance, ui32_loop, &c->datapoint);
		if(min_distance > current_distance) {
			min_distance = current_distance;
			min_index = ui32_loop;
		}
	}	
	
	#ifdef VERBOSE
		printf("minimal distance of %.2f to centroid %d\n", min_distance, min_index);
	#endif

	c->category = min_index;
	return min_index;

}

extern datapoint_t kmeans_get_random_point(void) {
	datapoint_t dp;
	gen_random_point(&dp);
	return dp;
}

extern void kmeans_stats(kmeans_t *kmeans_instance, uint32_t total_datapoints) {

	uint32_t ui32_loop = 0x00;

	printf("\n\n-- STATISTICS ------------------------\n");
	printf("Initial Centroids:\n");
	for(ui32_loop = 0; ui32_loop < NUMBER_CENTROIDS; ui32_loop++) {
		print_point(&initial_centroids[ui32_loop], " ");
	}
	printf("Current Centroids:\n");
	for(ui32_loop = 0; ui32_loop < NUMBER_CENTROIDS; ui32_loop++) {
		print_point(&kmeans_instance->centroids[ui32_loop], " ");
	}
	printf("Datapoints in each Cluster:\n");
	for(ui32_loop = 0; ui32_loop < NUMBER_CENTROIDS; ui32_loop++) {
		printf("Cluster %d: %d/%d datapoints\n", ui32_loop, kmeans_instance->noPoints[ui32_loop], total_datapoints);
	}
	printf("-------------------------------------\n\n");

}

extern void kmeans_deinit(kmeans_t *kmeans_instance) {
	if(kmeans_instance != NULL) {
		free(kmeans_instance);
	}
}

