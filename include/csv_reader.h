/**************************************
 * Module Name:
 * Module Short Name:
 * Author:
 * Date: 
 * Description:
 */

/**************************************
 * CHANGELOG
 * [Date][Name]: change
 */

#ifndef CSV_READER_H
#define CSV_READER_H

/**************************************
 * LIBRARIES
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

/**************************************
 * MACROS
 */

#define CSV_FILENAME	"datafiles/test.csv"
#define CSV_TOKENSIZE 20
#define CSV_EMPTY_LINE 0
#define CSV_GOT_LINE 1

/**************************************
 * GLOBALS
 */

/**************************************
 * TYPES
 */
typedef struct {
	FILE *fptr;
	char *linebuffer;
	ssize_t line_length;
	size_t max_linebuffer;
	char **items;
	uint8_t no_columns;
} csv_t;

/**************************************
 * FUNCTION PROTOTYPES
 */
extern csv_t *csv_ctor(char *filename, size_t max_linebuffer, uint8_t no_columns);
extern void csv_dtor(csv_t *self);
extern void csv_getline(csv_t *self);
extern uint8_t csv_split(csv_t *self);
extern uint8_t csv_extract_double(csv_t *self, double *p_dbuf);

/**************************************
 * EOF
 */
#endif


