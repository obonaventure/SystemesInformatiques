.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Application de filtres sur des images
=====================================

Une image numérique est composée de petits points appelée pixels. Chaque
pixel a une couleur bien spécifique qui est définie par 3 couleurs primaires:
le rouge, le vert et le bleu. Ces 3 couleurs primaires permettent de représenter, en les additionnants, un grand nombre de couleurs.

Le format bitmap est un format de fichier pour stocker l'information sur les pixels
d'une image. C'est un format très simple qui utilise le format RGB pour chaque pixel.
Dans ce format, l'intensité de chacune des couleurs primaires d'un pixel est exprimé par un
entier sur 8 bits. Ces couleurs ont donc une valeur entre 0 et 255 avec 0 étant l'intensité
la plus faible (le noir) et 255 l'intensité la plus forte (le blanc).
Pour chaque pixel le format bitmap requiert donc
24 bits afin de stocker l'information nécessaire.

Dans ce projet, vous allez combiner des filtres sur des images. Un filtre est une opération appliquée sur les pixels d'une image. Par exemple, dans ce projet, vous allez implémenter un filtre qui retire la composante rouge d'une
image en changeant son intensité à 0.


Programme attendu
-----------------

On vous demande d'implémenter des filtres parallélisés sur les images bitmap.
Votre programme reçoit en argument un dossier contenant des fichiers bitmap,
une liste de filtres à appliquer et le nombre de threads utilisés par filtre. Votre programme doit se baser sur le code présent dans l'archive :download:`/Projets/P2/projet-2.tar.gz`.

Plus en détails, votre programme doit supporter la ligne de commande suivante:

    .. code-block:: console

        $ ./filter -f filter1[,filter2[,...]] -t numThreads1[,numThreads2[,...]] input-folder output-folder

L'option ''-f'' permet de spécifier les filtres et l'ordre dans lesquels ils sont appliqués sur chaque image.
La liste des filtres est la suivante:

    * ''red'' Filtre, qui enlève la composante 'rouge' de l'image.
    * ''green'' Filtre, qui enlève la composante 'vert' de l'image (déjà fourni).
    * ''blue'' Filtre, qui enlève la composante 'bleu' de l'image.
    * ''grayscale'' Filtre, qui transforme l'image en niveau de gris. Le niveau du gris est calculé en mettant chaque couleur primaire du pixel égale à la moyenne des trois couleurs primaires.
    * ''blur'' Filtre, qui ajoute un flou gaussien dans l'image. Voyez :download:`/Projets/P2/src/filter.h` pour plus d'informations sur ce filtre.

Nous vous demandons également de définir et d'implémenter vous-mêmes un filtre. Ce filtre sera évalué en fonction de son originalité. Vous pouvez bien sûr vous baser sur des filtres déjà existants. Il est cependant interdit de copier/coller un code existant.

L'option ''-t'' permet de spécifier le nombre de threads par filtre. Il y a donc toujours ''numThreads1'' threads pour le filtre ''filter1''. L'option ''-t'' doit avoir autant d'arguments que l'option ''-f''.

Les arguments ''input-folder'' et ''output-folder'' fournissent au programme respectivement le dossier où les fichiers bitmap se trouvent et le dans lequel il faut écrire les images. Chaque image à la sortie aura le même nom et extension qu'à l'entrée.

Voici un exemple d'utilisation du programme:

    .. code-block:: console

        $ ./filter -f red,blur,green -t 2,4,2 images/ out_images/


API fournie
-----------

Nous vous fournissons une API pour lire un fichier bitmap et écrire l'image dans le format bitmap.

     .. code-block:: c

        int load_bmp(char *file, struct image **res_image);

''load_bmp'' charge l'image donnée par ''file'' et alloue une structure ''struct image'' qui représente l'image entière. Regardez :download:`/Projets/P2/src/bitmap.h` pour plus d'informations.

     .. code-block:: c

        int write_bmp(struct image *img, char *file);

''write_bmp'' écrit l'image ''img'' dans le fichier dont le chemin est spécifié par ''file''. :download:`/Projets/P2/src/bitmap.h` fournit plus d'informations.

Pour pouvoir tester votre programme, nous avons mis à votre disposition un ensemble d'images sur `<http://sinf1252.info.ucl.ac.be/data/images.tar.gz>`_

Séance intermédiaire
--------------------

Afin d'au mieux vous aider dans vos choix de désign, nous organisons une séance intermédiaire *obligatoire*. Pour cela nous vous demandons d'écrire un petit rapport de *2 pages maximum* qui doit être présent sur le SVN du projet dans le votre dossier de groupe et doit se nommer *prerapport.pdf*. Ce pré-rapport doit être fourni avant le 14 mars à 23h55 et doit contenir la solution que vous comptez implémenter. Une discussion de maximum 10 minutes aura alors lieu avec les assistants du cours et sera organisée le 18 mars. Vous devez vous inscrire en indiquant votre numéro de groupe (du SVN) pour le projet (voir section suivante) sur le doodle: `<http://doodle.com/fskwhh22u56xxn5w>`_.

Consignes
---------

Le projet est à soumettre pour le 17 avril à 12h00 via le SVN du deuxième projet. Vous devez donc vous inscrire ensemble avec votre binôme sur le SVN ''SINF1252_2013_PROJET_2'' sur le
site `<https://scm.info.ucl.ac.be/cgi-bin/inscription.sh>`_.
Vous devez fournir sur le SVN dans votre dossier de groupe:

	- Le code source de votre projet (pas de binaires) ainsi qu'un ``Makefile`` (lorsque l'on tape ``make`` un binaire ``filter`` doit être généré.). Vous devez compiler votre programme avec les options *-Wall* et *-Werror* de gcc.
	- Un rapport de *4 pages maximum* (12pt) qui décrit vos choix architecturaux ainsi que les problèmes rencontrés. Le rapport doit être nommé *rapport.pdf* et présent dans votre dossier de groupe.

Les critères de cotation sont les suivants (liste non-exhaustive):

        - Votre impémentation doît fonctionner dans les salles informatiques du département;
	- Création et gestion des threads;
	- Synchronisation des threads;
	- Gestion de la mémoire;
	- Implémentation des filtres;
	- Respect des consignes.

