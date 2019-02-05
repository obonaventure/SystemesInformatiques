.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices
=========



1. Exercices de manipulation du shell
-------------------------------------

Pour rappel, quelques commandes de base dans le shell pour gérer les dossiers et fichiers:

 - `ls(1)`_ : affiche la liste des fichiers et dossiers du répertoire spécifié
 - `mv(1)`_ : utilitaire pour renommer ou déplacer un fichier ou dossier
 - `cp(1)`_ : copie un fichier ou dossier (``-r`` pour les dossiers)
 - `rm(1)`_ : efface un fichier ou dossier
 - `mkdir(1)`_ : crée un répertoire
 - `rmdir(1)`_ : efface un répertoire vide
 - `cd(1posix)`_ : change le répertoire courant
 - `pwd(1)`_ : affiche le répertoire courant
 - `grep(1)`_ : permet de faire des recherches sur le contenu des fichiers

Pour vous familiariser avec le shell, faites les petits exercices suivants dans le shell:

#. Créez, dans un nouveau répertoire ``my_dir`` le fichier nommé ``first`` contenant le texte "`Inserer`". Vérifiez chaque étape en utilisant une des commandes `ls(1)`_, `pwd(1)`_ et `cat(1)`_.
#. Copiez le fichier ``first`` vers ``second`` et ajoutez la ligne "`Retirer`" à ``second``.
#. Comment pourriez-vous afficher la taille des fichiers avec `ls(1)`_?
#. Concaténez ``first`` et ``second`` dans un nouveau fichier ``third`` (sans utiliser la command `echo(1)`_)
#. Utilisez `grep(1)`_ pour afficher le numéro de la ligne sur laquelle se trouve le mot "`Retirer`" dans ``second``.
#. Retournez dans le répertoire parent de ``my_dir`` et copiez le dossier complet ``my_dir`` dans ``my_dir_2``.
#. Effacez le dossier entier ``my_dir`` en une seule commande (utilisez `rm(1)`_).

Vous trouverez également sur `le cours LSINF1252 sur inginious <https://inginious.info.ucl.ac.be/course/LSINF1252>`_ les exercices suivants :

#. Utilisation de la commande `grep(1)`_ : https://inginious.info.ucl.ac.be/course/LSINF1252/s1_grep
#. Utilisation des pipes : https://inginious.info.ucl.ac.be/course/LSINF1252/s1_pipes
#. Utilisation de la commande `tar(1)`_ : https://inginious.info.ucl.ac.be/course/LSINF1252/s1_tar
#. Capture the flag (1): https://inginious.info.ucl.ac.be/course/LSINF1252/s1_ctf1
#. Capture the flag (2): https://inginious.info.ucl.ac.be/course/LSINF1252/s1_ctf2

