.. -*- coding: utf-8 -*-
.. Copyright |copy| 2014 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. raw:: html

  <script type="text/javascript" src="js/jquery-1.7.2.min.js"></script>
  <script type="text/javascript" src="js/jquery-shuffle.js"></script>
  <script type="text/javascript" src="js/rst-form.js"></script>
  <script type="text/javascript" src="js/prettify.js"></script>
  <script type="text/javascript">$nmbr_prop = 4</script>


===============
Onzième semaine
===============


La matière couverte cette semaine porte sur la mémoire virtuelle.

Question 1. Taille d'une page
-----------------------------

Laquelle des tailles ci-dessous correspond à une taille courante pour une page en mémoire virtuelle ?

.. class:: positive

- 4096 bytes


- 4 KBytes


.. class:: negative

- 4 bytes

- 32 bits

- 512 bytes

- 4096 bits

- 32 KBytes

- 4 MBytes

- 4 Kbits


Question 2. Table des pages
---------------------------

Un ordinateur expérimental utilise une table des pages à un seul niveau. Parmi les affirmations suivantes relatives au nombre d'entrées dans la table des pages, une seule est valide. Laquelle ?

.. class:: positive

- Si l'ordinateur utilise des adresses virtuelles sur 30 bits et des pages de 4 KBytes, alors la table des pages contient :math:`2^18` entrées

- Si l'ordinateur utilise des adresses virtuelles sur 30 bits et des pages de 1 KByte, alors la table des pages contient :math:`2^20` entrées


.. class:: negative

- Si l'ordinateur utilise des adresses virtuelles sur 32 bits et des pages de 4 KBytes, alors la table des pages contient :math:`2^18` entrées

- Si l'ordinateur utilise des adresses virtuelles sur 30 bits et des pages de 1 KByte, alors la table des pages contient :math:`2^18` entrées

- Si l'ordinateur utilise des adresses virtuelles sur 34 bits et des pages de 1 KByte, alors la table des pages contient :math:`2^18` entrées

- Si l'ordinateur utilise des adresses virtuelles sur 32 bits et des pages de 1 KByte, alors la table des pages contient :math:`2^20` entrées


Question 3. Bit de validité
---------------------------

Parmi les affirmations suivantes relatives au bit de validité utilisé dans la mémoire virtuelle, une seule est vraie. Laquelle

.. class:: positive

- lorsque le bit de validité d'une entrée de la table des pages est 'vrai', cela indique que la page correspondante se trouve en mémoire RAM

- Seules les pages dont le bit de validité est 'vrai' se trouvent en mémoire RAM 

.. class:: negative

- il y a un seul bit de validité pour une table des pages

 .. class:: comment

    Il y a un bit de validité par entrée de la table des pages

- le bit de validité est mis à 'faux' lorsqu'une donnée se trouvant dans une page est modifiée

- le bit de validité est toujours mis à 'vrai' dans la table des pages

- le bit de validité est mis à 'vrai' à chaque accès à une donnée se trouvant dans une page

Question 4. Création et suppression de pages
--------------------------------------------

Durant l'exécution d'un processus, certains événements peuvent provoquer la création de nouvelles pages en mémoire. Parmi les opérations ci-dessous, laquelle ne provoque surement pas la création de nouvelles pages en mémoire :

.. class:: positive

- l'exécution de `free(3)`_

- l'exécution de `waitpid(2)`_

.. class:: negative

- l'exécution de l'appel système `fork(2)`_

- l'exécution de l'appel système `execve(2)`_

- l'appel récursif à une fonction

- l'exécution de `malloc(3)`_

- la création d'un thread via la librairie POSIX



Question 5. Bits de contrôle
----------------------------


Chaque entrée de la table des pages contient plusieurs bits de contrôles relatifs à chaque page :

 - bit de validité
 - bit de modification
 - bit de reference

Considérons une mémoire virtuelle composée de 8 pages, numérotées de 0 à 7 par simplicité. Au démarrage du programme, les pages 0, 1, 2 et 7 sont utilisées. Les pages 0 à 3 contiennent les instructions du programme et la page 7 contient la pile. Les bits de modification et de référence sont remis à zéro puis le programme exécute les opérations suivantes :

 - modification (via des instructions se trouvant en page 1) d'une variable globale stockée dans la page 2
 - appel à une fonction qui alloue un tableau nécessitant 2 pages sur la pile. Les instructions de la fonction sont dans la page 1.
 
Après exécution de ce programme, quels sont les bits de contrôle de la table des pages ?

