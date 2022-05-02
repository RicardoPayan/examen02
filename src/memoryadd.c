#include <memoryadd.h>


//The memory of a program will be represented with a linked list with sentinel.
struct memoryadd_t {
    memoryadd_t* next;
    uint64_t value;
    uint64_t pos; 
};
// inicializa la lista ligada de la memoria
memoryadd_t* memory_make() {
    memoryadd_t* sent = (memoryadd_t*)malloc(sizeof(memoryadd_t));

    if (sent == NULL) return NULL;
   
    sent->next = NULL;
    sent->value = sent->pos = 0;
    
    return sent;
} 
// busca el nodo con el indice correspondiente (busca un indice que sea menor al que recibio para ordenarla)
// luego agrega el nodo a la lista ligada, si el indice ya existe reemplaza el valor
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
// Consigue el valor en el indice con el nodo correspondiente
uint64_t memory_eval(memoryadd_t* m, aexp_t* index_exp) {
    uint64_t index = aexp_eval(index_exp, m);

    while(m->next != NULL && m->next->pos <= index) {
        m = m->next;
        if (m->pos == index) return m->value; 
    } 

    return 0;
}
// Libera la memoria
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

