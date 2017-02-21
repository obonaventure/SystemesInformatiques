.. -*- coding: utf-8 -*-
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


.. sectionauthor:: Aurélie Massart <aurelie.massart@student.uclouvain.be>

Questions à choix multiples
===========================

:task_id: sinf1252-revision


Question 1. Structure et allocation de mémoire avec `malloc(3)`_
----------------------------------------------------------------

Dans le langage C, l'allocation de zone mémoire se fait souvent avec `malloc(3)`_ 
Pour une structure chainée définie comme suit : 

.. code-block:: c


    struct list {
      int value;
      struct list *next;
    };


.. question:: revision-allocmemoire
   :nb_prop: 3
   :nb_pos: 1

   Quel fragment de code ci-dessous alloue correctement la zone mémoire pour une telle structure avec `malloc(3)`_ ?

   .. positive::

      .. code-block:: c

         struct list *l = (struct list *)malloc (sizeof(struct list));
         if(l == NULL)
         error("malloc");

   .. positive::

      .. code-block:: c

         struct list *l;
         l = (struct list *)malloc(sizeof(struct list));
         if(l == NULL)
         error("malloc");


   .. negative::

      .. code-block:: c

         struct list *l = malloc(sizeof(list));
         if(l == NULL)
         error("malloc");

      .. comment:: La variable ``list`` est non déclarée. Pour référencer la structure, il faut faire appel à ``struct list`` et non à ``list``. De plus, `malloc(3)`_ retourne un pointeur de type ``void *`` qui doit donc être casté en pointeur de type ``struct list *``.


   .. negative::

      .. code-block:: c

         struct list *l = (struct list) malloc (sizeof(struct list ));
         if(l == NULL)
         error("malloc");

      .. comment:: La variable ``l`` est de type ``struct list *`` et pas de type ``struct list``.

   .. negative::

      .. code-block:: c

         struct list *l = malloc (struct list);
         if(l == NULL)
         error("malloc");

      .. comment:: `malloc(3)`_ prend en argument la taille de la zone mémoire à allouer, et doit donc prendre en argument une expression commençant par ``sizeof``.


Question 2. Allocation et libération de mémoire sur une structure chainée
-------------------------------------------------------------------------

Pour une structure chainée définie comme suit : 

.. code-block:: c


    struct list {
      int value;
      struct list *next;
    };
    
    
