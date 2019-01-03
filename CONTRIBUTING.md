Format des fichiers
===================


Les niveaux de titre. On utilise les mêmes niveaux de titres que pour la documentation python, c'est-à-dire ::

 ######
 Partie
 ######

 ********
 Chapitre
 ********

 Section
 =======

 Sous-section
 ------------

 Sous-sous section
 ^^^^^^^^^^^^^^^^^

 Paragraphe
 """"""""""

Les figures sont de préférence en format svg, mais une figure en format png est possible aussi, elles seront converties par après. Les figures se trouvent dans un répertoire svg pour chaque semaine.

Les liens sont définis dans le fichier links.rst qui est importé par tous les fichiers restructured text.

Les sources sont incluses dans un répertoire src pour chaque semaine.

La bibliographie sera construite semaine après semaine. Dans un premier temps, on a une bibliographie globale. Si possible, elle utilisera le format ACM Ref avec des liens hypertext vers l'article ou le livre sur google books pour faciliter l'accès aux étudiants.


Liens vers les pages de manuel :
- utiliser la version de Linux en salle et générer la version HTML avec un style correct. Deux possibilités
  - utiliser man2html
  - utiliser mandoc

Liens vers les fichiers include :
- utiliser les include qui sont ceux de linux en salle
  faire les liens directement pour les rendre accessible depuis le livre directement
  mandoc ne fonctionne pas correctement
  man2html semble être suffisant, mais il faudrait faire un css un peu comme man7.org

Exécution de programmes :
 - utiliser l'extension sphinx http://packages.python.org/sphinxcontrib-programoutput/
 - utiliser un fichier .out et faire un literal include de ce fichier


Exercices
=========

1. Exercices de type QCM

Voir si c'est faisable de faire une production sphinx dédiée. Si oui, include l'explication ici

2. Exercices de type question à trous

   Fournir une partie du code source et faire compléter par les étudiants. Type de construction restructured text à utilise :


 .. literalinclude:: example.c
    :language: c
    :emphasize-lines: 12,15-18
    :encoding: utf-8
    :lines: 1,3,5-10,20-

Il est aussi possible d'utiliser les options
start-after and end-before  qui prennent comme argument un string pour indiquer le texte qui est inclus. Cela permet d'avoir une construction du style.

   programme
   affiché
   ///AAA
   pas affiché
   ///BBB
   à affiché dans deuxième partie

Cela permet d'avoir du code C qui fonctionne et que l'on peut tester et dont on n'affiche qu'une partie dans le livre.

