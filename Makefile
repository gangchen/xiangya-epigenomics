#
# Makefile for Xiangya-Epigenomics project
# Author: Gang Chen <chengangcs@gmail.com>
# Created Date: Dec 25, 2011
#
#

xyeg : xyeg.cpp gene.h cpg.h tss.h genes_ucsc.h cpg_ucsc.h tss_dbtss.h cpgs.h
	g++ xyeg.cpp -o xyeg -Wall
clean:
	rm xyeg