.. question:: allocLib
   :nb_prop: 3
   :nb_pos: 1

   Un seul parmi les fragments de code ci-dessous est correct. Lequel ?

   .. positive::
      
      .. code-block:: c
      
      
         int main (int argc, char *argv[]) {

           struct list *node1 = (struct list *) malloc (sizeof (struct list));
           // premier noeud de la liste
           if (node1 == NULL)
             return (EXIT_FAILURE);


           struct list *node2 = (struct list *) malloc (sizeof (struct list));
           // deuxieme noeud de la liste
           if (node2 == NULL)
             return (EXIT_FAILURE);

           node2->value = 5;
           node2->next = NULL;
           node1->value = 2;
           node1->next = node2;
           // initialisation des noeuds de la liste


           while (node1 != NULL)
             {
               struct list *n = node1;
               node1 = node1->next;
               free (n);
               n = NULL;
             }
             // liberation de la memoire allouee

           return (EXIT_SUCCESS);
         }



   .. positive::
   
      .. code-block:: c
    

         int main (int argc, char *argv[]) {

           struct list *node1 = (struct list *) malloc (sizeof (struct list));
           // premier noeud de la liste
           if (node1 == NULL)
             return (EXIT_FAILURE);


           struct list *node2 = (struct list *) malloc (sizeof (struct list));
           // deuxieme noeud de la liste
           if (node2 == NULL)
             return (EXIT_FAILURE);
  
           node1->value = 2;
           node2->value = 5;
           node2->next = NULL;
           node1->next = node2;
           // initialisation des noeuds de la liste


           while (node1 != NULL)
             {
               struct list *n = node1;
               node1 = node1->next;
               free (n);
               n = NULL;
             }
             // liberation de la memoire allouee
  
           return (EXIT_SUCCESS);
         }  



   .. negative::
   
      .. code-block:: c
      
      
         int main (int argc, char *argv[]) {

           struct list *node1 = (struct list *) malloc (sizeof (struct list));
           // premier noeud de la liste
           if (node1 == NULL)
             return (EXIT_FAILURE);

   
          struct list *node2 = (struct list *) malloc (sizeof (struct list));
           // deuxieme noeud de la liste
           if (node2 == NULL)
             return (EXIT_FAILURE);


           node2->value = 5;
           node2->next = NULL;
           node1->value = 2;
           node1->next = node2;
           // initialisation des noeuds de la liste


           free(node1);
           // liberation de la memoire allouee

           return (EXIT_SUCCESS);
 
         }



      .. comment:: La mémoire n'est pas bien libérée. L'appel à `free(3)`_ ne va libérer que la mémoire associée au premier noeud de la liste.

   .. negative::
   
      .. code-block:: c



         int main (int argc, char *argv[]) {

           struct list *node1 = (struct list *) malloc (sizeof (struct list));
           // premier noeud de la liste
           if (node1 == NULL)
             return (EXIT_FAILURE);


           struct list *node2 = (struct list *) malloc (sizeof (struct list));
           // deuxieme noeud de la liste
           if (node2 == NULL)
             return (EXIT_FAILURE);

           node2->value = 5;
           node2->next = NULL;
           node1->value = 2;
           node1->next = node2;
           // initialisation des noeuds de la liste


           while (node1->next != NULL)
             {
               struct list *n = node1;
               node1 = node1->next;
               free (n);
               n = NULL;
             }
             // liberation de la memoire allouee

            return (EXIT_SUCCESS);
         }



      .. comment:: la mémoire n'est pas bien libérée. La boucle while se termine quand ``node->next`` vaut NULL et donc, la mémoire allouée pour le dernier élément de la liste ne sera pas libérée.

   .. negative::
   
      .. code-block:: c
   

         int main (int argc, char *argv[]) {

           struct list *node1 = (struct list *) malloc (sizeof (struct list));
           // premier noeud de la liste

           struct list *node2 = (struct list *) malloc (sizeof (struct list));
           // deuxieme noeud de la liste

           node2->value = 5;
           node2->next = NULL;
           node1->value = 2;
           node1->next = node2;
           // initialisation des noeuds de la liste


           while (node1 != NULL)
             {
               struct list *n = node1;
               node1 = node1->next;
               free (n);
               n = NULL;
             }
             // liberation de la memoire allouee

           return (EXIT_SUCCESS);
         }

      .. comment:: les valeurs de retour des pointeurs alloués avec `malloc(3)`_ n'ont pas été vérifiées.

   .. negative::
   
      .. code-block:: c


         int main (int argc, char *argv[]) {

           struct list *node1 = (struct list *) malloc (sizeof (struct list));
           // premier noeud de la liste
           if (node1 == NULL)
             return (EXIT_FAILURE);


           struct list *node2 = (struct list *) malloc (sizeof (struct list));
           // deuxieme noeud de la liste
           if (node2 == NULL)
             return (EXIT_FAILURE);

           node2->value = 5;
           node2->next = NULL;
           node1->value = 2;
           node1->next = node2;
           // initialisation des noeuds de la liste


           while (node1 != NULL)
             {
               struct list n = node1;
               free (n);
               n = NULL;
               node1 = node1->next;
             }
             // liberation de la memoire allouee

           return (EXIT_SUCCESS);
         }



      .. comment:: la variable ``n`` est de type ``struct list`` et ne peut donc pas être assignée à la valeur de la variable ``node1`` qui n'est pas du même type





.. include:: ../../../links.rst
.. include:: ../../../man_links.rst
.. include:: ../../../incl_links.rst


