#include "ring_buffer.h"
#include <assert.h>
#include <stdio.h>

void test_init_leaves_empty(){
	ring_buffer b;

	rb_init(&b);
	
	assert(rb_is_empty(&b));
	assert(!rb_is_full(&b));
}

void test_data_in_out(){
	ring_buffer b;

	int writed_data = 42, readed_data;
	rb_init(&b);
	rb_write(writed_data,&b);
	rb_read(&readed_data, &b);

	assert(writed_data == readed_data);
}

void test_multiple_data_in_out(){
	ring_buffer b;

	rb_init(&b);

	int writed_data[BUFFER_SIZE];
	int readed_data[BUFFER_SIZE];
	for (int i = 0; i<BUFFER_SIZE; i++){
		writed_data[i] = i;
		assert(rb_write(writed_data[i],&b) == 0);
	}

	for (int i = 0; i<BUFFER_SIZE; i++)
		assert(rb_read(&readed_data[i], &b) == 0);

	for (int i = 0; i<BUFFER_SIZE; i++)
		assert(writed_data[i] == readed_data[i]);
}

void test_write_when_full(){
	ring_buffer b;

	rb_init(&b);

	while (!rb_is_full(&b))
		rb_write(1,&b);

	assert(rb_write(1,&b) == 1);
}

void test_read_when_empty(){
	ring_buffer b;
 	int data;
	rb_init(&b);

	assert(rb_read(&data, &b) == 1);
}

void test_index_rotation(){
	ring_buffer b;
	int data[BUFFER_SIZE];

	rb_init(&b);

	for (int i = 0; i<BUFFER_SIZE; i++)
		assert(rb_write(i,&b) == 0);

	for (int i = 0; i<5; i++)
		assert(rb_read(data,&b) == 0);

	for (int i = BUFFER_SIZE; i<BUFFER_SIZE+5; i++)
		assert(rb_write(i,&b) == 0);
		
	for (int i = 0; i<BUFFER_SIZE; i++)
		assert(rb_read(&data[i],&b) == 0);

	for (int i = 0; i<BUFFER_SIZE; i++)
		assert(data[i] == i+5);

	assert(rb_is_empty(&b));
}

int main(){

	test_init_leaves_empty();
	test_data_in_out();
	test_multiple_data_in_out();
	test_write_when_full();
	test_read_when_empty();
	test_index_rotation();

	puts("All tests passed.");
	
	return 0;
}