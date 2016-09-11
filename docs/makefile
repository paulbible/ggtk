# Copyright (c) 2016 Paul W. Bible
all:
	doxygen ggtk_config 1> out.txt 2> err.txt
	cd latex; make > latex_out.txt
	cp latex/refman.pdf ggtk_reference.pdf
	

clean:
	rm -r html
	rm -r latex
	rm -r xml
	rm -r ggtk_reference.pdf
