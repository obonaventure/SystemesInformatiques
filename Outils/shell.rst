.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by Nicolas Houtain for shell and Maxime De Mol for bash
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_


Shell
=====

L'interpréteur de commande, ou shell, est l'interface de communication entre l'utilisateur et le système d'exploitation. C'est un exécutable chargé d'interpréter les commandes écrites par l'utilisateur et de les exécuter.

Dans le cadre de ce cours nous utiliserons l'interpréteur `bash(1)`_. Cet exécutable est généralement placé dans le fichier ``/bin/bash``.

Le shell est un outil très puissant. Il permet d'effectuer de nombreuses opérations qui peuvent difficilement être réalisées manuellement ou via une interface graphique.


.. note:: Astuce : utilisez la complétion

 Lors de la frappe d'un nom de fichier, d'un chemin d'accès ou même d'une commande tapez sur la touche ``<tab>`` pour "compléter" le mot que vous écrivez. Si rien ne se passe tapez deux fois <tab> pour obtenir la liste des possibilités.

.. note:: Chemin absolu et relatif

 Pour écrire la position d'un fichier (son chemin), il y a deux manières de faire :
	
	* Le chemin absolu : il fait référence au chemin qu'il faut parcourir dans le système de fichier en démarrant de la racine, représenté par le caractère ``/``.

	* Le chemin relatif: il fait référence au chemin à parcourir depuis le dossier courant.


Expressions régulières
----------------------

Avant de commencer à voir les commandes utiles avec le shell, il est important de définir ce qu'est une expression régulière (`regex(3)`). Les expressions régulières caractérisent des chaînes de caractères et elles sont utiles pour de nombreuses commandes. Nous l'utiliserons notamment pour faire une recherche dans un fichier.

Dans une regex, certains caractères ont une signification particulière :

         =============   ====================================   ====================================================
         Expression      Explication                            Exemple
         =============   ====================================   ====================================================
	 ``\`` 	         Caractère d'échappement 		``[\.]`` contient un "."
	 ``^`` 	 	 Début de ligne 			``^b`` commence par b
	 ``.`` 	 	 N'importe quel caractère 		``^.$`` contient un seul caractère
	 ``$`` 	 	 Fin de ligne 				``er$`` finit par "er"
	 ``|`` 	 	 Alternative 				``^(a|A)`` commence par a ou A
	 ``( )``	 Groupement 				``^((a)|(er))`` commence par a ou er
	 ``-`` 	 	 Intervalle de caractères 		``^[a-d]`` commence par a,b,c ou d
	 ``[ ]``  	 Ensemble de caractères 		``[0-9]`` contient un chiffre
	 ``[^]``  	 Tout sauf un ensemble de caractères 	``^[^a]`` ne commence pas par a
	 ``+`` 	 	 1 fois ou plus 			``^(a)+`` commence par un ou plusieurs a
	 ``?`` 	 	 0 ou 1 fois 	 			``^(a)?`` commence ou non par un a
	 ``*`` 	 	 0 fois ou plus 			``^(a)*`` peut ou non commencer par a
	 ``{x}``    	 x fois exactement 			``a{2}`` deux fois "a"
	 ``{x,}``     	 x fois au moins 			``a{2,}`` deux fois "a" au moins
	 ``{x, y}``  	 x fois minimum, y maximum 		``a{2,4}`` deux, trois ou quatre fois "a"
         =============   ====================================   ====================================================

Notes : 
	
	- ``^b$`` 	= contient uniquement le caractère ``b``
	- ``^$`` 	= la ligne est vide

Nous verrons plus en détail leur utilisation avec les commandes plus complexes.


Manipulation des répertoires
----------------------------

Chaque processus travaille dans un répertoire dit courant. C'est le répertoire dans lequel le processus accède pour lire ou écrire des fichiers lorsque le processus utilise un nom relatif. La commande `pwd(1)`_ affiche le chemin du répertoire courant. 

Il est possible de changer le répertoire courant du processus ou du shell en utilisant la commande `cd(1posix)`_. Exemples :

  - `cd(1posix)`_ `chemin` :	change le répertoire courant par celui de "chemin".
  - `cd(1posix)`_	: change le répertoire courant par le répertoire de login de l'utilisateur courant. 
  - `cd(1posix)`_ .. : remonte dans le répertoire prédécesseur dans l'arborescence des fichiers.

La commande `mkdir(1)`_ permet de créer un répertoire. Elle prend comme argument le nom du répertoire à créer.
La commande `rmdir(1)`_ supprime un répertoire qui doit être vide. Pour effacer un répertoire et tous les fichiers qu'il contient, il faut utiliser la commande `rm(1)`_ avec l'option ``-r``. Ainsi, ``rm -r /tmp/t`` supprime le répertoire ``/tmp/t`` ainsi que tous les fichiers et sous-répertoires se trouvant dans ce répertoire. 

La commande `ls(1)`_ permet de connaître l'ensemble des fichiers et répertoires contenus dans le répertoire courant. Elle supporte plusieurs options dont les plus utiles sont :
	
    * ``-F`` : 	Positionne à la fin des noms de fichier un ``/`` pour les répertoires et ``*`` pour les fichiers exécutables
    * ``-a`` : 	Affiche tous les fichiers, y compris les fichiers cachés (ceux qui commencent par le caractère ``.`` )
    * ``-d`` : 	Evite de lister le contenu d'un répertoire : si `rep` est un répertoire, ``ls -l`` `rep` listera le contenu du répertoire `rep`, alors que ``ls -ld`` `rep` listera la description du répertoire
    * ``-l`` : 	Description complète du contenu d'un répertoire (une ligne par fichier)

