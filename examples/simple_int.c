/*
 * Simple Integer Vector Test
 * 
 * Tests CN_Vec and how they can be used to store integers and
 * print them out in the order that they were added to the vec.
 * 
 * This application stores 0 through 9 in the vector and then
 * prints them out in that order by iterating through.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../cn_vec.h"

main() {
	//Initialize the vec
	CN_VEC vec = cn_vec_init(int);
	
	int a;
	for (a = 0; a < 10; a++)
		cn_vec_push_back(vec, &a); //Pushes the value of "a" into the vec
	
	int i = 0;
	for (; i < cn_vec_size(vec); i++)
		printf("%d\n", cn_vec_get(vec, int, i)); //Prints to stdout.
	
	//Free the vec
	cn_vec_free(vec);
}
