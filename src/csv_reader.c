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

/**************************************
 * LIBRARIES
 */
#include "csv_reader.h"

/**************************************
 * MACROS
 */

/**************************************
 * GLOBALS
 */
const char g_CSV_DELIMITER = ',';

/**************************************
 * TYPES
 */

/**************************************
 * FUNCTION PROTOTYPES
 */


/**************************************
 * PUBLIC FUNCTIONS 
 */
extern csv_t *csv_ctor(char *filename, size_t max_linebuffer, uint8_t no_columns) {

	assert(filename != NULL);

	uint8_t i = 0x00;
	csv_t *c = (csv_t*)malloc(sizeof(csv_t));

	c->items = malloc(sizeof(char*)*no_columns);

	for(i = 0; i < no_columns; i++) {
		c->items[i] = NULL;
	}
	
	c->no_columns = no_columns;

	c->max_linebuffer = max_linebuffer;
	c->fptr = fopen(filename, "r");
	c->linebuffer = NULL;

	if(c->fptr == NULL) {
		printf("csv_ctor: %s\n", strerror(errno));
		free(c);
		c = NULL;
	}

	return c;

}

extern void csv_dtor(csv_t *self) {

	uint8_t i = 0x00;

	assert(self != NULL);
	if(self->fptr != NULL) {
		
		if(fclose(self->fptr)) {
			printf("csv_dtor: %s\n", strerror(errno));
		} /* close file */

		if(self->linebuffer != NULL) {
			free(self->linebuffer);
		} /* getline alloc's linebuffer */
		
		if(self->items != NULL) {
			for(i = 0; i < self->no_columns; i++) {
				if(self->items[i] != NULL) {
					free(self->items[i]);
				} /* single item */
			} /* for loop */
		} /* if items not NULL */
		free(self->items);
	
	}

	free(self);

}

extern void csv_getline(csv_t *self) {

	ssize_t bytes_read = 0;
	
	bytes_read = getline(&self->linebuffer, &self->max_linebuffer, self->fptr);
	if(bytes_read == -1) {
		if(errno == ENOMEM || errno == EINVAL) {
			printf("csv_getline: %s\n", strerror(errno));
		} else {
			printf("csv_getline: EOF reached.\n");
		}
		
	}

	self->line_length = bytes_read;

}

extern uint8_t csv_split(csv_t *self) {

	assert(self != NULL);

	if(self->line_length == -1) {
		printf("csv_split: line empty, can't split.\n");
		return CSV_EMPTY_LINE;
	}

	uint16_t i = 0x00;	
	uint8_t column = 0;
	uint8_t token_cursor = 0;
	char *token_buffer = (char*)malloc(sizeof(char)*CSV_TOKENSIZE);		

	for(i = 0; i < self->no_columns; i++) {
		if(self->items[i] != NULL) {
			free(self->items[i]);
			self->items[i] = NULL;
		}
	}

	assert(token_buffer != NULL);

	for(i = 0; i < self->line_length; i++) {

		if(self->linebuffer[i] != g_CSV_DELIMITER && self->linebuffer[i] != '\n') {
			*(token_buffer+token_cursor) = self->linebuffer[i];
			token_cursor++;
		} else {
			self->items[column] = (char*)malloc(sizeof(char)*token_cursor);
			memcpy(self->items[column], token_buffer, token_cursor+1);
			*(self->items[column]+token_cursor) = '\0';
			token_cursor = 0;
			memset(token_buffer, 0, CSV_TOKENSIZE);
			column++;
		} /* else */

	} /* for */

	free(token_buffer);

	return CSV_GOT_LINE;

}

extern uint8_t csv_extract_double(csv_t *self, double *p_dbuf) {

	assert(self != NULL);
	assert(p_dbuf != NULL);
	
	if(self->line_length == -1) {
		printf("csv_extract_double: can't extract double from empty line.\n");
		return CSV_EMPTY_LINE;
	}

	uint16_t i = 0x00;	
	uint8_t buffer_cursor = 0;
	uint8_t token_cursor = 0;
	char *token_buffer = (char*)malloc(sizeof(char)*CSV_TOKENSIZE);		

	assert(token_buffer != NULL);

	for(i = 0; i < self->line_length; i++) {

		if(self->linebuffer[i] != g_CSV_DELIMITER && self->linebuffer[i] != '\n') {
			*(token_buffer+token_cursor) = self->linebuffer[i];
			token_cursor++;
		} else {

			*(p_dbuf+buffer_cursor) = strtod(&token_buffer[0], NULL);

			token_cursor = 0;
			memset(token_buffer, 0, CSV_TOKENSIZE);
			buffer_cursor++;
		}

	}

	free(token_buffer);

	return CSV_GOT_LINE;

}

/**************************************
 * EOF
 */