Avec l'option ``-l``, le premier caractère de la ligne indique le type du fichier. Le caractère ``-`` correspond à un fichier standard et ``d`` à un répertoire. Il est aussi possible de connaître le contenu d'un autre répertoire que le répertoire courant en fournissant le nom de ce répertoire comme argument à la commande ``ls``. 

	.. code-block:: console
		
		/repertoiretest $ ls
		file.txt  repertoiresoustest/
		
		/repertoiretest $ l repertoiresoustest/
		first.txt  log.log  second.txt


Manipulation de fichiers
------------------------

Créer et détruire 
^^^^^^^^^^^^^^^^^

	* > filename			crée un fichier vide.
	* `touch(1)`_ filename		crée un fichier vide.
	* `echo(1)`_ mon_texte > filename	crée un fichier avec "mon_texte" dedans.
	
	`rm(1)`_ [-irf] files	    	efface les fichiers
				    	* -i : 	intéractif, demande une confirmation sur chaque fichier
				    	* -f : 	force la suppression du fichier
				    	* -r :  efface un répertoire et son contenu

Visualiser
^^^^^^^^^^

	* `cat(1)`_ [-opt] f1 f2		concatène et affiche les deux fichiers.
	* `cat(1)`_ [-opt] file			affiche le fichier sur la sortie standard.

					* -v : convertit les caractères spéciaux en caractères affichables
					* -n : numérote les lignes
					* -b : numérote seulement les lignes non vides
					* -E : affiche le symbôle $ à la fin de chaque ligne
					* -T : affiche les caractères de tabulation comme ^I
					* -A : équivalent à -vET
					* -e : équivalent à -vE
					* -t : équivalent à -vT

	Avec cat, il est possible d'écrire depuis la console dans un fichier. 
	Appuyez sur ctrl+D au début d'une ligne pour terminer la saisie

	.. code-block:: console

		$ cat > monfichier.txt
		En faisant ceci je remplace le texte dans
		monfichier.txt
		$

		$ cat >> monfichier.txt
		et je rajoute ceci à la fin
		$

		$ cat monfichier.txt
		En faisant ceci je remplace le texte dans
		monfichier.txt
		et je rajoute ceci à la fin


`nl(1)`_ [-opt] file		affiche le contenu d'un fichier et en numérote les lignes. 
					* -bt     : numérote les lignes non vides (par défaut)
					* -ba     : numérote toutes les lignes
					* -bpXXX  : numérote seulement les lignes qui contiennent la chaîne de caractères XXX
					* -sX     : supprime le décalage dû à la numérotation et utilise le séparateur X
					* -s'XXX' : supprime le décalage dû à la numérotation et utilise la chaîne 'XXX' 

`paste(1)`_ [-opt] f1 f2	concatène horizontalement et affiche les deux fichiers. 
					* -s : copie les lignes d'un fichier sur une ligne

`more(1)`_ file			visualise le contenu du ou des fichiers par page.
		    		Si il contient plus d'une page :
				    	* q ou Q : 	pour terminer la visualisation
					* RETURN : 	pour visualiser une ligne supplémentaire
					* ESPACE : 	pour visualiser la page suivante
					* h 	 : 	pour obtenir de l'aide 

Modifier
^^^^^^^^

`touch(1)`_ filename		met à jour les dates d'accès et de modification du fichier. Crée le fichier si il n'existe pas.
					* -c : empêche la création du fichier si celui ci n'existe pas
					* -m : change uniquement la date de modification du fichier
					* -a : change uniquement la date d'accès du fichier

`split(1)`_ [-opt] file [out]	coupe le fichier en plusieurs petites parties
					* -b nbr : decoupe selon un nombre d'octets
					* -n nbr : decoupe selon un nombre de lignes

Extraction de données
^^^^^^^^^^^^^^^^^^^^^

`grep(1)`_ [-opt] regex file	recherche l'expression dans les fichiers.
					* -i : ignore la casse
				    	* -v : affiche les lignes ne contenant pas l'expression. 
					* -c : compte les lignes ne contenant pas la chaine
					* -n : numérote chaque ligne contenant la chaîne
					* -x : affiche les lignes correspondant exactement à la chaine

`uniq(1)`_ [-opt] filename	affiche le fichier en supprimant les lignes qui se répètent successivement.
					* -u : Affiche seulement les lignes n'apparaissant qu'une seule fois
	   				* -d : Affiche seulement les lignes répétées
	   				* -c : En plus de l'affichage standard, chaque ligne est précédée du nombre de répétitions
						Si cette option est utilisée, alors les options -u et -d sont ignorées.
	   				* -i : ignore la casse
				   	* -s N : ne compare pas les N premiers caractères de chaque ligne
				   	* -w N : ne compare pas plus de N caractères de chaque ligne

