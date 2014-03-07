.. -*- coding: utf-8 -*-
.. Copyright |copy| 2012 by `Olivier Bonaventure <http://inl.info.ucl.ac.be/obo>`_, Christoph Paasch et Grégory Detal
.. Ce fichier est distribué sous une licence `creative commons <http://creativecommons.org/licenses/by-sa/3.0/>`_

.. raw:: html

  <script type="text/javascript" src="js/jquery-1.7.2.min.js"></script>
  <script type="text/javascript" src="js/jquery-shuffle.js"></script>
  <script type="text/javascript" src="js/rst-form.js"></script>
  <script type="text/javascript" src="js/prettify.js"></script>
  <script type="text/javascript">$nmbr_prop = 3</script>



=================
Quatrième semaine
=================

Cette semaine, la matière porte sur l'organisation de la mémoire et sur le langage assembleur IA32. La matière couverte se trouve dans les sections suivantes du syllabus :

  - `Organisation des ordinateurs <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Assembleur/memory.html>`_
 - `Etude de cas : IA32 <http://sites.uclouvain.be/SystInfo/notes/Theorie/html/Assembleur/memory.html#etude-de-cas-architecture-ia32>`_

Question 1. Instruction ``mov``
-------------------------------

Les instructions de la famille ``mov`` permettent de déplacer des données entre registres ou d'initialiser des registres. Considérons le fragment de code C suivant (dans lequel ``g``, ``g2`` et ``s`` sont des variables globales de type ``int``) :

.. code-block:: c

   g=1234;
   g2=5678;
   s=g;
   g=g2;
   g2=s;

Parmi les traductions en assembleur ci-dessus, une seule est correcte. Laquelle ?


.. class:: positive


-
 .. code-block:: nasm

    movl    $1234, g
    movl    $5678, g2
    movl    g, %ecx
    movl    %ecx, s
    movl    g2, %ecx
    movl    %ecx, g
    movl    s, %ecx
    movl    %ecx, g2

-
 .. code-block:: nasm

    movl    $1234, g
    movl    $5678, g2
    movl    g, %eax
    movl    %eax, s
    movl    g2, %eax
    movl    %eax, g
    movl    s, %eax
    movl    %eax, g2


.. class:: negative

-
 .. code-block:: nasm

    movl    g, $1234
    movl    g2, $5678
    movl    %eax, g
    movl    s, %eax
    movl    %eax, g2
    movl    g, %eax
    movl    s, %eax
    movl    g2, %eax

 .. class:: comment

    L'instruction ``mov`` prend comme premier argument la source et comme second la destination.

-
 .. code-block:: nasm

    movl    $1234, g
    movl    $5678, g2
    movl    g2, %eax
    movl    %edx, s
    movl    g, %eax
    movl    %edx, g2
    movl    s, %eax
    movl    %eax, g2

 .. class:: comment

    Ce code utilise les registres ``%edx`` et ``%eax``. ``%edx`` est utilisé sans être initialisé.


-
 .. code-block:: nasm

    movw    $1234, g
    movw    $5678, g2
    movb    g2, %eax
    movb    %eax, s
    movb    g, %eax
    movb    %eax, g2
    movb    s, %eax
    movb    %eax, g2

 .. class:: comment

    L'instruction ``movb`` déplace un ``byte`` et non le contenu complet d'un registre de 32 bits.

-
 .. code-block:: nasm

    movw    $1234, g
    movw    $5678, g2
    movb    g2, %edx
    movb    %edx, s
    movb    g, %edx
    movb    %edx, g2
    movb    s, %edx
    movb    %edx, g2


 .. class:: comment

    L'instruction ``movb`` déplace un ``byte`` et non le contenu complet d'un registre de 32 bits.

Question 2. Opérations arithmétiques
------------------------------------

Considérons le fragment de programme C ci-dessous :

 .. code-block:: c

    a=a+b;
    b=b+b;
    c=b-a;

Une seule des séquences d'instructions assembleur ci-dessous est une traduction correcte de cette séquence d'instructions. Laquelle ?

.. class:: positive

-
 .. code-block:: nasm

        movl    a, %eax
        addl    b, %eax
        movl    %eax, a
        movl    b, %eax
        addl    b, %eax
        movl    %eax, b
        movl    b, %eax
        subl    a, %eax
        movl    %eax, c

