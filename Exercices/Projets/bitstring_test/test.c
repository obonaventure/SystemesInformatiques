#include "bitstring.h"

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#define LEN 26

/** CU_ASSERT comme défini dans CUnit.h :
#define CU_ASSERT(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, "", CU_FALSE); }
**
=> CU_assertImplementation() renvoie un boolean (la valeur de l'assertion),
mais pour pouvoir l'affecter directement, il aurait fallu ajouter des parenthèses.
Je le redéfini donc ici :  **/
#define MY_CU_ASSERT(value, args...)                                           \
        do {                                                                   \
                if (!(CU_ASSERT(value))) {                                       \
                        printf(args);                                          \
                        return;                                                \
                }                                                              \
        } while(0)

/* Ptr vers les bitstring employés pour les tests */
static bitstring_t * b;
static bitstring_t * b2;
static bitstring_t * res;

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void) {
    /* code pour l'init de la suite de tests, alloc ou autre... */
    b = NULL;
    b2 = NULL;
    res = NULL;
    return 0; /* elle marche tjrs */
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void) {
    bitstring_free(b);
    bitstring_free(b2);
    bitstring_free(res);
    return 0;
}

/* Teste bitstring_alloc() */
void testAlloc() {
    int i;
    b = bitstring_alloc(LEN);

    printf("\n");
    /* verif mémoire allouée */
    MY_CU_ASSERT(b != NULL,
                 "\t - Le ptr bitstring 'b' ne pointe vers aucune addresse"
                 " mémoire. Lui avez-vous alloué de la mémoire (malloc()) ?"
                 " Renvoyez-vous le bon pointeur ?\n");
    MY_CU_ASSERT(bitstring_len(b) == LEN,
                 "\t - Le bitstring n'a pas la bonne longueur (en bits)."
                 " Avez-vous pensé à l'affecter à une variable de la structure après avoir"
                 " alloué la mémoire ? Il se peut que ce soit votre fonction 'bitstring_len()'"
                 " qui n'est pas correcte.\n");

    for (i = 0; i < LEN; i++) {
        MY_CU_ASSERT(bitstring_get(b, i) == 0,
                     "\t - Au moins un des bits du bitstring ne vaut pas 0. Assurez-vous"
                     " que l'espace mémoire pour les données du bitstring soit bien mis"
                     " à 0 après l'allocation. De plus, est-ce que bitstring_get est correcte?\n");
    }
    
    printf("\t\tVotre fonction 'bitstring_alloc()' a l'air correcte.\n");
}

/* Teste bitstring_set() */
void testSet() {
    int i;
    int testbit = 19;

    printf("\n");
    
    printf("\tMise du bit %d à 1\n", testbit);
    bitstring_set(b, testbit, 1); /*on met le bit testbit à 1*/
    
    /* vérifie que tous les bits sont à 0 (ignore le testbit) */
    for(i = 0; i < LEN; ++i) {
        if(i == testbit)
                continue;
        MY_CU_ASSERT(bitstring_get(b, i) == 0,
                     "\t - Impossible de tester la fonction 'bitstring_set()' car"
                     " votre fonction 'bitstring_get()' ou 'bitstring_alloc()' n'est pas correcte.");
    }

    /* vérifie que le bit testbit est bien à 1 */
    MY_CU_ASSERT(bitstring_get(b, testbit) == 1,
                 "\t - Tous les bits semblent être à 0 dans votre bitstring alors"
                 " que le n°%d (0 étant le premier) devrait être à 1. Le problème"
                 " peut venir de 'bitstring_set()', mais aussi de 'bitstring_get()'.\n",
                 testbit);


    /* on assigne un autre bit dans le même octet pour voir si ça n'efface pas l'autre */
    printf("\tMise du bit %d à 1\n", testbit+2);
    bitstring_set(b, testbit + 2, 1);

    /* revérifie tous les bits */
    /* intéressant uniquement si les étudiants codent 8 bits par octet,
       mais ne devrait pas trigger dans le cas contraire */
    for(i = 0; i < LEN; ++i) {
        if(i == testbit || i == testbit + 2) {
            MY_CU_ASSERT(bitstring_get(b, i) == 1,
                         "\t - Affecter un seul bit fonctionne correctement, mais en"
                         " affecter un second dans le même octet semble effacer le premier (ou ne"
                         " pas affecter correctement le second). Vérifiez que vous ne mettez pas"
                         " tout l'octet à 0 avant d'y set un bit. (Il se peut aussi que ce soit du"
                         " à 'bitstring_get()')\n");
        } else {
            MY_CU_ASSERT(bitstring_get(b, i) == 0,
                         "\t - Affecter un seul bit fonctionne correctement, mais en"
                         " affecter un second dans le même octet altère des bits qui ne devraient pas"
                         " l'être. (Il se peut aussi que ce soit du à 'bitstring_get()')\n");
        }
    }


    /* Il faudrait éventuellement penser à ajouter un test sur le premier et dernier bit du bitstring,
       pour voir s'il n'y a pas d'effet de bord : les numéros de bits allant de 0 à bitstring_len() − 1 */
    
    /* succès */
    printf("\t\tVotre fonction 'bitstring_set()' a l'air correcte.\n");
    printf("\t");
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if(CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite de tests pour bitstring", init_suite1, clean_suite1);
   if(NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - first fct added = first to be run */
   if(NULL == CU_add_test(pSuite, "test de 'bitstring_alloc()'", testAlloc) ||
      NULL == CU_add_test(pSuite, "test de 'bitstring_set()'", testSet)) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   /*CU_console_run_tests(); */
   CU_cleanup_registry();
   return CU_get_error();
}