`sort(1)`_ [-opt] filename	trie les lignes par ordre alphabétique.
					* -f : ignore la casse
					* -r : inverse l'ordre de tri
					* -o : modifie la sortie standard
					* -t : modifie le caractère séparateur. Par défaut c'est une chaîne de blancs
					* -n : compare selon la valeur arithmétique
					* -k : spécifie la colonne utilisée pour le tri

	uniq et sort sont souvent utilisés ensemble. Par exemple, cette commande trie les lignes de file.txt selon leur nombre d'apparitions.
	
	.. code-block:: console
	
		$ cat file.txt 
		une fois
		deux fois
		deux fois
		trois fois
		encore une fois
		trois fois
		toujours une fois
		trois fois

		$ sort file.txt | uniq -c | sort -n
			1 encore une fois
		      	1 toujours une fois
		      	1 une fois
		      	2 deux fois
		      	3 trois fois

	Une autre utilisation possible est de pouvoir trier un fichier, par exemple CSV, sur une colonne particulière. Tout d'abord, il faut modifier le séparateur de colonne avec -t, puis spécifier la colonne

	.. code-block:: console
	
		$ cat file.txt
		pcr,01,3
		pcr,1,3
		pcr,04,5
		pcr,03,6
		alex,03,6
		zorro,01,20
		zorro,5,4

		$ cat file.txt | sort -t, -k2n
		zorro,01,20
		pcr,01,3
		pcr,1,3
		alex,03,6
		pcr,03,6
		pcr,04,5
		zorro,5,4

`diff(1)`_ [-opt] f1 f2		compare le contenu de deux fichiers.
					* -i : ignore la casse
					* -c : rapport plus clair
					* -q : indique uniquement si les fichiers sont différents
					* -b : ignore les différences dues à des espaces blancs
					* -B : ignore les différences dues à des lignes blanches

	.. code-block:: console
		
		$ cat test.txt
		premiere ligne similaire

		deuxieme differente
		et moi pareil
		troisieme comme la deuxieme

		et enfin la quatrieme est la meme!
		$ cat testbis.txt
		premiere ligne similaire
		en effet, je ne lui ressemble pas..
		et moi pareil
		moi non plus, tres cher.

		et enfin la quatrieme est la meme!
		
		$ diff test.txt testbis.txt 
		2,3c2					=  Les lignes 2,3 du premier fichier et 2 du second sont différentes
		< 				        _
		< deuxieme differente		         \
		---					  >  Affichage des lignes différentes
		> en effet, je ne lui ressemble pas..   _/
		5c4				        _
		< troisieme comme la deuxieme		 \
		---					  > Même réflexion
		> moi non plus, tres cher.		_/


Obtenir des informations
^^^^^^^^^^^^^^^^^^^^^^^^

`wc(1)`_ [-opt] filename	donne sur stdout des informations au sujet de l'entrée standard ou d'une liste de fichiers. 
				Première colonne est le nombre de lignes, deuxième le nombre de mots et en dernier le nombre d'octets.
					* -l : nombre de lignes
	   				* -c : nombre d'octets
	   				* -m : nombre de caractères
	   				* -L : la longueur de la plus longue ligne
	   				* -w : le nombre de mots

Manipulations communes aux répertoires et fichiers
--------------------------------------------------

Copier
^^^^^^

`cp(1)`_ [-opt] src dst		copie la src dans le fichier dst.
		    		Si dst n'existe pas, il est créé. Sinon, si c'est un fichier, son contenu est écrasé.
					* -r : spécifie la copie d'un répertoire
					* -u : copie uniquement si src est plus récent que dst ou si il est manquant dans dst
		    	
			Note : Si la destination est un répertoire, alors la source peut être une liste de fichiers. 

	.. code-block:: console

		$ cp test.txt ./testbis/
		$ cp test.txt btest.txt ../
		$ cp -r repertoire ../repertoirebis

Déplacer ou renomer
^^^^^^^^^^^^^^^^^^^

`mv(1)`_ [-opt] src dst    	renomme ou déplace src en dst.
					* -f : écrase les fichiers existants
					* -i : demande confirmation avant d'écraser un fichier existant
					* -n : n'écrase aucun fichier déja existant
		
			Note : Si la destination est un répertoire, alors la source peut être une liste de fichiers. 

	.. code-block:: console
	
		$ mv test.txt testrename.txt
		$ mv test.txt ./testbis/
		$ mv repertoire ./repertoirebis

Rechercher
^^^^^^^^^^

Pour les critères de recherche :
		* critère1 critère2 		= et logique
		* !critère 			= non logique
		* critère1 -a critère2	 	= ou logique

`find(1)`_ chemin regex	 	recherche les fichiers/répertoires caractérisés par nom, à partir du répertoire rep et affiche le résultat.
			    		* -name  : sur le nom du fichier
			    		* -perm  : sur les droits d'accès du fichier
			    		* -links : sur le nombre de liens du fichier
			    		* -user  : sur le propriétaire du fichier
			    		* -group : sur le groupe auquel appartient le fichier
			    		* -type  : sur le type (d=répertoire, c=caractère, f=fichier normal)
			    		* -size  : sur la taille du fichier en nombre de blocs (1 bloc=512octets)
			    		* -atime : par date de dernier accès en lecture du fichier
			    		* -mtime : par date de dernière modification du fichier
			    		* -ctime : par date de création du fichier
					* -print : affiche les fichiers sur stdout
	
	.. code-block:: console

		$ find ./ -name "*fi*" -print	 	= contenant fi
		$ find ./ -mtime "3" -print	 	= modifié dans les trois derniers jours
		$ find ./ -name "*s*" -a -name "f*"	= contenant s et commençant par f

	Note : "./" représente le répertoire courant
		

	Il y a trois remarques à faire sur la commande find :

		* Il est parfois nécessaire de mettre -print dans la commande pour afficher le résultat
		
		* Lors de larges recherches, il peut y avoir un message d'erreur pour chaque tentative d'accès à un fichier où vous n'avez pas d'autorisation d'accès, par exemple des fichiers système. Pour éviter que ces messages d'erreur ne polluent la recherche, il faut rediriger la sortie d'erreur standard dans "un puits sans fond". Pour cela, rajoutez 2>/dev/null
		
		* Il est parfois très utile de pouvoir exécuter une commande sur les fichiers trouvés. La solution la plus légère est de rediriger la sortie et de lui attribuer une commande. Pour cela, il faut faire : "find rep -name expr| xargs commande". Cette commande est expliquée dans la section "Commandes plus complexes".

	
	Pour cet exemple, le résultat est tous les fichiers dont le nom contient "mon test", et donc le fichier contient "supertab".
	.. code-block:: console
	
		$ find /testdirectory -name *mon test* -type f | xargs grep supertab 
	
		
