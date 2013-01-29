.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices
=========



1. Exercices en bash
--------------------

Pour rappel, quelques commandes de base dans le shell pour gèrer les dossiers et fichiers:

 - `ls(1)`_ : affiche la liste des fichiers et dossiers du répertoire spécifié
 - `mv(1)`_ : utilitiaire pour renommer ou déplacer un fichier ou dossier
 - `cp(1)`_ : copie un fichier ou dossier (``-r`` pour les dossiers)
 - `rm(1)`_ : efface un fichier ou dossier
 - `mkdir(1)`_ : crée un répertoire
 - `rmdir(1)`_ : efface un répertoire vide
 - `cd(1posix)`_ : change le répertoire courant
 - `pwd(1)`_ : affiche le répertoire courant
 - `grep(1)`_ : permet de faire des recherches sur le contenu des fichiers

Pour vous familiarisez avec le shell, faites les petits exercices suivants dans le shell:

#. Créez, dans un nouveau répertoire ``my_dir`` le fichier nommé ``first`` contenant le texte "`Inserer`". Vérifiez chaque étape que vous avez en utilisant une des commandes `ls(1)`_, `pwd(1)`_ et `cat(1)`_.
#. Copiez le fichier ``first`` vers ``second`` et ajoutez la ligne "`Retirer`" à ``second``.
#. Comment pourriez-vous afficher la taille des fichiers avec `ls(1)`_?
#. Concaténez ``first`` et ``second`` dans un nouveau fichier ``third`` (sans utiliser la command `echo(1)`_)
#. Utilisez `grep(1)`_ pour afficher le numéro de la ligne sur laquelle se trouve le mot "`Retirer`" dans ``second``.
#. Retournez dans le répertoire parent de ``my_dir`` et copiez le dossier complet ``my_dir`` dans ``my_dir_2``.
#. Effacez le dossier entier ``my_dir`` en une seule commande (utilisez `rm(1)`_).

2. Questions de base
--------------------

#. Compilez et exécutez le code suivant. Expliquez ce que fait l'appel à `printf(3)`_.

        .. code-block:: c

	        int main(int argc, const char *argv[]) 
                {
                        int a = 1252;
                        printf("%d\n", a);
                }

#. Expliquez à quoi sert l'option ``-Werror`` de ``gcc``. Regardez la manpage (`gcc(1)`_).

        .. only:: staff

                .. note::
                        ``-Werror``
                                   Make all warnings into errors.

#. Recompilez le code du point `1` avec l'option ``-Werror``, que ce passe-t'il ? Que faut-t'il rajouter dans le code pour qu'il compile sans erreurs ? 

        .. only:: staff

                .. note::
                
                        Le programme ne compile plus. Il faut inclure ``stdio.h`` parce que C nécessite d'avoir une déclaration des fonctions.

#. (bonus) comment se fait-t'il que ``gcc`` compilait sans problème au point `1`?

        .. only:: staff

                .. note::
                
                        ``gcc`` crée une déclaration implicite des fonctions de la librairie C. Il n'affiche qu'un warning.

#. Lorsque j'exécute le programme corrigé du point `3` dans une console, j'ai accès à plusieurs variables, l'une d'elle est ``$?`` qui permet de récupérer la valeur de retour du dernier programme exécuté. Expliquez à quoi sert cette valeur.

        .. code-block:: console

                $ gcc -Werror -std=c99 test.c -o test
                $ ./test
                42
                $ echo $?
                0

        .. only:: staff

                .. note::

                        voir note du cours.

#. Expliquez à quoi sert l'option ``-Wall`` de ``gcc``.

        .. only:: staff 

                .. note::
                
                        ``-Wall``
                                This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros.

#. Recompilez le code corrigé du point `3` avec les options ``-Wall`` et ``-Werror``, que ce passe-t'il ? Que faut-t'il rajouter dans le code pour qu'il compile sans erreurs ?

        .. only:: staff 

                .. note::
        
                        ``-Wall``: warning si une fonction ne renvoi pas de valeur. Il faut donc ajouter ``return 0;`` à la fin de la ``main``.

