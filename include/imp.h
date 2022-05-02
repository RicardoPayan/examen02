#ifndef ED_IMP_H_
#define ED_IMP_H_

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

/***************************/
/* EXPRESIONES ARITMÉTICAS */
/***************************/

#ifndef MEMORYADD_TYPE
#define MEMORYADD_TYPE

struct memoryadd_t;
typedef struct memoryadd_t memoryadd_t;

#endif

/*
  Una estructura de tipo `aexp_t' representa una expresión aritmética.
 */
struct aexp_t;
typedef struct aexp_t aexp_t;

/*
  A -> N | (A + A) | (A - A) | (A * A) 
  
  Una expresión aritmética A puede ser un natural, una suma, una resta
  o una multiplicación.
  Los siguientes predicados determinan qué tipo de expresión es A.
  Toda expresión aritmética satisface únicamente uno de estos
  predicados.
 */
bool aexp_is_num(aexp_t *a);
bool aexp_is_add(aexp_t *a);
bool aexp_is_sub(aexp_t *a);
bool aexp_is_mul(aexp_t *a);
bool aexp_is_mem(aexp_t *a);

/*
  El valor de un natural se puede obtener con el selector `aexp_num',
  mientras que los operandos izquierdo y derecho de una suma, resta o
  multiplicación se pueden obtener con los selectores `aexp_left' y
  `aexp_right' respectivamente.
 */
uint64_t aexp_num(aexp_t *a);
aexp_t *aexp_left(aexp_t *a);
aexp_t *aexp_right(aexp_t *a);
aexp_t *aexp_index(aexp_t *a);

/*
  Los siguientes constructores permiten crear un natural a partir de
  un valor de tipo `uint64_t', o bien, una expresión aritmética
  compuesta por otras expresiones aritméticas más simples.
 */
aexp_t *aexp_make_num(uint64_t num);
aexp_t *aexp_make_add(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_sub(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_mul(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_mem(aexp_t *index);

/*
  Para liberar el espacio en memoria que ocupa una expresión
  aritmética se utiliza el siguiente destructor.
 */
void aexp_free(aexp_t *a);

/*
  Evaluador de expresiones aritméticas.
 */
uint64_t aexp_eval(aexp_t *a, memoryadd_t* m);
/*************************/
/* EXPRESIONES BOOLEANAS */
/*************************/

struct bexp_t;
typedef struct bexp_t bexp_t;

/*
  B -> true | false | (A = A) | (A < A) | (B and B) | (B or B) | not B
  Una expresión Booleana B puede ser verdadero, falso, la comparación
  de igualdad y menor qué entre dos expresiones ariméticas, la
  conjunción, disyunción y negación de expresiones Booleanas.
  Los siguientes predicados determinan qué tipo de expresión es B.
  Toda expresión booleana satisface únicamente uno de estos
  predicados.
 */
bool bexp_is_true(bexp_t *b);
bool bexp_is_false(bexp_t *b);
bool bexp_is_equal(bexp_t *b);
bool bexp_is_less(bexp_t *b);
bool bexp_is_and(bexp_t *b);
bool bexp_is_or(bexp_t *b);
bool bexp_is_neg(bexp_t *b);

/*
Sirven para acceder a los componentes de una expresión booleana segun su tipo
*/
aexp_t *bexp_aleft(bexp_t *b);
aexp_t *bexp_aright(bexp_t *b);
bexp_t *bexp_bleft(bexp_t *b);
bexp_t *bexp_bright(bexp_t *b);
bexp_t *bexp_nchild(bexp_t *b);

/* 
Constructores de cada tipo de expresiones booleanas
*/

bexp_t *bexp_make_true();
bexp_t *bexp_make_false();
bexp_t *bexp_make_equal(aexp_t *left, aexp_t *right);
bexp_t *bexp_make_less(aexp_t *left, aexp_t *right);
bexp_t *bexp_make_and(bexp_t *left, bexp_t *right);
bexp_t *bexp_make_or(bexp_t *left, bexp_t *right);
bexp_t *bexp_make_neg(bexp_t *child);

/**
 * @brief Libera la memoria que utiliza una expresión booleana
 *        incluyendo a cualquiera de sus hijos.
 * 
 * @param b Expresión booleanas por liberar.
 */
void bexp_free(bexp_t *b);

/**
 * @brief Evalua el valor de verdad de una expresión booleana.
 * 
 * @param b Expresión booleana por evaluar.
 * @return bool Valor de verdad de la expresión. 
 */
bool bexp_eval(bexp_t *b, memoryadd_t* m);

/***************************/
/* EXPRESIONES DE PROGRAMA */
/***************************/

struct pexp_t;
typedef struct pexp_t pexp_t;

/*
ENUNCIADOS:
Se elige cual es la expresión de P mas adecuada para el programa a partir de la siguientes reglas gramaticales:

P-> skip | x[A]:=A | (P;P)|(while B do P)|(if B then P else P)
*/
bool pexp_is_skip(pexp_t *p);
bool pexp_is_ass(pexp_t *p);
bool pexp_is_seq(pexp_t *p) ;
bool pexp_is_while(pexp_t *p);
bool pexp_is_if(pexp_t *p);

/*
CONSTRUCTORES:
Utilizando las mismas reglas gramaticales de P comentadas anteriormente, Estos constructores determinan y crean los enunciados de P
*/
pexp_t *pexp_make_skip();
pexp_t *pexp_make_assign(aexp_t *index, aexp_t *rvalue);
pexp_t *pexp_make_sequence(pexp_t *pfirst, pexp_t *psecond);
pexp_t *pexp_make_while(bexp_t *condition, pexp_t *ptrue);
pexp_t *pexp_make_if(bexp_t *conditional, pexp_t *iftrue, pexp_t *ifelse);

/*
SELECTORES:
Sirven para acceder a los componentes de un programa
*/
aexp_t *pexp_aindex(pexp_t *p);
aexp_t *pexp_arvalue(pexp_t *p);
pexp_t *pexp_psecond(pexp_t *p);
pexp_t *pexp_pfirst(pexp_t *p);
bexp_t *pexp_bcondition(pexp_t *p);
pexp_t *pexp_ptrue(pexp_t *p);
pexp_t *pexp_pfalse(pexp_t *p);
pexp_t *pexp_iftrue(pexp_t *p);
pexp_t *pexp_ifelse(pexp_t *p);
bexp_t *pexp_bconditional(pexp_t *p);
//DESTRUCTOR >:(
/**
* @brief Libera la memoria de un programa P
* @param p el programa del cual se desea liberar memoria.
*/
void pexp_free(pexp_t *p);

//EVALUADOR :)
/*
* @brief Evalúa los procesos de un programa y su utilización de memoria
* @param p Programa que se evaluará
* @param m Memoria del programa
* @return true En caso que el funcionamiento sea correcto
* @return false En caso de alguna falla
*/
bool peval(pexp_t *p, memoryadd_t* m);

#endif  /* ED_IMP_H_ */
