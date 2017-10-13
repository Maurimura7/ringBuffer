#ifndef __RINGBUFF_H__
#define __RINGBUFF_H__

//Tiene que ser potencia de 2, para que la indexacion funcione correctamente
#define N 16

//Cantidad de hilos
#define P 32

typedef struct ringBuff{
	int *data;
	int head;
	int tail;
	int cant;
} ringBuff;

typedef ringBuff *RBuff;

//Buffer
RBuff buff;

//Funcion que crea el buffer
RBuff create_buffer();

/*
 * Se encarga de escribir en el buffer
 * Devuelve -1 en caso de error
 *
*/

int write_buffer(int newData);

/*
 * Se encarga de leer del buffer
 * Devuelve -1 en caso de error
 */

int read_buffer(int arg);

/*
 * Se encarga de manejar los threads de escritura
 */

void *proc_write(void *arg);

/*
 * Se encarga de manejar los threads de lectur*a
 */

void *proc_read(void *arg);

#endif /* __RINGBUFF_H__ */