#. Compiler le code suivant (sans les options ``-Wall`` et ``-Werror``). Expliquez ce que sont les arguments de la fonction ``main``. Expliquez ce que fait `atoi(3)`_ (voir `strtol(3)`_ pour une fonction similaire). Exécutez ensuite le code avec ou sans arguments. Qu'observez-vous ? Comment se protéger du fait qu'un utilisateur ne va pas forcément rentrer le bon nombre d'arguments ?

        .. code-block:: c

                #include <stdlib.h>
                int main(int argc, const char *argv[])
                {
                        int a = atoi(argv[1]);
                        printf("%d\n", a);
                }

        .. only:: staff 

                .. note::

                        ``argc`` = nombre d'arguments.
                        ``argv`` = tableau de chaine de caractère contenant le nom de l'exécutable suivi des arguments.
                        ``atoi`` = transforme une chaine de caractère en un entier.
                        Le programme renvoi une segmentation fault lorsque l'on ne passe pas d'argument. Il faut donc utiliser ``argc`` pour tester que l'on a le bon nombre d'argument.

#. Ecrivez un programme qui va itérer (avec une boucle ``for`` et une boucle ``while``) et afficher tous les arguments qui lui sont passé à la sortie standard. 

        .. only:: staff 

                .. note::
                        
                        .. code-block:: c
                                
                                #include <stdio.h>
                                int main(int argc, const char *argv[]) 
                                {
                                        int i;
                                        for (i = 1; i < argc; i++)
                                                printf("%s\n", argv[i]);
                                        return 0;
                                }

#. Ecrivez deux programmes qui réagissent de façon similaire à `true(1)`_ et `false(1)`_ en utilisant `exit(3)`_. Vous pouvez tester le bon fonctionnement de votre programme en exécutant le code suivant dans une console:

        .. code-block:: console

                $ if ./true; then echo "true fonctionne"; fi
                true fonctionne
                $ if ! ./false; then echo "false fonctionne"; fi
                false fonctionne

   Bash permet aussi de faire des ``else``. Trouvez comme faire ceci en regardant ce `lien <http://tldp.org/LDP/abs/html/tests.html>`_.
        .. only:: staff 

                .. note::
                
                        ``true`` retourne toujours 0:
                                .. code-block:: c
                                
                                        #include <stdlib.h>
                                        int main(int argc, const char *argv[]) 
                                        {
                                        exit(0);
                                        }

                        ``false`` retourne toujours quelque chose != 0:
                                .. code-block:: c

                                        #include <stdlib.h>
                                        int main(int argc, const char *argv[]) 
                                        {
                                                exit(1);
                                        }
        

3. Petits programmes
--------------------


#.  Faites l'exercice sur `Pythia <http://pythia.info.ucl.ac.be/module/10/problem/26>`_ sur la commande `test(1)`_.

    Pythia est un environnement qui permet de soumettre du code, et des tests sont automatiquement exécuté sur ce code. Cela vous permettra de vérifier que votre programme fonctionne.

    Vous avez besoin d'un login sur Pythia, que vous recevrez durant l'après-midi du 29 janvier.


#. Faites de même pour la commande `expr(1)`_. On vous demande d'implémenter les expressions suivante: ``+``, ``-``, ``*``, ``/`` et ``%``. Mais cette-fois ci sans utiliser Pythia. Vous devriez tester votre programme vous-même et assurez le bon fonctionnement de celui-ci.

   N'oubliez pas de respecter les valeurs de retour comme décrit dans les man-pages.


#. En utilisant le shell et un programme C, essayez de déterminer expérimentalement le nombre maximum d'arguments que vous pouvez passer à un programme C. Y-a-t-il une limite à ce nombre d'arguments ? Si oui, d'où vient-elle et de quoi dépend-elle ?
