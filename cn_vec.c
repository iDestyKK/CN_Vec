/*
 * CN_Vec Library
 *
 * Version 1.0.2 (Last Updated 2016-05-20)
 *
 * Description:
 *     C++ Vectors for C library. Implements the data structure with a struct
 *     and use of realloc() along with exponential expansion via a binary math.
 *     Any datatype can be stored in a CN_Vec, just like C++ Vectors.
 *
 *     Changelog of library is located at the bottom of "cn_vec.h"
 *
 * Author:
 *     Clara Ann Nguyen
 *
 * For documentation and details on every function in this library, visit the following URL:
 * http://web.eecs.utk.edu/~ssmit285/lib/cn_vec/index.html
 */

#include "cn_vec.h"

//Functions
//Initializer
CN_VEC new_cn_vec(cnv_uint size) {
    //Initializes the new vector. It needs the size of the data type we are storing in it.
    CN_VEC vec = (CN_VEC) malloc(sizeof(struct cn_vec));
    vec->size      = 0;
    vec->data      = NULL; //The void of space as we know it.
    vec->elem_size = size; //Size of each element.
    vec->capacity  = 0;

    return vec;
}

//Add
void cn_vec_push_back(CN_VEC vec, void* ptr) {
    //cnv_uint __cap = __cn_vec_gen_capacity(vec->size + 1);
    /*if (vec->size == 0) {
        //Our vector is empty. Initialize the memory properly.
        vec->data = (void *) malloc(vec->elem_size);
        if (vec->data != NULL)
            memcpy(vec->data, ptr, vec->elem_size);
    } else {
        //It's already allocated. Let's expand on it.
        if (__cap != vec->capacity) {
            void* new_vec = realloc(vec->data, vec->elem_size * __cap);
            if (!new_vec) {
                return; //Memory Error
            } else {
                vec->data = new_vec;
            }
        }
        memcpy(vec->data + (vec->size * vec->elem_size), ptr, vec->elem_size);
    }
	vec->size++;*/

    cn_vec_resize(vec, vec->size + 1);
    memcpy(vec->data + ((vec->size - 1) * vec->elem_size), ptr, vec->elem_size);
}

void cn_vec_insert(CN_VEC vec, cnv_uint pos, void* ptr) {
    if (pos == vec->size - 1)
        cn_vec_push_back(vec, ptr); //Cheat
    else
    if (pos >= vec->size)
        return; //Out of bounds
    else {
        cn_vec_resize(vec, vec->size + 1);
        //Abuse the fact that memmove uses a buffer to allow overlaying
        memmove(vec->data + ((pos + 1) * vec->elem_size), vec->data + (pos * vec->elem_size), (vec->size - 1 - pos) * vec->elem_size);
        memcpy(vec->data + (pos * vec->elem_size), ptr, vec->elem_size);
    }
}

//Set
void cn_vec_resize(CN_VEC vec, cnv_uint size) {
    cnv_uint __cap = __cn_vec_gen_capacity(size);
    if (vec->data == NULL)
        vec->data = (void *) malloc(vec->elem_size * __cap);
    else
    if (__cap != vec->capacity) {
        if (size == 0)
            free(vec->data);
        else {
            void* new_vec = (void *) realloc(vec->data, vec->elem_size * __cap);
            if (!new_vec)
                return; //Memory Error
            else
                vec->data = new_vec;
        }
    }
    vec->size = size;
    vec->capacity = __cap;
}

void cn_vec_set(CN_VEC vec, cnv_uint pos, void* ptr) {
    if (pos >= vec->size)
        return; //You failed.
    memcpy(vec->data + (pos * vec->elem_size), ptr, vec->elem_size);
}

