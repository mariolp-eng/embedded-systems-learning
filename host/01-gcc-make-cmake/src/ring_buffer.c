#include "ring_buffer.h"
#include <assert.h>
#include <stdio.h>

void rb_init(ring_buffer *b){
	assert(b != NULL);
	
	b->cont = 0;
	b->writer = 0;
	b->reader = 0;
}

int rb_write(int value, ring_buffer *b){
	assert(b != NULL);
	
	if (rb_is_full(b))
		return 1;

	b->buffer[b->writer] = value;
	b->writer++;
	if (b->writer == BUFFER_SIZE)
		b->writer = 0;
	b->cont++;
	
	return 0;
}

int rb_read(int *value, ring_buffer *b){
	assert(b != NULL);
	assert(value != NULL);

	if (rb_is_empty(b))
		return 1;

	*value = b->buffer[b->reader];
	b->reader++;
	if (b->reader == BUFFER_SIZE)
		b->reader = 0;
	b->cont--;

	return 0;
}

bool rb_is_empty(const ring_buffer *b){
	assert(b != NULL);

	if (b->cont == 0){
		return true;
	} else {
		return false;
	}
}

bool rb_is_full(const ring_buffer *b){
	assert(b != NULL);
		
	if (b->cont == BUFFER_SIZE){
		return true;
	} else {
		return false;
	}
}



void rb_display(const ring_buffer *b){
	assert(b != NULL);

	for (int i =0; i<BUFFER_SIZE; i++){
		printf("| %d ", b->buffer[i]);
	}
	puts("|");
}