Création de lien
^^^^^^^^^^^^^^^^

`ln(1)`_ [-opt] src dst		création d'un lien (raccourci) sur un fichier ou un répertoire. Attention un lien n'est pas une copie.
	    			Il existe deux sortes de liens: 
					* le lien physique 			 : uniquement des fichiers
					* le lien symbolique (avec l'option -s)  : fichiers et répertoires

   "SHEMA"

Dans le cas de lien physique, on supprime le fichier en supprimant tous les liens qui pointent sur ce fichier. 
Par contre pour des liens symboliques, vous pouvez effacer le fichier sans effacer les liens, mais alors ceux-ci seront invalides. 

Archivage et compression
^^^^^^^^^^^^^^^^^^^^^^^^

Il est important de noter qu'une archive n'est pas forcément compressée.

`tar(1)`_ [-opt] tarname.tar files	crée une archive à partir d'une liste de fichiers ou de répertoires.
						* f : 	argument obligatoire, sauf si l'on veut lire ou écrire vers/depuis un lecteur de bande
						* c : 	crée une archive
						* z :	compresse l'archive créée, en utilisant gzip. (Attention, l'extension doit être "tar.gz")
						* j : 	compresse mieux l'archive mais prend plus de temps. (Attention, l'extension doit être "tar.bz2")
						* x : 	désarchive
						* t : 	inspection de l'archive

	.. code-block:: none

		$ tar cf monarchive.tar firstfile.c  secondfile.c  	 = 	crée une archive contenant deux fichiers
		$ tar cfz monarchive.tar.gz firstfile.c  secondfile.c	 =	crée une archive compressée
		$ tar tf monarchive.tar					 =	inspecte l'archive créée
		firstfile.c
		secondfile.c
		$ tar xf monarchive.tar.gz				 =	désarchive
		$ tar xf monarchive.tar -C /home			 =	désarchive monarchive.tar dans /home

 
`gzip(1)`_ file				compresse un fichier ou une archive
						* -c  :	la compression est effectuée sur la sortie standard au lieu du fichier lui-même
						* -c1 :	compression plus rapide
						* -c9 :	meilleur compression

	.. code-block:: console
	
		$ gzip secondfile.c 		=	compresse un fichier et produit un fichier .gz
		$ gzip monarchive.tar 		=	compresse une archive
		
		$ ls
		monarchive.tar			=	compresse monarchive.tar vers monarchive.tar.gz
		$ gzip monarchive.tar 
		ls
		monarchive.tar  monarchive.tar.gz

Permissions
^^^^^^^^^^^

Pour chaque fichier, il y a trois classes d'utilisateurs
	* user  	: 	le propriétaire du fichier
	* groupe 	: 	le groupe auquel appartient le fichier
	* autre 	: 	tous les autres

Les permissions accordées à ces trois classes sont :
	* r : 	lecture
	* w : 	écriture
	* x : 	exécution (Un fichier peut être executé et un répertoire peut devenir répertoire courant)


`chmod(1)`_ mode files    	change les permissions du ou des fichiers/répertoires.
    
	.. code-block:: console

	    					user 	group 	other 	
	    	mode désiré : rwxr-xr--		rwx 	 r-x 	 r-- 	
	    					111 	 101 	 100 	 (en binaire)
	    					 7 	  5 	  4 	 (en hexadecimal)
	    	
		d'où la commande ``chmod 754 fichier``

 
`chown(1)`_ owner files    	change le propriétaire du fichier.

`chgrp(1)`_ grp files	    	change le groupe du fichier.

Obtenir des informations
^^^^^^^^^^^^^^^^^^^^^^^^

