HEADERS = ringBuffer.h 

default: main

main: main.c $(HEADERS)
	gcc main.c ringBuffer.c -lpthread -o ringBuffer
clean:
	-rm -f ringBuffer