.. class:: positive

-
   - bit de validité vrai pour les pages 0, 1, 2, 5, 6 et 7 
   - bit de modification vrai pour les pages 2, 5, 6 et 7 
   - bit de référence vrai pour les pages 1, 2, 5, 6
   

.. class:: negative

-
   - bit de validité vrai pour les pages 0, 1, 2, 3, 4, 5, 6 et 7 
   - bit de modification vrai pour les pages 2, 5, 6 et 7 
   - bit de référence vrai pour les pages 1, 2, 5, 6, 7

-
   - bit de validité vrai pour les pages 5, 6 et 7 
   - bit de modification vrai pour les pages 5, 6 et 7 
   - bit de référence vrai pour les pages  5, 6 


-
   - bit de validité vrai pour les pages 0, 1, et 2 
   - bit de modification vrai pour les pages 5, 6 et 7 
   - bit de référence vrai pour les pages  1, 2


Question 5. Bits de contrôle
----------------------------

Parmi les affirmations suivantes, une seule est vraie. Laquelle

.. class:: positive

- Si lors d'un accès à la mémoire le bit de modification est mis à vrai, alors le bit de référence est aussi mis à vrai 

.. class:: negative

- Si lors d'un accès à la mémoire le bit de référence est mis à vrai, alors le bit de modification est aussi mis à vrai 

- Si lors d'un accès à la mémoire le bit de validité est mis à vrai, alors le bit de modification est aussi mis à vrai 

- Si lors d'un accès à la mémoire le bit de validité est mis à vrai, alors le bit de référence est aussi mis à vrai 



Question 6. Bits de permissions
-------------------------------

Parmi les affirmations suivantes, une seule est correcte. Laquelle ?

.. class:: positive

- Les pages contenant le code d'un programme ont `R-X` comme permissions tandis que les pages contenant le heap et le stack ont `RW-` comme permissions

- Les pages contenant  le heap et le stack ont `RW-` comme permissions tandis que les pages contenant le code ont `R-X` comme permissions

.. class:: negative

- Toutes les pages d'un programme doivent nécessairement avoir `RWX` comme permissions

- Toutes les pages de la pile d'un programme doivent nécessairement avoir `-WX` comme permissions

- Les pages de la pile d'un programme ont toujours `-W-` comme permissions

- Les pages contenant le code d'un programme ont toujours `--X` comme permissions


Question 7. Bits de contrôle
----------------------------

Parmi les affirmations suivantes relatives à l'exécution d'instruction en assembleur, une seule est correcte. Laquelle ?

.. class:: positive

- l'exécution de ``mov %ecx, 0x12345678`` provoque la modification de deux bits de référence et un bit de modification

- l'exécution de ``mov 4(%eax), %ecx`` provoque la modification de deux bits de référence et un bit de modification

.. class:: negative

- l'exécution de ``mov %ecx, 0x8765412`` provoque la modification d'un bit de référence et un bit de modification

- l'exécution de ``mov 8(%eax), %ebx`` provoque la modification d'un bit de référence et un bit de modification

- l'exécution de ``mov 8(%eax), %ebx`` provoque la modification de deux bits de référence et deux bits de modification

- l'exécution de ``add %eax, %ebx`` provoque la modification d'un bit de référence et un bit de modification

- l'exécution de ``j label`` provoque la modification de deux bits de référence

Question 8. TLB
---------------

Parmi les affirmations suivantes relatives au fonctionnement du TLB, une seule est correcte. Laquelle ?

.. class:: positive

- lors d'un accès en écriture à une page, les bits de modification et de référence sont mis à jour dans le TLB mais pas dans la table des pages

- lors d'un accès en lecture à une page, le bit de référence est mis à jour dans le TLB mais pas dans la table des pages

.. class:: negative

- les bits de contrôle stockés dans le TLB pour la page `p` sont toujours identiques aux bits de contrôle de la même page dans la table des pages

 .. class:: comment

    Les bits de contrôle stockés dans le TLB sont mis à jour à chaque accès à une page sans passer par la table des pages. Ils ne sont mis à jour dans la table des pages que lorsque l'entrée correspondant à une page retourne dans la table des pages.

- lors d'un accès en écriture à une page, les bits de modification et de référence sont mis à jour dans le TLB et dans la table des pages

- lors d'un accès en lecture à une page, le bit de référence est mis à jour dans le TLB et dans la table des pages



.. include:: ../../../links.rst
.. include:: ../../../man_links.rst
.. include:: ../../../incl_links.rst
