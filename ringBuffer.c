#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <unistd.h>
#include "ringBuffer.h"

pthread_mutex_t mut  = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full  = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

int writers = 0; //Cantidad de hilos escribiendo
int readers = 0; //Cantidad de hilos leyendo

RBuff create_buffer(){
	RBuff newBuffer = malloc(sizeof(ringBuff));
	newBuffer->data = malloc(sizeof(int) * N);
	newBuffer->head = 0;
	newBuffer->tail = 0;
	newBuffer->cant = 0;
       	return newBuffer;
}

int write_buffer(int newData){

	//Si cantidad es mayor a N sale
	if(buff->cant < N){
		buff->data[ ((buff->head)++) & (N - 1) ] = newData;
		buff->cant++;
		printf("Writting...\n%d\n", newData);

		// Hace un broadcast avisando que el buffer no esta vacio
		pthread_cond_broadcast(&empty);
		return 1;
	}
	return -1;
}

int read_buffer(int arg){

	//Si cantidad es menor a 0 sale
	if(buff->cant > 0){
		int val = buff->data[((buff->tail)++) & (N - 1)];
		buff->cant--;
		printf("Reading...\n%d\n", val);

		// Avisa que hay lugar en el buffer
		pthread_cond_broadcast(&full);
		return val;
	}
	return -1;
}

void *proc_write(void *arg){
	int val = *((int *) arg);

	for(;;){
		usleep(random()%8);
    		pthread_mutex_lock(&mut);

		// Mientras este lleno, espera.
		while(write_buffer(val) < 0){

			// Condicion que indica que el buffer esta lleno
			pthread_cond_wait(&full, &mut);
			printf("BUFFER LLENO\n");
		}

		pthread_mutex_unlock(&mut);
	}
	return NULL;
}

void *proc_read(void *arg){
	int val = *((int *) arg);

	for(;;){
		usleep(random()%3);
    		pthread_mutex_lock(&mut);

		// Mientras este vacio, espera.
		while(read_buffer(val) < 0){

			// Condicion que indica que el buffer esta vacio
			pthread_cond_wait(&empty, &mut);
			printf("BUFFER VACIO\n");
		}
		pthread_mutex_unlock(&mut);

	}
	return NULL;
}
