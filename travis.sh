#!/bin/bash

# Flags used here, not in `make html`:
#  -n   Run in nit-picky mode. Currently, this generates warnings for all missing references.
#  -W   Turn warnings into errors. This means that the build stops at the first warning and sphinx-build exits with exit status 1.
cd Theorie
sphinx-build  -nW  -b html . /tmp
cd ../Outils
sphinx-build  -nW  -b html . /tmp
cd ../Exercices
sphinx-build  -nW  -b html . /tmp
cd QCM
make
cd ../..