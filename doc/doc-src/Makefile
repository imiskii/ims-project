#
# Project: simulation_study.tex
# Author: Michal Ľaš
# Date: 03.12.2023
# 


NAME=simulation_study

all: proj

proj: $(NAME).tex
	pdflatex $(NAME).tex
	make bibtex 
	pdflatex $(NAME).tex
	pdflatex $(NAME).tex

	mv ./$(NAME).pdf ../



bibtex: $(NAME).bib
	bibtex $(NAME)


clean:
	rm -f *.dvi
	rm -f *.ps
	rm -f *.aux
	rm -f *.out
	rm -f *.log
	rm -f *.bbl *.blg *.bcf *.run.xml
	rm -f *.gz
	rm -f *.toc
	rm -f *.pdf
#	rm ../$(NAME).pdf
