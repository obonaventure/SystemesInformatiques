.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices
=========

1. Dans quels cas l'appel système `fork(2)`_ peut-il retourner une erreur? Pourriez-vous construire un programme dans lequel `fork(2)`_ retourne une erreur ?

 .. only:: staff

    Il suffit de créer trop de processus

2. Dans quels cas l'appel système `wait(2)`_ peut-il retourner une erreur ? Pourriez-vous écrire un petit programme dans lequel `wait(2)`_ retourne une erreur ?

 .. only:: staff

    Voir page de manuel. Un exemple est lorsqu'il n'y a plus de processus fils

3. L'appel système `fork(2)`_ retourne l'identifiant du processus fils dans le processus père. Imaginez qu'une variante de Unix choisisse d'implémenter `fork(2)`_ en retournant ``0`` dans le processus fils et ``1`` dans le processus père. Quel serait l'impact de cette modification pour un programme qui lance plusieurs processus fils ?

 .. only:: staff

    `waitpid(2)`_ ne pourrait plus fonctionner

4. Combien de processus sont créés lors de l'exécution du programme ci-dessous ?

 .. code-block:: c

    // ...
    fork();
    fork();
    // ...

 .. only:: staff

    le père crée un fils puis un second

    le premier fils crée également un fils

5. En supposant que le processus père a comme identifiant la valeur ``1252``, représentez graphiquement sous forme d'un arbre l'ensemble des processus créés par le programme ci-dessus en supposant que les identifiants de processus sont attribués séquentiellement par le :term:`kernel`.

6. L'appel système `fork(2)`_ est nécessaire au fonctionnement de Unix. Cependant, un programme qui abuse de `fork(2)`_ risque de perturber le fonctionnement du système. Que risque-t-il d'arriver si vous exécutez un programme qui par mégarde contient :

.. code-block:: c

   while(true) {
     fork();
     // ...
   }

Consultez les pages de manuel pour déterminer comment le système d'exploitation peut se protéger contre de telles `fork bomb <http://en.wikipedia.org/wiki/Fork_bomb>`_.

7. Comparez les performances de la création et la terminaison de threads et de processus en compilant et exécutant sur un ordinateur non chargé les programmes :download:`/Programmes/src/fork-perf.c` et :download:`/Programmes/src/pthread-perf.c`. Utilisez la commande `time(1posix)`_ pour mesurer le temps d'exécution de chacun des ces programmes qui créent 100000 processus ou threads. Expliquez vos résultats.

 .. only:: staff

    Essayez de discuter avec les étudiants des avantages et inconvénients des threads et des processus pour voir dans quels cas un processus est plus utile qu'un thread. A ce stade, ils n'ont vu aucun mécanisme de partage entre processus et ils n'ont pas encore vu les fichiers. Le seul avantage des processus est que si le père crashe son fils ne crashe pas nécessairement, alors que dans les threads un crash provoque le crash de tous les threads du processus.

8. Compilez le programme :download:`/Programmes/src/fork-zombie.c`. Ce programme crée un processus mais le processus père attend une minute pour récupérer sa valeur de retour. Lancez ce programme en tâche de fond (voir section outils) et utilisez `ps(1)`_ ou consultez ``/proc/``

9. La librairie standard comprend une fonction `system(3posix)`_ qui permet l'exécution d'une commande du shell. Ainsi, la ligne ``system("for f in {1..3} ; do echo $f ; done")`` va provoquer un appel au shell `bash(1)`_ qui va exécuter la commande passé en argument et donc afficher trois lignes contenant chacune un nombre sur la sortie standard. Quels sont les appels systèmes utilisées par une implémentation de cette fonction `system(3posix)`_ ?

10. Quelles différences et similitudes voyez-vous entre :

    - `pthread_create(3)`_ et `fork(2)`_
    - `pthread_join(3)`_ et `waitpid(2)`_


11. La commande `strace(1)`_ permet de tracer tous les appels systèmes faits par un programme. Recompilez un programme d'exemple et essayer d'identifier les principaux appels systèmes qui sont utilisés par ce programme. Les paramètres ``-c``, ``-t`` et ``-e`` peuvent être utiles pour explorer le comportement d'un programme et avoir une idée des appels systèmes qu'il effectue.

12. La commande `pstree(1)`_ permet de visualiser sous forme d'arbre l'ensemble des processus actifs sur un ordinateur Linux. Exécutez `pstree(1)`_ et identifiez quels sont les processus qui sont les ancêtres de votre commande.

13. Un shell tel que `bash(1)`_ permet à l'utilisateur de lancer plusieurs programmes simultanément. Par exemple, il est possible de lancer un programme en background (ou tâche de fond en français) en le suffixant avec le caractère ``&``. On peut faire de même en tapant `Ctrl-Z` (les touches `Ctrl` et `Z` simultanément) pendant qu'un programme s'exécute. Cela peut être utile pour taper une commande pour par exemple voir l'état du système pendant l'exécution du programme. Il est possible de revenir à l'exécution du programme via la commande `fg(1)`. La commande `jobs(1posix)`_ permet de lister les processus qui sont actuellement exécutés par le shell en tâche de fond. La section `JOB CONTROL` du manuel de `bash(1)`_ fournit plus d'informations à ce sujet.

14. Le répertoire ``/proc`` contient une image de la table des processus maintenue par le :term:`kernel` et d'autres structures de données maintenues par le :term:`kernel`. Compilez le programme :download:`/Programmes/src/fork-pthread.c` qui lance un processus fils puis crée un thread à l'intérieur du processus père. Lancez ce programme en background via `bash(1)`_ et observez les entrées relatives au père, au fils et au thread créé par le processus père dans ``/proc``.

15. Faites l'exercice sur les shell sur `IngiNIOUS <https://inginious.info.ucl.ac.be/course/LSINF1252/shell>`_