-
 .. code-block:: nasm

        movl    b, %eax
        addl    a, %eax
        movl    %eax, a
        movl    b, %eax
        addl    b, %eax
        movl    %eax, b
        movl    b, %eax
        subl    a, %eax
        movl    %eax, c


.. class:: negative

-
 .. code-block:: nasm

        movl    b, %eax
        addl    a, %eax
        movl    %eax, a
        movl    b, %eax
        movl    %eax, %ecx
        addl    $1, %ecx
        movl    %ecx, b
        movl    %eax, b
        movl    a, %eax
        subl    b, %eax
        movl    %eax, c

 .. class:: comment

           Ceci est la traduction de  :

           .. code-block:: c

       	      a=b+a;
  	      b=b++;
  	      c=a-b;

-
 .. code-block:: nasm

        movl    b, %eax
        addl    a, %eax
        movl    %eax, c
        movl    b, %eax
        movl    %eax, %ecx
        addl    $1, %ecx
        movl    %ecx, b
        movl    %eax, b
        movl    a, %eax
        subl    b, %eax
        movl    %eax, a

 .. class:: comment

        Ceci est la traduction de  :

        .. code-block:: c

	  c=b+a;
  	  b=b++;
  	  a=a-b;

-
 .. code-block:: nasm

        movl    b, %eax
        addl    a, %eax
        movl    %eax, b
        movl    b, %eax
        movl    %eax, %ecx
        addl    $1, %ecx
        movl    %ecx, b
        movl    %eax, a
        movl    b, %eax
        subl    a, %eax
        movl    %eax, c

 .. class:: comment

        Ceci est la traduction de  :

        .. code-block:: c

            b=b+a;
  	    a=b++;
  	    c=b-a;

Question 3. Instructions conditionnelles
----------------------------------------

Les instructions conditionnelles sont fréquemment utilisées en langage C et en assembleur. Considérons le fragment de programme C ci-dessous (``a`` et ``b`` sont des variables globales de type ``int``):

 .. code-block:: c

   if(b<4)
     a++;

Une seule des séquences d'instructions assembleur ci-dessous est une traduction correcte de cette séquence d'instructions. Laquelle ?

.. class:: positive

-
 .. code-block:: nasm

    begin:
        cmpl    $4, b
        jge     end
        movl    a, %eax
        addl    $1, %eax
	movl    %eax, a
    end:

-
 .. code-block:: nasm

    begin:
        cmpl    $4, b
        jl      next
        jmp     end
    next:
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
    end:

 .. class:: comment

    Ceci est la traduction de  :

    .. code-block:: c

       if((b>=4))
       {}
       else
         a++;


.. class:: negative

-
 .. code-block:: nasm

    begin:
        cmpl    $4, b
        jg      end
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
    end:

 .. class:: comment

    Ceci est la traduction de  :

    .. code-block:: c

       if(b<=4)
         a++;


-
 .. code-block:: nasm

    begin:
        cmpl    $4, b
        je      end
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
    end:



 .. class:: comment

    Ceci est la traduction de  :

    .. code-block:: c

       if(b!=4)
         a++;

-
 .. code-block:: nasm

    begin:
        cmpl    $4, b
        jl      end
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
    end:


 .. class:: comment

    Ceci est la traduction de  :

    .. code-block:: c

     if(!(b<4))
        a++;

-
 .. code-block:: nasm

    begin:
        cmpl    $4, b
        jl      end
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
    end:


 .. class:: comment

    Ceci est la traduction de  :

    .. code-block:: c

       if(b>=4)
         a++;


Question 4. Instructions conditionnelles
----------------------------------------

Les instructions conditionnelles sont fréquemment utilisées en langage C et en assembleur. Considérons le fragment de programme C ci-dessous :

 .. code-block:: c

   if(a<=b)
     c++;


Une seule des séquences d'instructions en assembleur ci-dessous correspond à ce fragment de code C. Laquelle ?


.. class:: positive

-
 .. code-block:: nasm

     if:
        movl    a, %eax
        cmpl    b, %eax
        jg      next
        movl    c, %eax
        addl    $1, %eax
        movl    %eax, c
     next:

-
 .. code-block:: nasm

    if:
        movl    b, %eax
        cmpl    a, %eax
        jl      next
        movl    c, %eax
        addl    $1, %eax
        movl    %eax, c
    next:

 .. class:: comment

       Ceci est en fait l'implémentation de :

       .. code-block:: c

           if(b>=a)
             c++;