.. only:: staff

   - Il faudrait quand même qu'ils l'aient fait une fois avant le TP
   - Faire l'exercice sur les pipes avant de faire le CTF
   - Si un élève est bloqué, relire les dernières consignes, si rien d'explicite taper "./.suite"
   - Quand les consignes disent de
            dire quelque chose de spécifique = "echo parole | ./interlocuteur"
            parler à quelqu'un = "./interlocuteur"
   - Faire TRÈS attention à taper correctement l'identifiant inginious au début, sinon ce n'est qu'en ayant fini le CTF qu'ils verront l'erreur
   - Attention, quand on tape la réponse finale dans inginious, elle est écrite sous la forme "[hash] -", il faut copier-coller la sortie en entier, le tiret compris, pas juste le hash
   - L'exercice est individuel, la réponse dépend de l'identifiant de l'étudiant
   - En cas de problème avec le code de vérification (il n'y en a théoriquement pas, mais qui sait) le tuteur peut générer la clé à entrer dans inginious comme suit (depuis la racine) :
     	cd .ressources/script
	./init lIdentifiantInginious
	./next
	./next
	./next
	./next
	./next 


2. Découverte du C
------------------

Certains côtés du C sont très proches du langage Java que vous connaissez déjà. Ce n'est pas surprenant
puisque Java a été conçu avec le langage C comme base. Les inventeurs de Java ont ajouté tout ce qui 
était nécessaire pour supporter les objets et ont retiré la gestion explicite de la mémoire. Les premiers
exercices `inginious en C <https://inginious.info.ucl.ac.be/course/LSINF1252>`_ sont très proches de ceux
que vous aviez réalisé en Java.

#. Calcul de la valeur absolue d'une entier: https://inginious.info.ucl.ac.be/course/LSINF1252/absolute_value
#. Calcul de la factorielle d'un nombre entier: https://inginious.info.ucl.ac.be/course/LSINF1252/factorial
#. Recherche d'un élément dans un tableau d'entiers: https://inginious.info.ucl.ac.be/course/LSINF1252/tab_find

#. Compilez et exécutez le code suivant. Expliquez ce que fait l'appel à `printf(3)`_.

        .. code-block:: c

                int f()
                {
                        int a = 1252;
                        printf("%d\n", a);
                }

                int main(int argc, const char *argv[])
                {
                        f();
                }


#. Expliquez à quoi sert l'option ``-Werror`` de ``gcc``. Regardez la manpage (`gcc(1)`_).

        .. only:: staff

                .. note::
                        ``-Werror``
                                   Make all warnings into errors.

#. Recompilez le code du point `4` avec l'option ``-Werror``, que se passe-t-il ? Que faut-t-il rajouter dans le code pour qu'il compile sans erreurs ?

        .. only:: staff

                .. note::

                        Le programme ne compile plus. Il faut inclure ``stdio.h`` parce que C nécessite d'avoir une déclaration des fonctions.

#. (bonus) comment se fait-il que ``gcc`` compilait sans problème au point `4`?

        .. only:: staff

                .. note::

                        ``gcc`` crée une déclaration implicite des fonctions de la librairie C. Il n'affiche qu'un warning.

#. Lorsque j'exécute le programme corrigé du point `6` dans une console, j'ai accès à plusieurs variables. L'une d'elles est ``$?`` qui permet de récupérer la valeur de retour du dernier programme exécuté. Expliquez à quoi sert cette valeur.

        .. code-block:: console

                $ gcc -Werror -std=c99 test.c -o test
                $ ./test
                1252
                $ echo $?
                0

        .. only:: staff

                .. note::

                        voir notes de cours.

#. Expliquez à quoi sert l'option ``-Wall`` de ``gcc``.

        .. only:: staff

                .. note::

                        ``-Wall``
                                This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros.

#. Recompilez le code corrigé du point `6` avec les options ``-Wall`` et ``-Werror``, que se passe-t-il ? Que faut-il rajouter dans le code pour qu'il compile sans erreurs ?

        .. only:: staff

                .. note::

                        ``-Wall``: warning si une fonction ne renvoie pas de valeur. Il faut donc ajouter ``return 0;`` à la fin de la ``main``.


        .. only:: staff

                  #. Compilez le code suivant (sans les options ``-Wall`` et ``-Werror``). Expliquez ce que sont les arguments de la fonction ``main``. Expliquez ce que fait `atoi(3)`_ (voir `strtol(3)`_ pour une fonction similaire). Exécutez ensuite le code avec ou sans arguments. Qu'observez-vous ? Comment se protéger du fait qu'un utilisateur ne va pas forcément rentrer le bon nombre d'arguments ?

                     .. code-block:: c

                        #include <stdlib.h>
                        int main(int argc, const char *argv[])
                        {
                                int a = atoi(argv[1]);
                                printf("%d\n", a);
                        }

                        .. note::

                                ``argc`` = nombre d'arguments.
                                ``argv`` = tableau de chaine de caractère contenant le nom de l'exécutable suivi des arguments.
                                ``atoi`` = transforme une chaine de caractère en un entier.
                                Le programme renvoi une segmentation fault lorsque l'on ne passe pas d'argument. Il faut donc utiliser ``argc`` pour tester que l'on a le bon nombre d'argument.


        .. only:: staff
       
                  #. Ecrivez un programme qui va itérer (avec une boucle ``for`` et une boucle ``while``) et afficher tous les arguments qui lui sont passés à la sortie standard.

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

   Bash permet aussi de faire des ``else``. Trouvez comment faire en regardant ce `lien <http://tldp.org/LDP/abs/html/tests.html>`_.
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



.. only:: staff

          #.  Faites l'exercice sur `commandetest <https://inginious.info.ucl.ac.be/course/LSINF1252/commandetest>`_ sur la commande `test(1)`_.

              INGInious est un environnement qui permet de soumettre du code, et des tests sont automatiquement exécutés sur ce code. Cela vous permettra de vérifier que votre programme fonctionne.

              Pour vous connecter sur INGInious, utilisez votre login INGI que vous recevrez durant la première séance de TP.


          #. Faites de même pour la commande `expr(1)`_. On vous demande d'implémenter les expressions suivantes : ``+``, ``-``, ``*``, ``/`` et ``%``, mais cette fois-ci sans utiliser INGInious. Vous devriez tester votre programme vous-même et assurer le bon fonctionnement de celui-ci.

          N'oubliez pas de respecter les valeurs de retour qui sont décrites dans les man-pages.


.. only:: staff 
          
          #. En utilisant le shell et un programme C, essayez de déterminer expérimentalement le nombre maximum d'arguments que vous pouvez passer à un programme C. Y a-t-il une limite à ce nombre d'arguments ? Si oui, d'où vient-elle et de quoi dépend-elle ?

3. Question de bilan final
--------------------------

Le fizz buzz est un programme qui affiche sur la sortie standard pour chaque entier ``n``:

- ``fizz buzz`` si le nombre est divisible par 3 et par 5;
- ``fizz`` si le nombre est divisible par 3;
- ``buzz`` si le nombre est divisible par 5;
- La valeur de ``n`` sinon.

Un étudiant implémente cet algorithme en Bash. Malheureusement, son script comporte plusieurs erreurs.
Pouvez-vous identifier et corriger les erreurs en question? Son code est disponible ci-dessous.

.. code-block:: bash

        #!/bin/bash

        x=1
        limit=100
        if [ ! -z "$1" ]
        then
            limit=$1
        fi

        while [[ $x < "$limit" ]]
        do
            if [[0 -eq "($x%3)"  && 0 -eq "($x%5)"]]
            then
                # Check if divide by 3 & 5
                echo "fizz buzz"
            elif [[0 == "($x%5)"]]
            then
                # Check if divide by 5
                echo "buzz"
            elif [[0 == "($x%3)"]]
            then
                # Check if divide by 3
                echo "fizz"
            else
                echo "$x"
            fi
            x=$(( x + 1 ))
        done


Il y a 4 différents groupes d'erreurs. Trois d'entre-eux peuvent être facilement repérés via
`ShellCheck <https://www.shellcheck.net>`_, un outil de vérification statique de code Bash. L'utilisation
systématique de ce genre d'outils vous évitera bon nombre d'erreurs fréquentes lors de la rédaction de code.

.. only:: staff

          #. Double crochets qui manque un espace

          #. == au lieu de -eq

          #. ! -z au lieu de -n

          #. < au lieu de -lt . Cette erreur n'est pas détectée par ShellCheck.