`stat(1)`_ [-opt] filename	donne des informations sur les métadonnées associées au fichier
					* -f : affiche l'état du système de fichiers plutôt que celui du fichier
					* -L : suit les liens du fichier
					* -t : affiche les informations de façon concise
					* --format=FORMAT : affiche les informations selon le format choisi

		.. code-block:: console

			Séquences de format valables pour les fichiers :
				%a droits d'accès en octal
				%A droits d'accès dans un format lisible par un humain
				%b nombre de blocs alloués (voir << %B >>)
				%B taille, en octets, de chaque bloc rapporté par %b
				%d numéro de péripherique en décimal
				%D numéro de péripherique en hexadécimal
				%f mode brut en hexadécimal
				%F type de fichier
				%g identifiant de groupe du propriétaire
				%G nom de groupe du propriétaire
				%h nombre de liens directs (<< hard >>)
				%i numéro d'inode
				%m point de montage
				%n nom de fichier
				%N nom du fichier cité, déréférencé s'il s'agit d'un lien symbolique
				%o taille de bloc d'entrée/sortie
				%s taille totale, en octets
				%u identifiant du propriétaire
				%U nom d'utilisateur du propriétaire
				%w date de création au format lisible, ou << - >> si elle n'est pas connue
				%x date du dernier accés au format lisible
				%y date de la dernière modification au format lisible
				%z date du dernier changement au format lisible

			 Séquences de format valables pour les systèmes de fichiers :
				%a nombre de blocs libres disponibles pour les utilisateurs normaux
				%b nombre total de blocs de données dans le système de fichiers
				%c nombre total d'inodes dans le système de fichiers
				%d nombre d'inodes libres dans le système de fichiers
				%f nombre de blocs libres dans le système de fichiers
				%i identifiant du système de fichier en hexadécimal
				%l longueur maximale des noms de fichier
				%n nom de fichier
				%s taille des blocs (pour des transferts plus rapides)
				%S taille fondamentale des blocs (pour le décompte des blocs)
				%t type en hexadecimal
				%T type dans un format lisible par un humain


Gestion des processus
---------------------

`top(1)`_ 			affiche les processus en cours d'exécution.
`pstree(1)`_			affiche l'arbre des processus.

`strace(1)`_ [-opt] cmd		trace les appels systèmes et la création de signaux effectués par une commande
					* -c : collecte quelques statistiques de base concernant les appels système tracés
					* -o : redirige la sortie standard
					* -p : avec cette option, cmd est remplacé par le PID d'un processus, et celui ci est tracé
					* -T : indique le temps passé dans chaque appel système
					* -t : indique l'heure au début de chaque ligne. -tt comprend les microsecondes
					* -r : donne le temps entre deux appels systèmes successifs

	.. code-block:: console

		$ strace -c ./monexecutable -o fichierRecoltantLesInformations.log
		

`lsof(8)`_ [-opt]		affiche les fichiers ouverts.
					* -p PID : uniquement les fichiers ouverts du processus
					* -i : affiche les connexions réseau ouvertes

	.. code-block:: console
	
		$ lsof -i -p 2735	  =  Les connexions ouvertes ET les fichiers ouverts par le processus 2735
		$ lsof -i -a -p 2735	  =  Les connexions ouvertes par le processus 2735


`kill(1)`_ pid			supprime le processus specifié. Si malgré la commande, le processus n'est pas détruit, essayez kill -9 pid.


Symboles utiles
---------------

Redirection de l'entrée, sortie et erreur standard
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Lors de l'exécution d'une commande, un processus est créé et celui-ci va ouvrir trois flux : l'entrée, la sortie et l'erreur standard. Par défaut lorsque l'on exécute un programme, les données sont donc lues à partir du clavier et le programme envoie sa sortie et ses erreurs sur l'écran. toutefois, il est possible de rediriger ces flux.

	* < 		l'entrée standard est lue à partir d'un fichier
	* > 		La sortie standard est redirigée dans un fichier. Si le fichier existe, il est vidé avant d'écrire.
	* >> 		La sortie standard est redirigée dans un fichier. Si le fichier existe, la sortie standard est ajoutée à la fin de celui ci.
	* 2>		La sortie d'erreur standard est redirigée
   	* cmd1 | cmd2		La sortie standard de cmd1 devient l'entrée standard de cmd2

Symboles pour les commandes
^^^^^^^^^^^^^^^^^^^^^^^^^^^

	* ``?`` 		caractère joker remplaçant un seul caractère
	* ``!`` 		inverse le sens d’un test ou l’état de sortie d’une commande. 

	* ``*`` 		caractère joker remplaçant une chaîne de caractères
	* ``&`` 		exécute une commande en arrière-plan
	* ``;`` 		sépare des instructions sur une seule ligne

        * ``cmd1 && cmd 2``		cmd2 n'est exécuté que si cmd1 réussit
        * ``cmd1 || cmd 2``		cmd2 n'est exécuté que si cmd1 échoue

	* ``\``		annule l'effet du caractère spécial suivant
	* ``" "``		annule l'effet de tous les caractères spéciaux entre les guillemets, sauf ``$`` et ``\``


Commandes utiles
----------------

Pour effectuer des chaînes
^^^^^^^^^^^^^^^^^^^^^^^^^^

`xargs(1)`_			permet d'appliquer une commande à l'entrée standard.

	Pour cet exemple, le résultat est tous les fichiers dont le nom contient "mon test", et dont le fichier contient "supertab".
	
	.. code-block:: console
	
		$ find /testdirectory -name *mon test* -type f | xargs grep supertab 

`tee(1)`_ file			lit depuis l'entrée standard, écrit dans la sortie standard et dans le fichier. Elle est utilisée pour continuer une chaîne tout en faisant une sauvegarde des informations.

	.. code-block:: console

		% echo "Les tubes sont un mécanisme puissant." | tee fichier.txt | wc
     			 1       6      39
		% cat fichier.txt 
		Les tubes sont un mécanisme puissant.

	On peut voir que le texte a bien été relayé vers la commande "wc" et qu'en même temps, ce texte a été écrit dans fichier.txt


Informations générales
^^^^^^^^^^^^^^^^^^^^^^

