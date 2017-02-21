.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Exercices
---------

#. En utilisant `signal(2)`_, écrivez une fonction C ``sig_ignored`` qui prend comme argument un numéro de signal et retourne ``true`` si le signal passé en argument est ignoré par le processus et ``false`` sinon.

   .. only:: staff

      Il suffit de tester la valeur de retour de signal. sigaction est une autre possibilité

#. A votre avis, pourquoi le système d'exploitation refuse-t-il l'exécution de la ligne ``signal(SIGKILL,SIG_IGN)`` ?

   .. only:: staff

      Bien évidemment pour garantir qu'il sera toujours possible de tuer un processus.

#. Sachant qu'en tapant `Ctrl-C` durant l'exécution d'un processus le shell envoie un signal ``SIGINT`` à ce processus, comment feriez-vous pour qu'un de vos programmes puisse survivre à `Ctrl-C` ?

   .. only:: staff

      Il faut évidemment définir un handler pour SIGINT et traiter ce signal, ce n'est pas très difficile à faire

#. Le programme :download:`/Programmes/src/alarm.c` que nous avons utilisé pour illustrer l'appel système `alarm(2)`_ contient une condition de course qui peut dans certains cas empêcher l'interruption de l'appel système `read(2)`_. Un étudiant propose de résoudre ce problème en utilisant une variable modifiée par la fonction de traitement de ``SIGALRM``. Que pensez-vous du programme :download:`/Programmes/src/alarm3.c` ?

   .. only:: staff

      Cette solution n'est pas fiable car il est possible que le processus aie été bloqué juste après l'exécution du if mais juste avant l'appel à read

#. La page de manuel `signal(7)`_ définit les signaux suivants :

   - ``SIGSYS``
   - ``SIGPIPE``

   Expliquez dans quels cas ces deux signaux peuvent être générés et délivrés à un processus.

   .. #. Les constantes ``SIG_DFL`` et ``SIG_IGN`` utilisées par `signal(2)`_ sont-elles des entiers ou un autre type?

#. Unix définit un signal ``SIGCHLD`` qui est envoyé lorsqu'un fils se termine. Quel est l'intérêt d'un tel signal pour le processus père?

   .. only:: staff

      Cela permet au père de savoir quand il doit effectuer un wait.

#. Un processus a exécuté une fonction de traitement du signal ``SIGUSR1`` et une autre fonction pour traiter le signal ``SIGUSR2``. La fonction qui traite ``SIGUSR1`` est une fonction assez complexe qui prend des centaines d'instructions. Que se passe-t-il si pendant que le processus est en train de traiter le signal ``SIGUSR1``, un autre processus lui envoie :

   - ``SIGUSR1``
   - ``SIGUSR2``

#. Considérons la fonction de gestion des signaux suivante :

   .. code-block:: c

      static void sig_handler(int signum) {
          char *msg="Reçu signal \n";
          write(STDERR_FILENO,msg,strlen(msg));
      }

   Cette fonction utilise l'appel système `write(2)`_ qui peut modifier la variable ``errno`` en cas d'erreur. Modifiez-la de façon à ce que toute modification à ``errno`` n'affecte pas l'utilisation de ``errno`` dans le programme en cours d'exécution.

#. Dans les programmes :download:`/Programmes/src/process-sem-before.c` et :download:`/Programmes/src/process-sem-after.c`, on a choisi de créer le sémaphore dans un processus avec `sem_open(3)`_ et de le supprimer avec `sem_unlink(3)`_ dans un autre processus. Est-ce possible de créer et supprimer le sémaphore dans le même processus ?

#. Un processus ``P`` ouvre le fichier ``fichier`` avec l'appel système `open(2)`_. Celui-ci est associé au descripteur ``fd``. Ensuite, le processus utilise `fork(2)`_ pour créer un processus fils.

   - représenter les open-file objects utilisés
   - le père et le fils peuvent-ils lire sur ``fd`` ?
   - le processus fils utilise l'appel système `chmod(2)`_ pour rendre le fichier inaccessible en écriture et lecture. Après cette opération, le père et le fils peuvent-ils lire sur ``fd`` ?
   - le père ferme le descripteur ``fd``. Après cette opération, le père et le fils peuvent-ils lire sur ``fd`` ?
   - le fils exécute `unlink(2)`_ sur le fichier. Après cette opération, le père et le fils peuvent-ils lire sur ``fd`` ?

#. Même question que ci-dessus, mais en remplaçant le fichier par un sémaphore nommé et `open(2)`_ par `sem_open(3)`_ ?

#. Le programme :download:`/Programmes/src/miniprojet.c` utilise des sémaphores nommés pour synchroniser la production/consommation entre deux processus. Le processus père crée le fichier ``my_file.txt`` y écrit une valeur. Le processus fils est chargé de lire la donnée présente dans le fichier et l'affiche à la console. Ce programme tourne à l'infini et donc il faut l'arrèter avec la commande ``Ctrl-C``. Malheureusement dans ce cas les sémaphores nommés ne sont pas supprimés correctement. Après avoir terminé le programme  avec `Ctrl-C` vous verrez qu'il reste des sémaphores dans ``/dev/shm/``.

   Comment modifier ce programme pour gèrer la terminaison correcte des processus lors de la pression sur ``Ctrl-C``. Pour ce faire, vous devez modifier le programme de façon à ce qu'il libère toutes les ressources allouées avant de se terminer. Ceci peut se faire en traitant le signal envoyé au processus par le shell lorsque l'utilisateur presse ``Ctrl-C``.

#. Faites les deux exercices INGInious sur `les signaux <https://inginious.info.ucl.ac.be/course/LSINF1252/signaux>`_ et `le sleep <https://inginious.info.ucl.ac.be/course/LSINF1252/sleep>`_.