.. class:: negative

-
 .. code-block:: nasm

    if:
        movl    a, %eax
        cmpl    b, %eax
        jne     next
        movl    c, %eax
        addl    $1, %eax
        movl    %eax, c
    next:

 .. class:: comment

       Ceci est l'implémentation de :

       .. code-block:: c

           if(a==b)
    	      c++;

-
 .. code-block:: nasm

    if:
        movl    a, %eax
        cmpl    b, %eax
        jle     next
        movl    c, %eax
        addl    $1, %eax
        movl    %eax, c
    next:

 .. class:: comment

       Ceci est l'implémentation de :

       .. code-block:: c

          if(a>b)
    	    c++;

-
 .. code-block:: nasm

    if:
        movl    a, %eax
        cmpl    b, %eax
        jge     next
        movl    c, %eax
        addl    $1, %eax
        movl    %eax, c
    next:

 .. class:: comment

       Ceci est l'implémentation de :

       .. code-block:: c

          if(a<b)
    	    c++;

-
 .. code-block:: nasm

    if:
        movl    a, %eax
        cmpl    b, %eax
        je      next
        movl    c, %eax
        addl    $1, %eax
        movl    %eax, c
    next:

 .. class:: comment

       Ceci est l'implémentation de :

       .. code-block:: c

          if(a!=b)
    	    c++;

Question 5. Instructions conditionnelles
----------------------------------------

L'instruction conditionnelle ``if() ... else `` se retrouve dans de nombreux programmes en langage C. Considérons l'instruction ``if() ... else`` simple ci-dessous dans laquelle ``a`` et ``b`` sont des variables globales de type ``int`` :

.. code-block:: c

  if(a>=b)
    a++;
  else
    b++;

Parmi les séquences d'assembleur ci-dessous, une seule est une traduction correcte de cette instruction conditionnelle. Laquelle ?

.. class:: positive

-
 .. code-block:: nasm

     movl    a, %eax
     cmpl    b, %eax
     jl      label
     movl    a, %eax
     addl    $1, %eax
     movl    %eax, a
     jmp     end
   label:
     movl    b, %eax
     addl    $1, %eax
     movl    %eax, b
   end:

-
 .. code-block:: nasm

        movl    b, %eax
        cmpl    a, %eax
        jg      label
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
        jmp     end
    label:
        movl    b, %eax
        addl    $1, %eax
        movl    %eax, b
    end:


 .. class:: comment

       Ceci est la traduction de :

       .. code-block:: c

          if(b<=a)
    	   a++;
  	  else
    	   b++;


.. class:: negative


-
 .. code-block:: nasm


        movl    a, %eax
        cmpl    b, %eax
        jl      label
        movl    b, %eax
        addl    $1, %eax
        movl    %eax, b
        jmp     end
     label:
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
     end:


 .. class:: comment

       Ceci est la traduction de :

       .. code-block:: c

          if(a>=b)
   	   b++;
  	  else
    	   a++;

-
 .. code-block:: nasm


        movl    b, %eax
        cmpl    a, %eax
        jge     label
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
        jmp     end
     label:
        movl    b, %eax
        addl    $1, %eax
        movl    %eax, b
     end:




 .. class:: comment

       Ceci est la traduction de :

       .. code-block:: c

         if(b<a)
    	  a++;
  	 else
    	  b++;

-
 .. code-block:: nasm

        movl    b, %eax
        cmpl    a, %eax
        jle     label
        movl    b, %eax
        addl    $1, %eax
        movl    %eax, b
        jmp     .LBB4_3
     label:
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
     end:

 .. class:: comment

       Ceci est la traduction de :

       .. code-block:: c

         if(b>a)
    	  b++;
  	 else
    	  a++;

-
 .. code-block:: nasm

        movl    a, %eax
        cmpl    b, %eax
        jl      label
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
    label:
        movl    b, %eax
        addl    $1, %eax
        movl    %eax, b
    end:

 .. class:: comment

       Ceci est la traduction de :

       .. code-block:: c

          if(a>=b) {
    	    a++;
   	  }
   	  b++;



Question 6. Boucles ``while``
-----------------------------

Les boucles ``while`` sont fréquemment utilisées dans des programmes C. Considérons la boucle suivante qui utilise des variables globales (toutes de type ``int``):

 .. code-block:: c

    while(a!=c)
    {
     a++;
     b=b+c;
    }


