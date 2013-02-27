.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. _valgrind-ref:

Valgrind
--------

Plusieurs outils en informatique peuvent vous aider à localiser des bugs dans vos programmes. Parmi ceux-ci, voici deux outils particulièrement utiles pour les problèmes liés à la mémoire :
 
 * `valgrind(1)`_ vous permet de détecter des erreurs liés à la gestion de la mémoire (`malloc(3)`_, `free(3)`_,...)
 * `gdb(1)`_ permet de voir ce qui se passe "à l'intérieur" de votre programme et comment les variables évoluent.

Le site http://www.cprogramming.com/debugging/ vous donne des techniques de débuggage plus détaillées et explique `valgrind(1)`_ et `gdb(1)`_ plus en détails.

Valgrind permet de détecter des erreurs liées à la gestion de la mémoire dans vos programmes. Pour utiliser valgrind, lancez la commande `valgrind(1)`_ avec votre exécutable comme argument:

	.. code-block:: console

		valgrind --leak-check=yes [my binary]

Parmi les erreurs que valgrind est capable de détecter nous avons:
 
	* Mémoire non-désallouée: Lors d'un appel à `malloc(3)`_, vous obtenez un pointeur vers une zone de mémoire allouée. Si vous "perdez" la valeur de ce pointeur, vous n'avez plus le moyen de libérer cette zone de mémoire. Essayez `valgrind(1)`_ avec le petit programme :download:`src/nofree.c`
	* Désallouer deux fois la même zone de mémoire: Si vous appelez deux fois `free(3)`_ sur la même zone de mémoire, `valgrind(1)`_ va détecter cette erreur. Essayez-le avec le petit programme  :download:`src/twofree.c`
	* Accès en dehors des limites d'une zone mémoire: Si vous allouez une zone de mémoire d'une certaine taille (par exemple un table de 10 chars) et que vous accèdez à une adresse qui excède cette zone (par exemple vous accèdez au 11ième élément) vous aurez probablement une ``Segmentation fault``. Valgrind permet de détecter ces erreurs et indique l'endroit dans votre code où vous faites cet accès. Essayez-le avec le petit programme :download:`src/outofbounds.c`

On vous encourage à lancer `valgrind(1)`_ sur votre projet pour vérifier que vous n'avez pas introduit de memory-leaks sans le vouloir. `valgrind(1)`_ ne remplace pas une écriture attentive du code mais peut permettre de détecter rapidement certaines erreurs courantes. Vous trouverez plus de détails sur les liens suivants:
 
	* http://www.cprogramming.com/debugging/valgrind.html
	* http://valgrind.org


Détecter les deadlocks avec ``valgrind``
----------------------------------------

`valgrind(1)`_ contient des outils qui vont au-delà des simples tests de l'allocation de la mémoire. Notamment l'outil ``helgrind`` permet de détecter des deadlocks. Utilisez ``helgrind`` sur le petit programme :download:`/Outils/src/thread_crash.c` en faisant:

        .. code-block:: console

                $ valgrind --tool=helgrind [my binary]
                
                ==24314== Helgrind, a thread error detector
                ==24314== Copyright (C) 2007-2010, and GNU GPL'd, by OpenWorks LLP et al.
                ==24314== Using Valgrind-3.6.1-Debian and LibVEX; rerun with -h for copyright info
                ==24314== Command: ./thread_crash
                ==24314==
                ==24314== Thread #2 was created
                ==24314==    at 0x512E85E: clone (clone.S:77)
                ==24314==    by 0x4E36E7F: do_clone.constprop.3 (createthread.c:75)
                ==24314==    by 0x4E38604: pthread_create@@GLIBC_2.2.5 (createthread.c:256)
                ==24314==    by 0x4C29B23: pthread_create_WRK (hg_intercepts.c:257)
                ==24314==    by 0x4C29CA7: pthread_create@* (hg_intercepts.c:288)
                ==24314==    by 0x400715: main (in /home/christoph/workspace/SINF1252/SINF1252/2012/S6/src/thread_crash)
                ==24314==
                ==24314== Thread #2: Exiting thread still holds 1 lock
                ==24314==    at 0x4E37FB6: start_thread (pthread_create.c:430)
                ==24314==    by 0x512E89C: clone (clone.S:112)

Plus d'informations sur:
        * http://valgrind.org/docs/manual/hg-manual.html
