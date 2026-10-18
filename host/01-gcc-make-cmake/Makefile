CC=cc
CFLAGS=-std=c11 -Wall -Wextra -Werror -g -Iinclude

.PHONY: all test clean

all: ring_buffer_demo test_ring_buffer
test: test_ring_buffer
	./test_ring_buffer

# Executables
ring_buffer_demo: main.o ring_buffer.o
	$(CC) $^ -o $@

test_ring_buffer: test_ring_buffer.o ring_buffer.o
	$(CC) $^ -o $@


# Object files
%.o: src/%.c include/ring_buffer.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: tests/%.c include/ring_buffer.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o ring_buffer_demo test_ring_buffer