`su(1)`_			passe en mode "root", c'est à dire administrateur

`whatis(1)`_ cmd		explique briévement l'utilité d'une commande

`apropos(1)`_ [-opt] motclé	recherche dans les man pages les commandes correspondants aux mots clés.
				* -a : Affiche seulement les résultats répondant à tout les mots clés. 
				       L'inverse est le fonctionnement par défault

`date(1)`_			donne l'heure, selon l'horloge de votre ordinateur

`cal(1)`_			affiche un calendrier du mois courant

`halt(8)`_			éteint l'ordinateur.

`reboot(8)`_			redémarre l'ordinateur

Informations système
^^^^^^^^^^^^^^^^^^^^

`time(1posix)`_ programme		permet de calculer le temps d'exécution d'un programme

`df(1)`_ [-opt] [file]		indique l'espace disque utilisé et disponible sur tous les systèmes de fichiers. 
				Si des fichiers sont passés en argument, seul les systèmes de fichiers contenant un des fichiers sont montrés.		
				
				* -h 	Imprime les dimensions dans un format lisible par l’utilisateur
				* -H 	Idem que -h, mais il utilise des puissances de 1000 au lieu de 1024
				* -i 	Affiche l’information i-node au lieu de l’utilisation des blocs
				* -l 	Limite l’affichage aux systèmes de fichiers locaux
				* -P 	Utilise le format de résultat POSIX
				* -T 	Imprime le type de système de fichiers


Maniement des jobs
^^^^^^^^^^^^^^^^^^

La plupart des commandes en console sont exécutées rapidement, mais ce n'est pas le cas de toutes. Certaines commandes, que l'on va appeler `jobs`, prennent plus de temps (comme par exemple copier un très gros fichier), et d'autres encore tournent indéfiniment.

Évidemment, quand un job est en cours d'exécution à la console, plus aucune action ne peut être faite sur celle-ci. Unix nous vient en aide dans ce cas-là avec le raccourci ``Ctrl+z`` et les commandes `jobs(1)`_, `bg(1)`_ et `fg(1)`_.

    	* ``Ctrl+z``  : Le job passe dans l'état ``suspended``. Il est en pause, et placé en background.
    	* ``jobs``    : Affiche à la console la liste des jobs présents en background
   	* ``bg``      : Passe un job mis en background de l'état ``suspended`` à l'état ``running``. Le job reste en background, mais il continue à s'exécuter
    	* ``fg``      : Passe un job du background à l'avant-plan

Exemples :

    .. code-block:: none 

      $ yes > \dev\null
      #nous lançons la commande yes

      ^Z
      #nous la suspendons avec Ctrl+z
      [1]+  Stopped                 yes > \dev\null
      #elle est placée en arrière-plan

      $ jobs
      #nous regardons la liste des jobs en arrière plan
      [1]+  Stopped                 yes > \dev\null
      #chaque job à un numéro qui lui est attribué. ici 1

      $ bg 1
      #nous relançons yes en arrière-plan. On peut utiliser son nom comme son numéro avec la commande bg et fg
      [1]+ yes > \dev\null &
      #yes s'est remis en route

      $ jobs
      #nous vérifions le statut de yes avec jobs
      [1]+  Running                 yes > \dev\null &
      #il est en cours d'exécution
      
      $ fg yes
      #nous remettons yes en avant-plan
      yes > \dev\null

      ^Z
      #nous le suspendons à nouveau
      [1]+  Stopped                 yes > \dev\null
      
      $ kill %1
      #nous terminons yes avec la commande kill %[numJob]
      [1]+  Stopped                 yes > \dev\null

      $ jobs
      #nous vérifions les jobs
      [1]+  Terminated: 15          yes > \dev\null
      #yes est marqué Terminated

      $ jobs
      #un deuxième appel à jobs nous affiche une liste vide


.. _`jobs(1)`: http://www.manpagez.com/man/1/jobs/
.. _`bg(1)`: http://linux.die.net/man/1/bg
.. _`fg(1)`: http://linux.die.net/man/1/fg


Commandes complexes
-------------------

Modification d'un fichier
^^^^^^^^^^^^^^^^^^^^^^^^^



`sed(1)`_ [-n] [-e 'prog'] [-f cmdfile] [file]  	applique des commandes de 'prog' sur un fichier
				
				* -n : n'affiche aucune ligne, sauf celle spécifiée avec la commande p
				* -e : specifie les commandes à appliquer sur le fichier
					Note : Il vaut mieux encadrer la commande avec des ' ou des " 
				* -f : les commandes sont lues à partir d'un fichier

Pour bien comprendre la puissance de sed, il est important de comprendre son fonctionnement. sed fonctionne en 4 étapes :

	* Lecture d'une ligne sur le flux d'entrée, et stockage dans l'espace de travail
	* Exécute les commandes sur l'espace de travail
	* Envoie la ligne au flux de sortie en lui rajoutant un '\n'
	* Recommence avec la ligne suivante ...  


Une commande d'un 'prog' est constituée d'un adressage, c-à-d les lignes sur lesquelles la commande est appliquée, et de l'action à exécuter.

