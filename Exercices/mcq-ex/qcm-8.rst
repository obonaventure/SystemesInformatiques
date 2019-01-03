.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_





Questions à choix multiples
===========================

:task_id: sinf1252-8

La matière couverte cette semaine couvre les processus.

 - `Les processus <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Threads/processus.html>`_

Question 1. `fork(2)`_
-----------------------

L'appel système `fork(2)`_ permet de créer une copie du processus courant. Un étudiant a écrit le fragment de code ci-dessous se trouvant dans la fonction ``main``:

.. code-block:: c

  int n=...
  for(int i=0; i<n ; i++) {
    printf("i=%d\n",i);
    pid_t pid;
    pid=fork();
    if (pid==-1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    else {
      if(pid!=0) {
          printf("Running in %d\n",pid);
      }
    }
  }
  return(EXIT_SUCCESS);

.. question:: fork
   :nb_prop: 3
   :nb_pos: 1

   Lors de l'exécution de ce programme, combien de processus sont créés en fonction de la valeur de ``n`` ?

   .. positive::

      Lorsque ``n`` est initialisé à ``2``, quatre processus sont créés.

      .. comment::

         Le premier processus démarre son exécution. Il exécute `fork(2)`_. Un nouveau processus est donc créé. Ces deux processus exécutent à leur tour `fork(2)`_ et deux processus supplémentaires sont donc créés.

   .. positive::

      Lorsque ``n`` est initialisé à ``3``, huit processus sont créés.

      .. comment::

         Le premier processus démarre son exécution. Il exécute `fork(2)`_. Un nouveau processus est donc créé. Ces deux processus exécutent à leur tour `fork(2)`_ et deux processus supplémentaires sont donc créés. Chacun de ces quatre processus exécute à son tour `fork(2)`_ et il y a donc huit processus au total.

   .. negative::

      Lorsque ``n`` est initialisé à ``2``, deux processus sont créés.

      .. comment::

         Le premier processus démarre son exécution. Il exécute `fork(2)`_. Un nouveau processus est donc créé. Chacun de ces deux processus poursuit son exécution et la valeur de ``i`` est incrémentée.

   .. negative::

      Lorsque ``n`` est initialisé à ``2``, trois processus sont créés.

      .. comment::

         Le premier processus démarre son exécution. Il exécute `fork(2)`_. Un nouveau processus est donc créé. Chacun de ces deux processus poursuit son exécution et la valeur de ``i`` est incrémentée.

   .. negative::

      Lorsque ``n`` est initialisé à ``3``, trois processus sont créés.

      .. comment::

         Le premier processus démarre son exécution. Il exécute `fork(2)`_. Un nouveau processus est donc créé. Chacun de ces deux processus poursuit son exécution et la valeur de ``i`` est incrémentée.

   .. negative::

      Lorsque ``n`` est initialisé à ``3``, quatre processus sont créés.

      .. comment::

         Le premier processus démarre son exécution. Il exécute `fork(2)`_. Un nouveau processus est donc créé. Chacun de ces deux processus poursuit son exécution et la valeur de ``i`` est incrémentée.

Question 2. `execve(2)`_
------------------------

.. question:: execve
   :nb_prop: 3
   :nb_pos: 1

   Parmi les extraits de programme ci-dessous, lequel est un appel correct à `execve(2)`_ pour lancer le programme ``/bin/echo`` avec comme arguments ``-n`` et ``SINF1252`` ?

   .. positive::


      .. code-block:: c

         char *arguments[]={"echo", "-n", "SINF1252", NULL};
         char *environnement[]={"LANG=fr",NULL};
         int err=execve("/bin/echo", arguments, environnement);
         if(err!=0) {
           perror("execve");
           exit(EXIT_FAILURE);
         }

   .. positive::

      .. code-block:: c


          char prog[]="echo";
          char param1[]="-n";
          char param2[]="SINF1252";
          char *arguments[4];
          arguments[0]=prog;
          arguments[1]=param1;
          arguments[2]=param2;
          arguments[3]=NULL;
          char *environnement[]={"LANG=fr", NULL};
          int err=execve("/bin/echo", arguments, environnement);
          if(err!=0) {
            perror("execve");
            exit(EXIT_FAILURE);
          }


   .. negative::


      .. code-block:: c

         char arguments[]={"echo", "-n", "SINF1252", NULL};
         char environnement[]={"LANG=fr",NULL};
         int err=execve("/bin/echo", arguments, environnement);
         if(err!=0) {
           perror("execve");
           exit(EXIT_FAILURE);
         }


      .. comment::

         Les deuxième et troisième arguments à `execve(2)`_ doivent être de type ``char *arg[]``.

   .. negative::

      .. code-block:: c


         char prog[]="echo";
         char param1[]="-n";
         char param2[]="SINF1252";
         char *arguments[4];
         arguments[0]=prog;
         arguments[1]=param1;
         arguments[2]=param2;
         arguments[3]=NULL;
         char *environnement[]={"LANG=fr"};
         int err=execve("/bin/echo", arguments, environnement);
         if(err!=0) {
           perror("execve");
           exit(EXIT_FAILURE);
         }

      .. comment::

         Les deuxième et troisième arguments à `execve(2)`_ doivent être de type ``char *arg[]``.

   .. negative::

      .. code-block:: c


         char prog[]="echo";
         char param1[]="-n";
         char param2[]="SINF1252";
         char *arguments[3];
         arguments[0]=prog;
         arguments[1]=param1;
         arguments[2]=param2;
         char *environnement[]={"LANG=fr"};
         int err=execve("/bin/echo", arguments, environnement);
         if(err!=0) {
           perror("execve");
           exit(EXIT_FAILURE);
         }

      .. comment::

         Le dernier élément des tableaux de pointeurs ``argv` et ``environnement`` doivent obligatoirement contenir ``NULL``. Sans cela, il n'est pas possible de déterminer le nombre d'éléments dans ces tableaux.

   .. negative::

      .. code-block:: c

         char *arguments[]={"echo", "-n", "SINF1252"};
         char *environnement[]={"LANG=fr"};
         int err=execve("/bin/echo", arguments, environnement);
         if(err!=0) {
           perror("execve");
           exit(EXIT_FAILURE);
         }

      .. comment::

         Le dernier élément des tableaux de pointeurs ``argv` et ``environnement`` doivent obligatoirement contenir ``NULL``. Sans cela, il n'est pas possible de déterminer le nombre d'éléments dans ces tableaux.


Question 3. `execve(2)`_
------------------------

.. question:: execve2
   :nb_prop: 3
   :nb_pos: 1

   L'appel système `execve(2)`_ permet d'exécuter un programme en remplaçant le programme en cours d'exécution par celui se trouvant sur disque dont le nom est spécifié. Un étudiant a écrit le programme ci-dessous pour tester `execve(2)`_ :

   .. code-block:: c

      #include <stdio.h>
      #include <stdlib.h>
      #include <unistd.h>

      extern char **environ;

      int main (int argc, char *argv[])  {

       int n=...
       int i=0;
       for(i=0;i<n;i++) {
         sleep(1);
         printf("%d\n",i);
         int err=execve(argv[0], argv, environ);
         if(err!=0) {
           perror("execve");
           exit(EXIT_FAILURE);
         }
       }
       return(EXIT_SUCCESS);
      }

   .. positive::

      Lorsque ``n`` est initialisé à ``3``, le programme ne s'arrête jamais et affiche :

      .. code-block:: console

         0
         0
         0
         ...

      .. comment::

         Lors de l'exécution de `execve(2)`_, le programme est remplacé par lui-même puisque ``argv[0]`` contient toujours le nom de l'exécutable qui est en train d'être exécuté. Ce programme redémarre son exécution au début de la fonction ``main``...

   .. positive::

      Lorsque ``n`` est initialisé à ``2``, le programme ne s'arrête jamais et affiche :

      .. code-block:: console

         0
         0
         0
         ...


      .. comment::

         Lors de l'exécution de `execve(2)`_, le programme est remplacé par lui-même puisque ``argv[0]`` contient toujours le nom de l'exécutable qui est en train d'être exécuté. Ce programme redémarre son exécution au début de la fonction ``main``...



   .. negative::

      Lorsque ``n`` est initialisé à ``3``, le programme affiche :

      .. code-block:: console

         0
         1
         2


      .. comment::

         Lors de l'exécution de `execve(2)`_, le programme est remplacé par lui-même puisque ``argv[0]`` contient toujours le nom de l'exécutable qui est en train d'être exécuté. Ce programme redémarre son exécution au début de la fonction ``main``...

   .. negative::

      Lorsque ``n`` est initialisé à ``2``, le programme affiche :

      .. code-block:: console

         0
         1


      .. comment::

         Lors de l'exécution de `execve(2)`_, le programme est remplacé par lui-même puisque ``argv[0]`` contient toujours le nom de l'exécutable qui est en train d'être exécuté. Ce programme redémarre son exécution au début de la fonction ``main``...

   .. negative::

      Lorsque ``n`` est initialisé à ``2``, l'appel à `execve(2)`_ est erroné et le programme s'arrête.

      .. comment::

         L'appel à `execve(2)`_ est tout à fait correct, même si il n'est pas recommandé d'utiliser `execve(2)`_ de cette façon...

   .. negative::


      Lorsque ``n`` est initialisé à ``3``, l'appel à `execve(2)`_ est erroné et le programme s'arrête.

      .. comment::

         L'appel à `execve(2)`_ est tout à fait correct, même si il n'est pas recommandé d'utiliser `execve(2)`_ de cette façon...



Question 4. Utilisation de `waitpid(2)`_
----------------------------------------

.. question:: waitpid
   :nb_prop: 3
   :nb_pos: 1

   L'appel système `waitpid(2)`_ permet à un processus d'attendre les valeurs de retour de ses processus fils. Un étudiant a écrit un programme qui lance de nombreux processus et veut faire une boucle qui permet de récupérer tous les processus fils qu'il a créé. Parmi les fragments de code ci-dessous, un seul est correct. Lequel ?


   .. positive::



      .. code-block:: c


          int fils;
          int done=false;
          while(!done) {
            int status;
            fils=waitpid(0,&status,0);
            if( (fils==-1) && (errno==ECHILD) )
              done=true;
          }

   .. positive::

      .. code-block:: c


          int fils;
          int done=false;
          while(!done) {
            int status;
            if( (waitpid(0,&status,0)==-1) && (errno==ECHILD) )
              done=true;
          }



   .. negative::


      .. code-block:: c


          int fils;
          int done=false;
          int status;
          while(waitpid(0,status,0)!=0) {
            if( (fils==-1) && (errno==ECHILD) )
              done=true;
          }


      .. comment::

         Le second argument de `waitpid(2)`_ est un pointeur vers un entier et non un entier.

   .. negative::


      .. code-block:: c


          int fils;
          int done=false;
          while(!done) {
            int status;
            fils=waitpid(getpid(),&status,0);
            if( (fils==-1) && (errno==ECHILD) )
              done=true;
          }

      .. comment::

         Lorsque le premier argument de `waitpid(2)`_ est un entier positif, il s'agit de l'identifiant du processus pour lequel `waitpid(2)`_ attend. Dans ce cas, `getpid(2)`_ retourne l'identifiant du processus qui existe `waitpid(2)`_ et un processus ne peut pas être un fils de lui-même.

Question 5. Récupération du résultat d'un processus avec `waitpid(2)`_
----------------------------------------------------------------------

.. question:: waitpid2
   :nb_prop: 3
   :nb_pos: 1

   Un étudiant souhaite récupérer le résultat du processus ``pid`` qu'il a créé en faisant `fork(2)`_ et l'afficher sur ``stdout``. Parmi les fragments de programmes ci-dessous, un seul est correct. Lequel ?

   .. positive::


      .. code-block:: c

         int status;
         int p=waitpid(pid,&status,0);
         if(p==-1) {
             perror("wait");
             exit(EXIT_FAILURE);
         }
         if(WIFEXITED(status)) {
           printf("Le processus a retourne %d\n",WEXITSTATUS(status));
         }


   .. negative::


      .. code-block:: c

         int status;
         int p=waitpid(pid,status,0);
         if(p==-1) {
             perror("wait");
             exit(EXIT_FAILURE);
         }
         printf("Le processus a retourne %d\n",WEXITSTATUS(status));

      .. comment::

         L'appel système `waitpid(2)`_ prend comme second argument un pointeur vers un ``int`` et non un `ìnt``.

   .. negative::


      .. code-block:: c

         int status;
         int p=waitpid(pid,&status,0);
         if(p==-1) {
             perror("wait");
             exit(EXIT_FAILURE);
         }
         printf("Le processus a retourne %d\n",p);

      .. comment::

         La valeur de retour de `waitpid(2)`_ indique si l'appel système s'est exécuté correctement ou non. Pour récupérer le statut du processus fils ``pid``, il faut utiliser la macro ``WEXITSTATUS``.

   .. negative::

      .. code-block:: c

         int *status;
         int p=waitpid(pid,status,0);
         if(p==-1) {
             perror("wait");
             exit(EXIT_FAILURE);
         }
         printf("Le processus a retourne %d\n",p);

      .. comment::

         La valeur de retour de `waitpid(2)`_ indique si l'appel système s'est exécuté correctement ou non. Pour récupérer le statut du processus fils ``pid``, il faut utiliser la macro ``WEXITSTATUS``. Le pointeur ``int * status`` doit pointer vers une zone mémoire allouée par malloc. Ici, il pointe vers ``NULL``.

