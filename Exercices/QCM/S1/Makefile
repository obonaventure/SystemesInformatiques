####################################################################
#
#  Makefile for SINF1252 QCM
#  OB, Jan 2013
# 
####################################################################

MISSION=1

EXNAME=Mission-$(MISSION)

RST_FILES=qcm-$(MISSION).rst

RST_FORM=../rst-form/js/jquery-1.7.2.min.js ../rst-form/js/jquery-shuffle.js ../rst-form/js/rst-form.js

IMAGES=../rst-form/images/correct.png ../rst-form/images/false.png

CSS=../rst-form/css/html4css1.css,../rst-form/css/rst-form.css,../rst-form/css/pygments.css


.PHONY : qcm all

qcm: 	$(RST_FILES)
	echo "Preparing QCM files"
	test -d SINF1252 || mkdir SINF1252
	test -d SINF1252/images || mkdir SINF1252/images
	test -d SINF1252/js || mkdir SINF1252/js
	@for i in $(RST_FILES); do\
	( rst2html.py --stylesheet-path=$(CSS)  $$i > SINF1252/$(EXNAME)-qcm.html ; ) ; done
	@for i in $(RST_FORM); do \
	( cp $$i SINF1252/js ;) ; done
	@for i in $(IMAGES); do \
	( cp $$i SINF1252/images ;) ; done


all: qcm
	cd SINF1252 && zip -9rp SINF1252-$(MISSION).zip *pdf js/* images/* *.html $(EXNAME).zip

clean:
	-rm -r SINF1252/*
