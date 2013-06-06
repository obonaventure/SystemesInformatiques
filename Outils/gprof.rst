.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. _gprof:

Profiling de code
-----------------


Lorsque l'on cherche à optimiser les performances de programmes écrits en C, il est utile de les exécuter à travers un profiler tel que `gprof(1)`_. Ce profiler permet de collecter des statistiques sur les fonctions les plus utilisées à l'intérieur du programme. Ce sont les fonctions qu'il faudra optimiser pour améliorer les performances. De nombreux articles décrivent les principes de base de l'utilisation de `gprof(1)`_. Un bon article pour démarrer est [Honeyford2006]_. `oprofile <http://oprofile.sourceforge.net/>`_ est un profiler plus puissant que `gprof(1)`_ mais malheureusement plus difficile à utiliser.
