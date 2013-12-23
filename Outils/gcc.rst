.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_  et Nicolas Houtain
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_



GCC
---


Comme cela a déja été dit, le compilateur fonctionne selon 4 étapes distinctes:
	* Appel du préprocesseur ``cpp``: Supprime les commentaires, inclus les #includes et évalue les macros
	* Appel du compilateur	 ``cc1``: Génère un fichier assembleur (.as)
	* Appel de l'assembleur	 ``as``	: Génère le fichier objet (.o)
	* Appel du linkeur	 ``ld``	: Génère l'exécutable


Différentes options peuvent être utilisé avec gcc :

	* -E		: Appelle uniquement le préprocesseur
	* -S		: Appelle uniquement le préprocesseur et le compilateur
	* -C 		: Appelle le préprocesseur, le compilateur et l'assembleur

	* -o nom	: Détermine le nom du fichier de sortie
	* -g		: Option nécessaire pour générer les informations symboliques de débogage avec gdb
	* -On		: Indique le niveau d'optimisation où n est compris entre 0 et 3
	* -Wall		: Active tout les warnings
	* -Werror 	: Considère tout les warnings comme des erreurs

	* --help

Notons que les trois premières options ne présentent pas d'interêt pour ce cour.