1) L'adressage est décomposé en deux catégories.
	
	* 			: toutes les lignes
	*         num		: la ligne "num". La dernière ligne est symbolisée par $
	*      num1, num2	: les lignes entre num1 et num2

	*       /regex/		: les lignes correspondant à l'expression régulière regex
	*  /regex1/, /regex2/	: les lignes entre la première ligne correspondant à regex1 et la première ligne correspondant à regex2
				  Si regex2 est vide, la commande sera appliquée jusqu'à la fin du fichier.

	Note : 	Le ! représente la négation. Mettez le après votre spécification des lignes pour prendre la négation

	RAPPEL sur les regex :

		
         =============   ====================================   ====================================================
         Expression      Explication                            Exemple
         =============   ====================================   ====================================================
	 ``\`` 	         Caractère d'échappement 		``[\.]`` contient un "."
	 ``^`` 	 	 Début de ligne 			``^b`` commence par b
	 ``.`` 	 	 N'importe quel caractère 		``^.$`` contient un seul caractère
	 ``$`` 	 	 Fin de ligne 				``er$`` finit par "er"
	 ``|`` 	 	 Alternative 				``^(a|A)`` commence par a ou A
	 ``( )``	 Groupement 				``^((a)|(er))`` commence par a ou er
	 ``-`` 	 	 Intervalle de caractères 		``^[a-d]`` commence par a,b,c ou d
	 ``[ ]``  	 Ensemble de caractères 		``[0-9]`` contient un chiffre
	 ``[^]``  	 Tout sauf un ensemble de caractères 	``^[^a]`` ne commence pas par a
	 ``+`` 	 	 1 fois ou plus 			``^(a)+`` commence par un ou plusieurs a
	 ``?`` 	 	 0 ou 1 fois 	 			``^(a)?`` commence ou non par un a
	 ``*`` 	 	 0 fois ou plus 			``^(a)*`` peut ou non commencer par a
	 ``{x}``    	 x fois exactement 			``a{2}`` deux fois "a"
	 ``{x,}``     	 x fois au moins 			``a{2,}`` deux fois "a" au moins
	 ``{x, y}``  	 x fois minimum, y maximum 		``a{2,4}`` deux, trois ou quatre fois "a"
         =============   ====================================   ====================================================

		
	Notes : 
	
	- ``^b$`` 	= contient uniquement le caractère ``b``
	- ``^$`` 	= la ligne est vide

2) Les actions

	* p 		: affiche les lignes
	* d 		: supprime les lignes
	* y/l1/l2 	: remplace les caractères de la première liste par les caractères de la seconde
	* s/mtf/sbst/ 	: substitue le mtf par le sbst
				  Note : Par défaut seule la première occurrence est remplacée. 
					* Pour toutes les remplacer : /s/motif/substitut/g
					* Pour en remplacer 4	   : /s/motif/substitut/4

	* N		: charge une ligne supplémentaire dans l'espace de travail
	* D		: efface l'espace de travail jusqu'au premier saut de ligne incorporé
	* b		: revient

	Pour faire des commandes groupées, placez vos commandes entre {} séparées par ";".

	Quelques illustrations basiques :

	.. code-block:: none

		$ sed '' test.txt			= Le script est vide, il renvoie simplement le fichier

		$ sed -n '/Ici/p' test.txt		= Affiche les lignes contenant Ici
		$ sed 'p' test.txt			= Double toutes les lignes
		
		$ sed -e '4d; 7d' test.txt		= Supprime les lignes 4 et 7
		$ sed -e '4,7d' test.txt		= Supprime les lignes entre 4 et 7
		
		$ sed '/^#/ d' test.txt			= Supprime les lignes commencant par #
		$ sed '/e$/ d' test.txt			= Supprime les lignes se terminant par e
		$ sed '/#/,/@/d' test.txt		= Supprime les lignes comprises entre le premier # et le premier @

		$ sed -e 's/^#//' test.txt		= Supprime le commentaire en début de ligne, puisqu'il 
							  est remplacé par ''
		
		$ sed -e 'y/éèê/eee/' test.txt		= Retire les accents, puisqu'ils sont remplacés par 'e'

		$ sed -e ' 4,7 {y/éèê/eee/;s/e/[]/} test.txt 	= Remplace les accents, puis remplace les "e" par "[]"
	
		$ sed -e '/^$/ {N; D}' test.txt		= Supprime les sauts de ligne
		
		
	Explication : Pour les lignes vides, on charge la ligne suivante, on envoie ce qui se trouve dans l'espace de travail jusqu'au premier '\n', puis on continue le traitement du texte. Pour continuer le traitement, une nouvelle ligne est chargée et va donc "écraser" les '\n' qui sont toujours présents dans l'espace de travail.

		