Parmi les séquences d'assembleur ci-dessous, une seule est une traduction correcte de cette boucle ``while``. Laquelle ?

.. class:: positive

-
 .. code-block:: nasm

     begin:
        movl    a, %eax
        cmpl    c, %eax
        je      end
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
        movl    b, %eax
        addl    c, %eax
        movl    %eax, b
        jmp     begin
     end:

-
 .. code-block:: nasm

     begin:
        movl    c, %eax
        cmpl    a, %eax
        je      end
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
        movl    b, %eax
        addl    c, %eax
        movl    %eax, b
        jmp     begin
     end:


.. class:: negative

-
 .. code-block:: nasm

    begin:
        movl    c, %eax
        cmpl    a, %eax
        jle     end
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
        movl    b, %eax
        addl    c, %eax
        movl    %eax, b
        jmp     begin
    end:

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       while(c>a)
       {
        a++;
    	b=b+c;
       }

-
 .. code-block:: nasm

    begin:
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
        movl    b, %eax
        addl    c, %eax
        movl    %eax, b
        movl    c, %eax
        cmpl    a, %eax
        jne     begin
     end:

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       do
       {
         a++;
    	 b=b+c;
       }
       while(c!=a);

-
 .. code-block:: nasm

    begin:
        movl    c, %eax
        cmpl    a, %eax
        jne     end
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
        movl    b, %eax
        addl    c, %eax
        movl    %eax, b
        jmp     begin
    end:

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       while(c==a)
       {
        a++;
    	b=b+c;
       }


Question 7. Boucles ``for``
---------------------------

Rares sont les programmes C qui ne contiennent pas de boucles ``for``. Considérons la boucle ci-dessous qui utilise uniquement des variables globales (de type ``int``) :

.. code-block:: c

  for(a=0;a<c;a++) {
    b=b-c;
  }

Parmi les séquences d'instructions en assembleur ci-dessous, une seule traduit correctement la boucle ``for`` ci-dessus. Laquelle ?


.. class:: positive

-
 .. code-block:: nasm

    begin:
        movl    $0, a
    loop:
        movl    a, %eax
        cmpl    c, %eax
        jge     end
        movl    b, %eax
        subl    c, %eax
        movl    %eax, b
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
        jmp     loop
     end:

-
 .. code-block:: nasm

    begin:
        movl    $0, a
    loop:
        movl    c, %eax
        cmpl    a, %eax
        jle     end
        movl    b, %eax
        subl    c, %eax
        movl    %eax, b
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
        jmp     loop
     end:

.. class:: negative

-
 .. code-block:: nasm

    begin:
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
    loop:
        movl    c, %eax
        cmpl    a, %eax
        jle     end
        movl    b, %eax
        subl    c, %eax
        movl    %eax, b
        movl    $0, a
        jmp     loop
    end:


 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       for(a=a+1;c>a;a=0) {
         b=b-c;
       }

-
 .. code-block:: nasm

    begin:
        movl    $0, a
    loop:
        movl    a, %eax
        cmpl    c, %eax
        jg      end
        movl    b, %eax
        subl    c, %eax
        movl    %eax, b
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
        jmp     loop
     end:

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

      for(a=0;a<=c;a++) {
        b=b-c;
      }

-
 .. code-block:: nasm

    begin:
        movl    $0, a
        movl    a, %eax
        cmpl    c, %eax
        jge     end
        movl    b, %eax
        subl    c, %eax
        movl    %eax, b
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
    end:

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

      a=0;
      if(a<c) {
        b=b-c;
    	a++;
      }

-
 .. code-block:: nasm

    begin:
    loop:
        movl    a, %eax
        cmpl    c, %eax
        jge     end
        movl    $0, a
        movl    b, %eax
        subl    c, %eax
        movl    %eax, b
        movl    a, %eax
        addl    $1, %eax
        movl    %eax, a
        jmp     loop

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

      for(;a<c;a++) {
        a=0;
   	b=b-c;
      }


Question 8. Fonctions
---------------------

Un programme C contient en général de nombreuses fonctions. Considérons une fonction simple qui effectue un calcul en utilisant un argument et une variable globale (``a``) :

.. code-block:: c


   int f(int i)
   {
     return i+a;
   }
   

Parmi les séquences d'instructions en assembleur ci-dessous, une seule traduit correctement la fonction ci-dessus. Laquelle ?

