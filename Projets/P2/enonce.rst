 .. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

Application de filtres sur des images
=====================================

Une image numérique est composée par des petits points appelée pixels. Chaque
pixel a une couleur bien spécifique. Cette couleur est défini par les 3 couleurs
primaires, rouge, vert et bleu. À l'aide de ces couleurs toute autre couleur
peut être représentée.

L'intensité de chaqune des couleurs primaires d'un pixel est exprimé par un
entier sur 8 bits. Donc, d'une valeur entre 0 et 255 avec 0 étant l'intensité
la plus faible. Par exemple, pour représenter la couleur "noir", l'intensité de
chaqune des couleurs primaires vaut 0. Le blanc est obtenu en mettant les intensités
à leur valeur maximale (255).

Le format bitmap est un format de fichier pour stocker l'information sur les pixels
d'une image. C'est un format très simple en stockant pour chaque pixel les intensités
des trois couleurs primaires. Donc, pour chaque pixel le format bitmap requiert
24 bits pour pouvoir stocker l'information nécessaire.

Un filter d'image est capable d'appliquer certains opérations sur les pixels.
Par exemple un filter peut enlever tout les parties 'rouge' de l'image en mettant
l'intensité de la couleur rouge de chaque pixel à 0.


Programme attendu
+++++++++++++++++


On vous demande d'implémenter des filtres parallélisé sur les images bitmap.
Votre programme recoît en argument un dossier contenant des fichiers bitmap,
une liste de filtres à appliquer et le nombre de threads par filtre.

Plus en détails, votre programme doît supporter la ligne de commande suivante:

    .. code-block:: console

        $ ./filter -f filter1[,filter2[,...]] -t numThreads1[,numThreads2[,...]] input-folder output-folder

L'option ''-f'' permet de spécifier le filtre et l'ordre dans lequel ils sont appliqué sur chaque image.
La liste des filtres est la suivante:

    * ''identity'' Un filtre qui ne change pas les pixels de l'image (déjà fourni).
    * ''red'' Filtre, qui enlève la partie 'rouge' de l'image.
    * ''green'' Filtre, qui enlève la partie 'vert' de l'image (déjà fourni).
    * ''blue'' Filtre, qui enlève la partie 'bleu' de l'image.
    * ''grayscale'' Filtre, qui transforme l'image en niveau de gris. Le niveau du gris est calculée en mettant chaque couleur primaire du pixel égale à la moyenne des trois couleurs primaire du pixel.
    * ''blur'' Filtre, qui ajoute un flou gaussien dans l'image. Voyez :download:`/Projets/P2/src/filter.h` pour plus d'informations sur ce filtre.

L'option ''-t'' permet de spécifier le nombre de threads par filtre. Donc, il y a toujours ''numThreads1'' threads pour le filtre ''filter1''. L'option ''-t'' a autant d'arguments que l'option ''-f''.

Les arguments ''input-folder'' et ''output-folder'' fournissent au programme le dossier où les fichiers bitmap se trouvent et le dossier vide ''output-folder'' dans lequel il faut écrire les images.


API fourni
++++++++++

Nous vous fournissons un API pour lire un fichier bitmap et écrire l'image dans le format bitmap.

     .. code-block:: c

        int load_bmp(char *file, struct image **res_image);

''load_bmp'' charge l'image donnée par ''file'' et alloue une structure ''struct image'' qui représente tout l'image entière. Regardez :download:`/Projets/P2/src/bitmap.h` pour plus d'informations.

     .. code-block:: c

        int write_bmp(struct image *img, char *file);

''write_bmp'' écrit l'image ''img'' dans le fichier dont le chemin est spécifié par ''file''. :download:`/Projets/P2/src/bitmap.h` fournit plus d'informations.


Consignes
+++++++++

Le projet est à soumettre pour le XXX DATE XXX via le SVN du deuxième projet. Vous devez donc vous inscrire ensemble avec votre binôme sur le SVN ''SINF1252_2013_P2'' sur le
site `<https://scm.info.ucl.ac.be/cgi-bin/inscription.sh>`_.

Critères d'évaluation XXX TODO XXX
