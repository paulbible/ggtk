# Copyright (c) 2016 Paul W. Bible
PYTHON=/public/users/paul/dev/software/Python-2.7.11
GGTK=/public/users/paul/dev/ggtk_home
BOOST=/public/users/paul/dev/boost_1_60_0

all: go_enum go_graph go_parsers app_utilities anno_parsers annotation_data term_maps term_sim term_set_sim enrichment_tools

go_graph:
	swig -c++ -python -I${GGTK} -I${BOOST} go_graph.i
	g++ -fpic -c go_graph_wrap.cxx -I${PYTHON}/Include -I${PYTHON} -I${GGTK}
	g++ -g -fpic -shared go_graph_wrap.o -o _go_graph.so
	cp go_graph_wrap.cxx ../ext
	cp go_graph.py ../ggtk

go_parsers:
	swig -c++ -python -I${GGTK} -I${BOOST} go_parsers.i
	g++ -fpic -c go_parsers_wrap.cxx -I${PYTHON}/Include -I${PYTHON} -I${GGTK}
	g++ -g -fpic -shared go_parsers_wrap.o -o _go_parsers.so
	cp go_parsers_wrap.cxx ../ext
	cp go_parsers.py ../ggtk

go_enum:
	#swig -v -debug-typemap -debug-typedef -debug-classes -c++ -python -I/public/users/paul/dev/ggtk_home -I${BOOST} go_enums.i
	swig -c++ -python -I${GGTK} -I${BOOST} go_enums.i
	g++ -fpic -c go_enums_wrap.cxx -I${PYTHON}/Include -I${PYTHON} -I${GGTK}
	g++ -g -fpic -shared go_enums_wrap.o -o _go_enums.so
	cp go_enums_wrap.cxx ../ext
	cp go_enums.py ../ggtk

app_utilities:
	swig -c++ -python -I${GGTK} -I${BOOST} app_utilities.i
	g++ -fpic -c app_utilities_wrap.cxx -I${PYTHON}/Include -I${PYTHON} -I${GGTK}
	g++ -g -fpic -shared app_utilities_wrap.o -o _app_utilities.so
	cp app_utilities_wrap.cxx ../ext
	cp app_utilities.py ../ggtk

anno_parsers:
	swig -c++ -python -I${GGTK} -I${BOOST} anno_parsers.i
	g++ -fpic -c anno_parsers_wrap.cxx -I${PYTHON}/Include -I${PYTHON} -I${GGTK}
	g++ -g -fpic -shared anno_parsers_wrap.o -o _anno_parsers.so
	cp anno_parsers_wrap.cxx ../ext
	cp anno_parsers.py ../ggtk

annotation_data:
	swig -c++ -python -I${GGTK} -I${BOOST} annotation_data.i
	g++ -fpic -c annotation_data_wrap.cxx -I${PYTHON}/Include -I${PYTHON} -I${GGTK}
	g++ -g -fpic -shared annotation_data_wrap.o -o _annotation_data.so
	cp annotation_data_wrap.cxx ../ext
	cp annotation_data.py ../ggtk

term_maps:
	swig -c++ -python -I${GGTK} -I${BOOST} term_maps.i
	g++ -fpic -c term_maps_wrap.cxx -I${PYTHON}/Include -I${PYTHON} -I${GGTK}
	g++ -g -fpic -shared term_maps_wrap.o -o _term_maps.so
	cp term_maps_wrap.cxx ../ext
	cp term_maps.py ../ggtk

term_sim:
	swig -c++ -python -I${GGTK} -I${BOOST} term_sim.i
	g++ -fpic -c term_sim_wrap.cxx -I${PYTHON}/Include -I${PYTHON} -I${GGTK}
	g++ -g -fpic -shared term_sim_wrap.o -o _term_sim.so
	cp term_sim_wrap.cxx ../ext
	cp term_sim.py ../ggtk

term_set_sim:
	swig -c++ -python -I${GGTK} -I${BOOST} term_set_sim.i
	g++ -fpic -c term_set_sim_wrap.cxx -I${PYTHON}/Include -I${PYTHON} -I${GGTK}
	g++ -g -fpic -shared term_set_sim_wrap.o -o _term_set_sim.so
	cp term_set_sim_wrap.cxx ../ext
	cp term_set_sim.py ../ggtk


enrichment_tools:
	swig -c++ -python -I${GGTK} -I${BOOST} enrichment_tools.i
	g++ -fpic -c enrichment_tools_wrap.cxx -I${PYTHON}/Include -I${PYTHON} -I${GGTK}
	g++ -g -fpic -shared enrichment_tools_wrap.o -o _enrichment_tools.so
	cp enrichment_tools_wrap.cxx ../ext
	cp enrichment_tools.py ../ggtk


test:
	g++ -fpic -c test.cpp -I${PYTHON}/Include -I${PYTHON} -I${GGTK}
	g++ -g -fpic test.o -o test

tc:
	rm test
	rm test.o

clean: clean_go_enums clean_go_parsers clean_go_graph clean_app_utilities clean_anno_parsers clean_annotation_data clean_term_maps clean_term_sim clean_term_set_sim clean_enrichment_tools

clean_go_enums:
	rm go_enums.py go_enums_wrap.cxx go_enums_wrap.o _go_enums.so ../ext/go_enums_wrap.cxx ../ggtk/go_enums.py

clean_go_parsers:
	rm go_parsers.py go_parsers_wrap.cxx go_parsers_wrap.o _go_parsers.so  ../ext/go_parsers_wrap.cxx ../ggtk/go_parsers.py

clean_go_graph:
	rm go_graph.py go_graph_wrap.cxx go_graph_wrap.o _go_graph.so ../ext/go_graph_wrap.cxx ../ggtk/go_graph.py

clean_app_utilities:
	rm app_utilities.py app_utilities_wrap.cxx app_utilities_wrap.o _app_utilities.so ../ext/app_utilities_wrap.cxx ../ggtk/app_utilities.py

clean_anno_parsers:
	rm anno_parsers.py anno_parsers_wrap.cxx anno_parsers_wrap.o _anno_parsers.so ../ext/anno_parsers_wrap.cxx ../ggtk/anno_parsers.py

clean_annotation_data:
	rm annotation_data.py annotation_data_wrap.cxx annotation_data_wrap.o _annotation_data.so ../ext/annotation_data_wrap.cxx ../ggtk/annotation_data.py

clean_term_maps:
	rm term_maps.py term_maps_wrap.cxx term_maps_wrap.o _term_maps.so ../ext/term_maps_wrap.cxx ../ggtk/term_maps.py

clean_term_sim:
	rm term_sim.py term_sim_wrap.cxx term_sim_wrap.o _term_sim.so ../ext/term_sim_wrap.cxx ../ggtk/term_sim.py

clean_term_set_sim:
	rm term_set_sim.py term_set_sim_wrap.cxx term_set_sim_wrap.o _term_set_sim.so ../ext/term_set_sim_wrap.cxx ../ggtk/term_set_sim.py


clean_enrichment_tools:
	rm enrichment_tools.py enrichment_tools_wrap.cxx enrichment_tools_wrap.o _enrichment_tools.so ../ext/enrichment_tools_wrap.cxx ../ggtk/enrichment_tools.py




