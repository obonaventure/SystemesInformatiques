Systèmes Informatiques
======================

Ce repository git est destiné à contenir les notes et exercices du cours de [Systèmes informatiques 1](http://www.uclouvain.be/cours-2014-LSINF1252) (C, Unix/Linux, ...) donné en deuxième année aux étudiants ingénieurs option informatique et aux étudiants en sciences informatiques de l'[UCL](http://www.uclouvain.be). Il sera mis régulièrement à jour et les étudiants sont encouragés à soumettre des bugs reports, envoyer des patches ( notamment pour la section relative aux outils) ou proposer de nouvelles questions à choix multiples.

Ce cours est écrit en restructured text et est distribué sous une licence creative commons
http://creativecommons.org/licenses/by-sa/3.0/fr/

Des versions HTML, pdf et epub sont disponibles via  http://sites.uclouvain.be/SystInfo

Compilation
-----------

Les notes sont écrites en [restructured text](http://docutils.sourceforge.net/rst.html) et peuvent être transformées en un document au format HTML, epub ou pdf en utilisant le logiciel [http://www.sphinx-doc.org](sphinx). Pour faciliter cette compilation, une configuration [vagrant](https://www.vagrantup.com) est reprise dans le fichier [[https://github.com/obonaventure/SystemesInformatiques/tree/master/Vagrantfile](Vagrantfile) se trouvant à la racine du projet. [vagrant](https://www.vagrantup.com) est un logiciel fonctionnant sur Linux, Windows et MacOS qui permet d'automatiser et de faciliter la création de machines virtuelles supportées notamment par [Virtualbox](https://www.virtualbox.org).


Comment créer de nouvelles questions à choix multiples
------------------------------------------------------

Une des améliorations récentes aux notes du cours reprises sur ce repository git est le support de questions à choix multiples. Ces questions à choix multiples sont écrites grâce à une petite extension à [http://www.sphinx-doc.org](sphinx) qui est intégrée au projet. Plusieurs dizaines de questions à choix multiples ont déjà étés écrites et les étudiants sont invités à proposer de nouvelles questions en s'appuyant sur les difficultés qu'ils ont rencontré en préparant les travaux pratiques du cours ou en révisant la théorie.

Une bonne question à choix multiples doit répondre à plusieurs critères :

 - elle doit être bien formulée et facilement compréhensible par les étudiants qui vont la lire
 - elle doit avoir plusieurs réponses correctes possibles. Ce point est nécessaire car les questions à choix multiples affichées à travers un script javascript dans les pages HTML qui présente une réponse positive et n réponses négatives au lecteur. La réponse positive et les réponses négatives sont à chaque fois choisies et présentées dans un ordre aléatoire.
 - les réponses négatives (au minimum de trois) doivent si possible être accompagnées de commentaires qui permettent à l'étudiant(e) qui les lit de bien comprendre l'erreur qu'il(elle) a fait et donc apprendre de ses erreurs

De nombreux exemples de questions sont disponibles dans le répertoire [https://github.com/obonaventure/SystemesInformatiques/tree/master/Exercices/mcq-ex](Exercices/mcq-ex). Un exemple illustrant la façon dont il faut écrire les questions en restructured text est disponible dans le fichier [https://github.com/obonaventure/SystemesInformatiques/tree/master/Exercices/mcq-ex/revision.rst](Exercices/mcq-ex/revision.rst). Les étudiants sont invités à repartir de cet exemple pour proposer de nouvelles questions.
