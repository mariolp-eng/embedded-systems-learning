#include <stdio.h>
#include "ring_buffer.h"


int main(){

	ring_buffer b;

	// Buffer initialization
	rb_init(&b);
	// Write values in the buffer
	int flag=1;
	while (flag){
		if (rb_write(1, &b) == 1)
		flag = 0;
	}

	rb_display(&b);

	return 0;
}