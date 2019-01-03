#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Definition et declaration de la structure des arguments*/

struct globalArgs_t {
    int nbrThreads; /* Le nombre de threads lancés durant l'exécution*/
    char lettre; /* La lettre de réference*/
    int numInputFiles; /* Le nombre de fichiers qui vont être lus*/
    char **inputFiles; /* Les différents fichiers passés en arguments*/
} globalArgs;

static const char *optString = "t:l:h"; /* Les différentes options valables*/


int main(int argc, char *argv[]){

    int opt=0;

    /* Initialisation de globalArgs avant de commencer*/

    globalArgs.nbrThreads=1; /* Le nombre de threads à exécuter par défaut est 1"*/
    globalArgs.lettre='a'; /* La lettre de réference par défaut est 'a' */
    globalArgs.numInputFiles=1; /* Il doit y avoir au minimum toujours 1 fichier input */
    globalArgs.inputFiles=NULL; 

    opt=getopt(argc, argv, optString); /* On récupert la première option */

    while(opt != -1){ /*Tant que l'option est valable (fait donc partie de optString)*/
        switch(opt){
            case 't':
                globalArgs.nbrThreads=atoi(optarg);
                break;

            case 'l':
                globalArgs.lettre=optarg[0];
                break;

            case '?':
                printf("Erreur : option non reconnue\n");
                exit(EXIT_FAILURE);

            case 'h': /*Display help*/

            default:
                /* On arrivera jamais ici*/
                break;
        }
        opt=getopt(argc, argv, optString); /* Prochaine option*/
    }
    globalArgs.inputFiles=argv + optind;
    globalArgs.numInputFiles=argc - optind;

    printf("Threads : %d , lettre : %c , nombre de fichiers : %d , nom des fichiers : ", globalArgs.nbrThreads, globalArgs.lettre, globalArgs.numInputFiles);

    int j;
    for(j=0; j<globalArgs.numInputFiles; j++){
        printf(" %s ",globalArgs.inputFiles[j]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
