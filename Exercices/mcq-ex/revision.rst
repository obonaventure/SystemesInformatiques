.. -*- coding: utf-8 -*-
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


.. Les lignes qui commencent par .. sont des commentaires ou des commandes restructuredtext. Celle-ci est un commentaire

.. Si vous proposez une ou des questions, mettez à jour l'information ci-dessous

.. sectionauthor:: Jean Tartempion <email>

Questions à choix multiples
===========================

.. La ligne ci-dessous identifie le numéro du groupe de question et ne devrait pas être modifiée

:task_id: sinf1252-revision

.. Toute question a un titre

Question 1. Conversion de types
-------------------------------

.. Si votre question comprend plusieurs paragraphe d'introduction, placez ces paragraphes avant de définir la question. Commencez votre paragraphe en première colonne pour éviter toute surprise avec les indentations.

En C tout comme dans des langages comme Java, il est possible de convertir des nombres d'un type primitif vers un autre. Cependant, alors que le compilateur Java vérifie si la conversion est sans risque, le compilateur C ne fait aucune vérification et suppose que si le programmeur a effectué une conversion explicite entre types, il a pris ses précautions. Sur une architecture où les types de données sont stockés comme suit :

.. Ceci est un exemple de code-source en C. Notez que le code est aligné sur la quatrième colonne comme le caractère c

.. code-block:: c

   // char			1 octet(s)
   // unsigned char		1 octet(s)
   // short			2 octet(s)
   // unsigned short		2 octet(s)
   // int			4 octet(s)
   // unsigned int		4 octet(s)

   int i;
   short s;
   long l;
   char c;
   unsigned int ui;
   unsigned char uc;
   unsigned long ul;
   unsigned short us;

.. Cette directive définit la question à choix multiples. Elle a un identifiant que vous devez choisir et qui doit être unique. Deux paramètres sont définis : nb_prop est le nombre de propositions qui sont présentées par le javascript (3 est un minimum, mais vous pouvez en proposer plus). nb_pos est le nombre de propositions positives qui sont présentées par le javascript. Si nb_pos > 1, alors la formulation de votre question doit demander à l'étudiant de sélectionner toutes les réponses correctes.

.. Une question doit nécessairement contenir un paragraphe de texte. Sinon, la compilation échouera. Pensez à aligner le paragraphe contenant la question en quatrième colonne 

.. question:: revision-conversiontypes
   :nb_prop: 3
   :nb_pos: 1

   Un seul des fragments de code ci-dessous contient des conversions de type qui sont sans risque. Lequel ?

   .. positive::

      .. code-block:: c

         i=(int ) s;
         s=(short) uc;
         l=(long )i;

.. la directive positive permet de spécifier une réponse positive. Celle-ci peut contenir un paragraphe ou une autre directive restructured text (dans cet exemple du code). Pensez à aligner le contenu de la directive positive sur la huitième colonne pour éviter tout problème d'indentation. 

.. une deuxième réponse positive qui est aussi correcte.

   .. positive::

      .. code-block:: c

         ui=(unsigned int) us;
         s=(short) c;
         ul=(unsigned long )ui;

.. une première réponse négative. Notez que le commentaire permet à l'étudiant d'apprendre de ses erreurs. Celui-ci est tout aussi important que la réponse négative qui est proposée. Veillez à respecter l'alignement de la directive comment sur la huitième colonne (caractère n de negative)

   .. negative::

      .. code-block:: c

         ui=(unsigned int ) s;
         us=(unsigned short) uc;
         l=(long )i;

      .. comment:: Si ``s`` est négatif, la conversion en ``unsigned int`` risque de poser problème.

.. Dans l'exemple ci-dessous, le commentaire contient un paragraphe complet. Son indentation est alignée sur la onzième colonne.

   .. negative::

      .. code-block:: c

         i=(int ) us;
         us=(unsigned short) i;
         l=(long )c;

      .. comment:: 

         La conversion d'un ``int`` en un ``unsigned short`` risque de poser problème.

   .. negative::

      .. code-block:: c

         ui=(int) s;
         s=(short) c;
         ul=(unsigned long )ui;

      .. comment:: La première conversion risque de poser des problèmes.


.. Ces include vous permettent de charger les liens vers les pages de manuel et les fichiers include standard de Linux auxquels vos commentaires et vos questions peuvent bien entendu faire appel

.. include:: ../links.rst
.. include:: ../man_links.rst
.. include:: ../incl_links.rst