.. class:: positive

-
 .. code-block:: nasm

        pushl   %eax
        movl    8(%esp), %eax
        movl    %eax, (%esp)
        movl    (%esp), %eax
        addl    a, %eax
        popl    %edx
        ret



-
 .. code-block:: nasm

        subl    $8, %esp
        movl    12(%esp), %eax
        movl    %eax, 4(%esp)
        movl    a, %eax
        movl    %eax, (%esp)
        movl    (%esp), %eax
        addl    4(%esp), %eax
        addl    $8, %esp
        ret

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       int f(int i)
       {
         int j=a;
  	 return j+i;
       }


.. class:: negative

-
 .. code-block:: nasm

        subl    $8, %esp
        movl    12(%esp), %eax
        movl    %eax, 4(%esp)
        movl    4(%esp), %eax
        addl    a, %eax
        movl    %eax, (%esp)
        addl    $8, %esp
        ret


 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       void f3(int i) // incorrect
       {
         int j=i+a;
       }

-
 .. code-block:: nasm

        pushl   %eax
        movl    (%esp), %eax
        addl    a, %eax
        popl    %edx
        ret

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c


       int f()
       {
        int i;
  	return i+a;
       }


-
 .. code-block:: nasm

        pushl   %eax
        movb    8(%esp), %al
        movb    %al, 3(%esp)
        movsbl  3(%esp), %ecx
        addl    a, %ecx
        movl    %ecx, %eax
        popl    %edx
        ret


 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       int f(char c)
       {
         return c+a;
       }

-
 .. code-block:: nasm

        pushl   %eax
        movb    8(%esp), %al
        movb    %al, 3(%esp)
        movsbl  3(%esp), %ecx
        addl    a, %ecx
        movb    %cl, %al
        movsbl  %al, %eax
        popl    %edx
        ret

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       char f(char c)
       {
         return c+a;
       }





Question 9. Fonction ``max``
----------------------------

Considérons la fonction C qui calcule le maximum entre deux entiers :

.. code-block:: c

   int max(int i, int j) {
   if (i>j)
     return i;
   else
     return j;
   }

Parmi les groupes d'instructions ci-dessous, un seul est la traduction de cette fonction. Lequel ?

.. class:: positive

-
 .. code-block:: nasm


    max:
        subl    $12, %esp
        movl    20(%esp), %eax
        movl    16(%esp), %ecx
        movl    %ecx, 4(%esp)
        movl    %eax, (%esp)
        movl    4(%esp), %eax
        cmpl    (%esp), %eax
        jle     next
        movl    4(%esp), %eax
        movl    %eax, 8(%esp)
        jmp     label
    next:
        movl    (%esp), %eax
        movl    %eax, 8(%esp)
    label:
        movl    8(%esp), %eax
        addl    $12, %esp
        ret


-
 .. code-block:: nasm

    max2:
        subl    $12, %esp
        movl    20(%esp), %eax
        movl    16(%esp), %ecx
        movl    %ecx, 4(%esp)
        movl    %eax, (%esp)
        movl    4(%esp), %eax
        cmpl    (%esp), %eax
        jge     label1
        movl    (%esp), %eax
        movl    %eax, 8(%esp)
        jmp     label2
    label1:
        movl    4(%esp), %eax
        movl    %eax, 8(%esp)
    label2:
        movl    8(%esp), %eax
        addl    $12, %esp
        ret


 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       int max(int i, int j) {
        if (i<j)
   	 return j;
 	  else
    	  return i;
       }


.. class:: negative

-
 .. code-block:: nasm

    max:
        subl    $8, %esp
        movl    12(%esp), %eax
        movl    %eax, (%esp)
        movl    (%esp), %eax
        cmpl    (%esp), %eax
        jge     label1
        movl    (%esp), %eax
        movl    %eax, 4(%esp)
        jmp     label2
    label1:
        movl    (%esp), %eax
        movl    %eax, 4(%esp)
    label2:
        movl    4(%esp), %eax
        addl    $8, %esp
        ret

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c


       int max(int i) {
         if (i<i)
    	  return i;
  	 else
    	 return i;
	 }

