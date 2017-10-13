#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "ringBuffer.h"

int main(){
	buff = create_buffer();	
	pthread_t r[P], w[P];

	for(int i = 0; i < P; i++){
		pthread_create(&w[i], NULL ,proc_write, (void *)&i);

		pthread_create(&r[i], NULL, proc_read, (void *)&i);
	}
	
	printf("Cant: %d\n", buff->cant);
  	pthread_join(r[0], NULL); /* Espera para siempre */	
	return 0;
}
