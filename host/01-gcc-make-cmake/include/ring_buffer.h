/*
 * Pointers must not be NULL
 */

#ifndef __RING_BUFFER_H
#define __RING_BUFFER_H

#define BUFFER_SIZE 10

#include <stdbool.h>

typedef struct
{
	int buffer[BUFFER_SIZE];
	unsigned int writer,reader,cont;
} ring_buffer;


void rb_init(ring_buffer *b);
int rb_write(int value, ring_buffer *b);
int rb_read(int *value, ring_buffer *b);
bool rb_is_empty(const ring_buffer *b);
bool rb_is_full(const ring_buffer *b);

void rb_display(const ring_buffer *b);

#endif