void cn_vec_delete(CN_VEC vec, cnv_uint pos) {
    memmove(vec->data +  (pos * vec->elem_size), vec->data + ((pos + 1) * vec->elem_size), (vec->size - 1 - pos) * vec->elem_size);
    /*cnv_uint i = pos;
    for (; i < vec->size - 1; i++)
        memcpy(vec->data + (i * vec->elem_size), vec->data + ((i + 1) * vec->elem_size), vec->elem_size);*/
    cn_vec_resize(vec, vec->size - 1);
}

void cn_vec_copy(CN_VEC dest, CN_VEC src) {
    if (dest == NULL || src == NULL)
        return;
    dest->size      = src->size;
    dest->elem_size = src->elem_size;
    dest->capacity  = src->capacity;

    cn_vec_resize(dest, src->size);
    memcpy(dest->data, src->data, src->size * src->elem_size);
}

//Modify
void cn_vec_clear(CN_VEC vec) {
    free(vec->data);
    vec->size = 0;
}

void cn_vec_swap(CN_VEC vec, cnv_uint pos1, cnv_uint pos2) {
    if (pos1 != pos2 && pos1 < vec->size && pos2 < vec->size) {
        cnv_uint i = 0;
        cnv_byte *b1, *b2;

        //XOR Swap > Malloc & Free... by 0.1 seconds :)
        b1 = vec->data + (pos1 * vec->elem_size);
        b2 = vec->data + (pos2 * vec->elem_size);

        for (; i < vec->elem_size; i++) {
            *b1   ^= *b2;
            *b2   ^= *b1;
            *b1++ ^= *b2++;
        }
    }

    /*void* tmp = (void *) malloc(vec->elem_size);
    memcpy(tmp, vec->data + (pos1 * vec->elem_size), vec->elem_size);
    memcpy(vec->data + (pos1 * vec->elem_size), vec->data + (pos2 * vec->elem_size), vec->elem_size);
    memcpy(vec->data + (pos2 * vec->elem_size), tmp, vec->elem_size);
    free(tmp);*/
}

void cn_vec_reverse(CN_VEC vec) {
    cnv_uint i  = 0,
             sr = cn_vec_size(vec),
             s  = sr / 2; //Round down
    sr--;
    for (; i < s; i++) {
        cn_vec_swap(vec, i, sr - i);
    }
}

/*void cn_vec_sort(CN_VEC vec, void (*func)(void*, void*)) {
    //TODO: Add Sort Functionality (Merge Sort? QSort?)
}*/

//Get
void* cn_vec_at(CN_VEC vec, cnv_uint pos) {
    //Returns the address of an entry in the vector at position "pos".
    if (pos < 0 || pos >= vec->size)
        return (void*)0xDEADBEEF; //Nice try. Segfault land for you buddy.

    return vec->data + (pos * vec->elem_size); //I'm in a good mood today.
}

cnv_uint cn_vec_size(CN_VEC vec) {
    return vec->size;
}

cnv_uint cn_vec_element_size(CN_VEC vec) {
    return vec->elem_size;
}

cnv_uint cn_vec_capacity(CN_VEC vec) {
	return vec->capacity;
}

cnv_byte cn_vec_empty(CN_VEC vec) {
    return (vec->size == 0);
}

void* cn_vec_data(CN_VEC vec) {
    return vec->data;
}

//Iteration
void* cn_vec_begin (CN_VEC vec) { return vec->data; }
void* cn_vec_end   (CN_VEC vec) { return vec->data + (vec->size * vec->elem_size); }
void* cn_vec_rbegin(CN_VEC vec) { return vec->data + (vec->size * vec->elem_size) - vec->elem_size; }
void* cn_vec_rend  (CN_VEC vec) { return vec->data - vec->elem_size; }

//Deinitializer
void cn_vec_free(CN_VEC vec) {
    if (vec->size != 0)
        free(vec->data);
    free(vec);
}

//Functions you won't use if you are sane
cnv_uint __cn_vec_gen_capacity(cnv_uint size) {
    //Constant time implementation
    size--;
    size |= size >> 1 | size >> 2 | size >> 4 | size >> 8 | size >> 16;
    return ++size;
}