-
 .. code-block:: nasm

    max:
        subl    $12, %esp
        movl    20(%esp), %eax
        movl    16(%esp), %ecx
        movl    %ecx, 4(%esp)
        movl    %eax, (%esp)
        movl    4(%esp), %eax
        cmpl    (%esp), %eax
        jge     label1
        movl    (%esp), %eax
        movl    %eax, 8(%esp)
        jmp     label2
    label1:
        movl    (%esp), %eax
        movl    %eax, 8(%esp)
    label2:
        movl    8(%esp), %eax
        addl    $12, %esp
        ret

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       int max4(int i, int j) { //incorrect
       if (i<j)
         return j;
  	 else
         return j;
	 }


-
 .. code-block:: nasm

    max:
        subl    $12, %esp
        movl    20(%esp), %eax
        movl    16(%esp), %ecx
        movl    %ecx, 4(%esp)
        movl    %eax, (%esp)
        movl    4(%esp), %eax
        cmpl    (%esp), %eax
        jge     label1
        movl    4(%esp), %eax
        movl    %eax, 8(%esp)
        jmp     label2
    label1:
        movl    (%esp), %eax
        movl    %eax, 8(%esp)
    label2:
        movl    8(%esp), %eax
        addl    $12, %esp
        ret



 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       int max5(int i, int j) { //incorrect
       if (i<j)
        return i;
       else
        return j;
       }

Question 10. Fonctions récursives
---------------------------------

Les fonctions récursives sont parfois utilisées en langage C. Lors de leur exécution, la pile permet de stocker temporairement les valeurs des variables et les adresses de retour. Considérons la fonction récursive suivante (où ``a`` est une variable globale) :

.. code-block:: c

   int f(int i)
   {
    return a+f(i-1);
   }

Parmi les séquences d'instructions assembleur ci-dessous, une seule est une traduction correctement de cette fonction. Laquelle ?

.. class:: positive

-
 .. code-block:: nasm


    f:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $12, %esp
        movl    8(%ebp), %eax
        movl    %eax, -4(%ebp)
        movl    a, %eax
        movl    -4(%ebp), %ecx
        subl    $1, %ecx
        movl    %ecx, (%esp)
        movl    %eax, -8(%ebp)
        calll   f
        movl    -8(%ebp), %ecx
        addl    %eax, %ecx
        movl    %ecx, %eax
        addl    $12, %esp
        popl    %ebp
        ret


-
 .. code-block:: nasm

    f:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $12, %esp
        movl    8(%ebp), %eax
        movl    %eax, -4(%ebp)
        movl    -4(%ebp), %eax
        subl    $1, %eax
        movl    %eax, (%esp)
        calll   f
        movl    %eax, -8(%ebp)
        movl    -8(%ebp), %eax
        addl    a, %eax
        addl    $12, %esp
        popl    %ebp
        ret



 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       int f(int i)
       {
       int j=f(i-1);
       return j+a;
       }


.. class:: negative

-
 .. code-block:: nasm

    f:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $12, %esp
        movl    8(%ebp), %eax
        movl    %eax, -4(%ebp)
        movl    a, %eax
        movl    -4(%ebp), %ecx
        movl    %ecx, (%esp)
        movl    %eax, -8(%ebp)
        calll   f
        movl    -8(%ebp), %ecx
        addl    %eax, %ecx
        movl    %ecx, %eax
        addl    $12, %esp
        popl    %ebp
        ret


 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       int f(int i)
       {
        return a+f(i);
      }

-
 .. code-block:: nasm

    f:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $8, %esp
        movl    8(%ebp), %eax
        movl    %eax, -4(%ebp)
        movl    -4(%ebp), %eax
        addl    a, %eax
        movl    %eax, (%esp)
        calll   f
        addl    $8, %esp
        popl    %ebp
        ret

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       int f(int i) // incorrect
       {
        return f(i+a);
       }

-
 .. code-block:: nasm

        pushl   %ebp
        movl    %esp, %ebp
        subl    $12, %esp
        movl    8(%ebp), %eax
        movl    %eax, -4(%ebp)
        movl    -4(%ebp), %eax
        subl    $1, %eax
        movl    %eax, (%esp)
        calll   f
        movl    %eax, -8(%ebp)
        movl    a, %eax
        addl    $12, %esp
        popl    %ebp
        ret

 .. class:: comment

    Ceci est la traduction de :

    .. code-block:: c

       int f(int i)
       {
         int j=f(i-1);
 	 return a;
      }


.. include:: ../../../links.rst
.. include:: ../../../man_links.rst
.. include:: ../../../incl_links.rst
