/*
 * Simple Struct example with CN_Vecs
 * 
 * CN_Vecs hold any datatype as long as the size specified on initialization.
 * It also copies the bytes of a struct into the vector. Hence what we will
 * demonstrate in the code below.
 *
 * This application will make a struct, set some values, push it to the vector.
 * Afterwards, it will modify that struct, then push another copy. Then print
 * out the values of the two structs to stdout.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../cn_vec.h"

typedef struct thing {
	int a, b;
} THING;

main() {
	CN_VEC vec = cn_vec_init(THING);
	
	THING a;
	a.a = 2;
	a.b = 3;

	cn_vec_push_back(vec, &a); //Push a copy of "a" to vec

	//Update the original struct
	a.a++;
	a.b = a.a + a.b;
	cn_vec_push_back(vec, &a); //Push another copy of "a" to vec
	
	THING* ii = 0; //Iterator
	cn_vec_traverse(vec, ii) {
		printf("STRUCT { A: %d, B: %d }\n", ii->a, ii->b);
	}
	
	cn_vec_free(vec);
}