Lors du remplacement d'un mot par un autre, il peut survenir un problème de taille. En effet, le remplacement n'est effectué que sur le premier mot de la ligne trouvé.

	.. code-block:: console

		$ sed -e ' s/[oe]/[/' test.txt 
		B[njour,

		C[ci est un fichier de test.
		Ici la lign[ numéro 4.

		# c[ci pourrait être un commentaire
		Ici la lign[ numéro 7.I

		Au r[voir

	On remarque que tout les 'e' et 'o' n'ont pas été remplacés...

Pour contrecarrer ce problème, il est possible de placer dans le script un label et de revenir dessus, comme un goto en C. Pour effectuer ce retour utilisez la commande 'b'.

	.. code-block:: console

		$ sed -re ':start {s/[eo]/[/g; /[eo]/ b start}' test.txt
		B[nj[ur,

		C[ci [st un fichi[r d[ t[st.
		Ici la lign[ numér[ 4.

		# c[ci p[urrait êtr[ un c[mm[ntair[
		Ici la lign[ numér[ 7.I

		Au r[v[ir

	Explication : Un label est placé au début des commandes. La première commande remplace le premier [eo] trouvé. La seconde retourne au label si il reste encore un [eo] dans la ligne. Une fois qu'il n'y a plus de [eo], la ligne suivante est chargée. 


Appliquer des actions à un fichier
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

`awk(1)`_ [-Fs] [-v variable] [-f fichier de commandes] 'program' fichier
  		* -F : Spécifie les séparateurs de champ
  		* -v : Définit une variable utilisée à l'intérieur du programme.
  		* -f : Les commandes sont lues à partir d'un fichier. 

Note : awk est une commande extrêmement puissante, elle permet d'effectuer une multitude d'opérations. Son utilisation est complexe et elle est bien détaillée sur ce site : http://www.shellunix.com/awk.html. Je vous encourage à le lire.


Redirection nommée
^^^^^^^^^^^^^^^^^^

`mkfifo(1)`_ nom		crée un tube nommé

	.. code-block:: console

		ls | less est donc similaire à 	mkfifo /tmp/tempfifo
						ls > /tmp/tempfifo
						less < /tmp/tempfifo






.. _bash:
	
Bash
----

Taper des commandes dans la console est inévitable lors d'opérations avancées sur un système Unix, et peut devenir très vite répétitif et fastidieux pour l'utilisateur. Le Bash est justement là pour éviter ces répétitions et automatiser certaines tâches à l'aide de scripts, qui sont des fichiers texte composés de différentes commandes Unix, lus, interprétés et exécutés par Bash.


Premier script
^^^^^^^^^^^^^^

Nous allons écrire un premier script bash pour présenter la manière générale de procéder avec un tel outil. Les scripts commencent toujours par la ligne ``#!/bin/bash`` qui indique à l'exécution qu'il s'agit d'un script et avec quel interpréteur le lire (ici bash).

    .. code-block:: bash

      #!/bin/bash
      echo "Hello, 1252"

Nous allons enregistrer ce texte sous le nom `hello.sh <https://raw.github.com/HappyRave/SystInfo1/master/valgrind/hello.sh>`_, puis changer ses permissions pour le rendre exécutable.

    .. code-block:: console

      $ chmod 700 hello.sh

Après il ne reste plus qu'à l'exécuter et observer le résultat.

    .. code-block:: console

      $ ./hello.sh
      Hello, 1252

Les variables
^^^^^^^^^^^^^

Bash permet l'utilisation de variables dans les scripts. Il peut s'agir de simples variables ou de tableaux. Bash n'est pas un langage typé, les Int ou les String n'existent pas, toutes les variables sont traitées de la même façon. Pour illustrer ceci nous allons écrire le script `variables.sh <https://raw.github.com/HappyRave/SystInfo1/master/valgrind/variables.sh>`_

    .. code-block:: bash

      #!/bin/bash

      bonjour='Hello, '
      #il est important de ne pas mettre d'espaces autour du =
      nombre[0]=12
      nombre[1]=52

      echo $bonjour${nombre[0]}${nombre[1]}
      #on accède à une variable simple avec un $ devant son nom
      #on accède à un élément d'un tableau avec un $ devant et des {} autour
      echo $bonjour${nombre[*]}
      #le caractère * indique qu'on veut utiliser tous les éléments du tableau (séparés
      #par un espace à chaque fois)

Ce script produit comme résultat

    .. code-block:: console

      $ ./variables.sh
      Hello,1252
      Hello,12 52

Il est interressant de visiter cette page : http://michel.mauny.net/sii/variables-shell.html

Les structures de contrôle
^^^^^^^^^^^^^^^^^^^^^^^^^^

Comme dans chaque langage de programmation, bash offre les structures de contrôle habituelles telles que les boucles if, for ou encore while que nous allons démontrer maintenant.

Comme dit précédemment, il n'y a pas de type en bash, true et false n'existent pas. Les conditions que les boucles vont utiliser seront les valeurs renvoyées par l'exécution d'une commande. Un 0 renvoyé correspond à un true, tandis que tout le reste est considéré comme un false.

Dans le but de tester ces boucles nous utiliserons un petit programme en C, `return.c <https://raw.github.com/HappyRave/SystInfo1/master/valgrind/return.c>`_, qui va renvoyer la valeur qu'il reçoit en argument. Le script de test est `structures.sh <https://raw.github.com/HappyRave/SystInfo1/master/valgrind/structures.sh>`_.

   .. code-block:: bash

      #!/bin/bash

      if ./return 0; then
      #la valeur de renvoi sera 0 quand la boucle aura été exécutée
      echo "Hello"
      fi

      if ./return 1; then
      #ici c'est la condition else qui sera remplie
      echo "Hello"
      else
      echo "Bye"
      fi

      for i in 1 2 5 2
      #les boucles for peuvent s'écrire de cette façon
      do
      echo $i
      done

      echo Hello again!

      for (( j=1; j<=5; j++))
      #ou encore utiliser la synthaxe classique comme en C ou Java
      do
      echo $j
      done

      k=4
      while ((k>0))
      do
      echo $k
      k=$((k-1))
      done

Le résultat à l'exécution est

    .. code-block:: console

      $ ./structures.sh
      Hello
      Bye
      1
      2
      5
      2
      Hello again!
      1
      2
      3
      4
      5
      4
      3
      2
      1
