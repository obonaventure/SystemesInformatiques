####################################################################
#
#  Makefile for SINF1252 QCM
#  OB, Jan 2013
# 
####################################################################

MISSION=1

EXNAME=Mission-$(MISSION)

RST_FILES=qcm-$(MISSION).rst

CSS=../rst-form/css/html4css1.css,../rst-form/css/rst-form.css,../rst-form/css/pygments.css

.PHONY : qcm all

qcm: $(RST_FILES)
	@for i in $(RST_FILES); do\
	( rst2html.py --stylesheet-path=$(CSS)  $$i > ../../../_static/$(EXNAME)-qcm.html ; ) ; done


all: qcm

clean:
	-rm -r $(EXNAME)
