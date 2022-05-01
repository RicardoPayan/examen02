#include <memoryadd.h>


//The memory of a program will be represented with a linked list with sentinel.
struct memoryadd_t {
    memoryadd_t* next;
    uint64_t value;
    uint64_t pos; 
};

memoryadd_t* memory_make() {
    memoryadd_t* sent = (memoryadd_t*)malloc(sizeof(memoryadd_t));

    if (sent == NULL) return NULL;
   
    sent->next = NULL;
    sent->value = sent->pos = 0;
    
    return sent;
} 

memoryadd_t* memory_assign(memoryadd_t* m, aexp_t* index_exp, aexp_t* value_exp) {
    uint64_t index = aexp_eval(index_exp, m);
    uint64_t value = aexp_eval(value_exp, m); 
    
    memoryadd_t* iter = m;

    while(iter->next != NULL && iter->next->pos <= index) 
        iter = iter->next;

    if (iter != m && iter->pos == index) {
        iter->value = value;
        return m;
    } 

    memoryadd_t* new_pos = memory_make();
    if (new_pos == NULL) return NULL;

    new_pos->next = iter->next;
    iter->next = new_pos;
    new_pos->pos = index;
    new_pos->value = value;

    return m; 
}

uint64_t memory_eval(memoryadd_t* m, aexp_t* index_exp) {
    uint64_t index = aexp_eval(index_exp, m);

    while(m->next != NULL && m->next->pos <= index) {
        m = m->next;
        if (m->pos == index) return m->value; 
    } 

    return 0;
}

void memory_free(memoryadd_t* m) {
    if (m == NULL) return;

    memoryadd_t* next = m->next;
    free(m);

    while(next != NULL) {
        m = next;
        next = next->next;

        free(m);
    }
}

