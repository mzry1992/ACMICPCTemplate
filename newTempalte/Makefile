all: pdf

pdf: mzry.tex
	astyle */*.cpp -A2 --indent=spaces=2
	xelatex mzry.tex
	xelatex mzry.tex

clean:
	rm -f *.toc *.pdf
