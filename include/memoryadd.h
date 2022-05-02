#ifndef ED_MEMORYADD_H
#define ED_MEMORYADD_H

#include <inttypes.h>
#include <stdlib.h>
#include "imp.h"

#ifndef MEMORYADD_TYPE
#define MEMORYADD_TYPE

struct memoryadd_t;
typedef struct memoryadd_t memoryadd_t;

#endif

/**
 * @brief Creates a new heap allocated memory list. 
 * 
 * @return memoryadd_t* Valid memory location or NULL is allocation was unsuccesful. 
 */
memoryadd_t* memory_make();

/**
 * @brief Assigns the evaluation of value_exp to the position
 *  that is evaluated from index_exp. 
 * 
 * @param m memoryadd_t* to be modified with new assignment. 
 * @param index_exp Arithmethic expression with index value. 
 * @param value_exp Arithmethic expression with assignment value. 
 * @return memoryadd_t* Pointer to m. NULL if operation was unsuccesful. 
 */
memoryadd_t* memory_assign(memoryadd_t* m, aexp_t* index_exp, aexp_t* value_exp); 

/**
 * @brief Returns the value stored at that index.
 *
 * By default, uninitialized memory locations store the value 0. 
 * @param m Memory list. 
 * @param index_exp Arithmethic expression with index. 
 * @return uint64_t Value stored at that index. 
 */
uint64_t memory_eval(memoryadd_t* m, aexp_t* index_exp);

/**
 * @brief Returns the value stored at that index.
 *
 * By default, uninitialized memory locations store the value 0. 
 * @param m Memory list. 
 * @param index uint64_t.   
 * @return uint64_t Value stored at that index. 
 */
uint64_t memory_eval_num(memoryadd_t* m, uint64_t index);

/**
 * @brief Deletes all data inside the memory list.
 * 
 * @param m Memory list to be freed. 
 */
void memory_free(memoryadd_t* m);
void memory_print(memoryadd_t* m);
#endif
