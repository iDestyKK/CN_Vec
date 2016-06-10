/*
 * CN_Vec Library
 *
 * Version 1.0.2 (Last Updated 2016-05-16)
 *
 * Description:
 *     C++ Vectors for C library. Implements the data structure with a struct
 *     and use of realloc() along with exponential expansion via a binary math.
 *     Any datatype can be stored in a CN_Vec, just like C++ Vectors.
 *
 *     Changelog of library is located at the bottom of this file.
 *
 * Author:
 *     Clara Van Nguyen
 *
 * For documentation and details on every function in this library, visit the following URL:
 * http://web.eecs.utk.edu/~ssmit285/lib/cn_vec/index.html
 */

#ifndef __CN_VEC__
#define __CN_VEC__

#include <stdlib.h>
#include <string.h>

//Custom Types
typedef unsigned int       cnv_uint;
typedef unsigned long long cnv_u64;
typedef unsigned char      cnv_byte;

//Structs
typedef struct cn_vec {
    void*    data;
    cnv_uint elem_size,
             size,
             capacity;
} *CN_VEC;

typedef CN_VEC VECTOR; //For you C++ people...

//Functions
//Initializer
CN_VEC   new_cn_vec(cnv_uint);

//Add
void     cn_vec_push_back   (CN_VEC, void*);
void     cn_vec_insert      (CN_VEC, cnv_uint, void*);

//Set
void     cn_vec_resize      (CN_VEC, cnv_uint);
void     cn_vec_set         (CN_VEC, cnv_uint, void*);
void     cn_vec_delete      (CN_VEC, cnv_uint);
void     cn_vec_copy        (CN_VEC, CN_VEC  );

//Modify
void     cn_vec_clear       (CN_VEC);
void     cn_vec_swap        (CN_VEC, cnv_uint, cnv_uint);
void     cn_vec_reverse     (CN_VEC);
//void     cn_vec_sort        (CN_VEC, void (*)(void*, void*));

//Get
void*    cn_vec_at          (CN_VEC, cnv_uint);
cnv_uint cn_vec_size        (CN_VEC);
cnv_uint cn_vec_element_size(CN_VEC);
cnv_uint cn_vec_capacity    (CN_VEC);
cnv_byte cn_vec_empty       (CN_VEC);
void*    cn_vec_data        (CN_VEC);

//Iteration
void*    cn_vec_begin       (CN_VEC);
void*    cn_vec_end         (CN_VEC);
void*    cn_vec_rbegin      (CN_VEC);
void*    cn_vec_rend        (CN_VEC);

//Deinitializer
void     cn_vec_free        (CN_VEC);

//Functions you won't use if you are sane
cnv_uint __cn_vec_gen_capacity(cnv_uint);

//Macros
#define cn_vec_deref(ptr, type) \
    (*(type*)ptr) //lol cheat

#define cn_vec_get(CN_VEC, type, pos) \
    cn_vec_deref(cn_vec_at(CN_VEC, pos), type) //CHEAT EVEN MORE

#define cn_vec_init(type) \
    new_cn_vec(sizeof(type)) //For those who hate typing sizeof(...)

#define cn_vec_array(CN_VEC, type) \
    (type*) cn_vec_data(CN_VEC)

#define cn_vec_traverse(CN_VEC, iterator) \
    for (iterator = cn_vec_begin(CN_VEC); iterator != cn_vec_end(CN_VEC); iterator++)

#define cn_vec_rtraverse(CN_VEC, iterator) \
    for (iterator = cn_vec_rbegin(CN_VEC); iterator != cn_vec_rend(CN_VEC); iterator--)

#define cn_vec_front(CN_VEC, type) \
    cn_vec_get(CN_VEC, type, 0)

#define cn_vec_back(CN_VEC, type) \
    cn_vec_get(CN_VEC, type, cn_vec_size(CN_VEC) - 1)

#endif

/***************************************\
    * ** ***    CHANGELOG    *** ** *
\***************************************/

/*
    2016-05-20 (1.0.2)
      - Added function "__cn_vec_gen_capacity", which you shouldn't use.
      - Added function "cn_vec_capacity".
      - Implemented exponential growth via capacity. This replaces linear growth.

    2016-05-16 (1.0.1)
      - Nope, not the only release.
      - Reorganized functions.
      - Added functions "cn_vec_swap", "cn_vec_reverse", "cn_vec_data", "cn_vec_insert", "cn_vec_begin", "cn_vec_end", "cn_vec_rbegin", and "cn_vec_rend".
      - Added macros "cn_vec_array", "cn_vec_traverse", "cn_vec_rtraverse". "cn_vec_front", and "cn_vec_back".
      - Swapped the arguments in macro "cn_vec_deref".

    2016-05-16 (1.0.0)
      - Started writing CN_Vec. Initial (And probably the only) Release.
*/
