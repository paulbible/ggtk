#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
from collections import defaultdict
import os

ggtk_version = '0.1.0'

if "BOOST" in os.environ:
    boost_root = os.environ['BOOST']
else:
    boost_root = "."

'''
The following 2 blocks add compiler flags needed by windows
Modified from:
http://stackoverflow.com/questions/30985862/how-to-identify-compiler-before-defining-cython-extensions
'''
BUILD_ARGS = defaultdict(lambda: ['-O3', '-g0'])
for compiler, args in [
    ('msvc', ['/EHsc', '/DHUNSPELL_STATIC', '/O2']),
    ('gcc', ['-O3', '-g0'])]:
    BUILD_ARGS[compiler] = args


class build_ext_compiler_check(build_ext):
    def build_extensions(self):
        compiler = self.compiler.compiler_type
        args = BUILD_ARGS[compiler]
        for ext in self.extensions:
            ext.extra_compile_args = args
        build_ext.build_extensions(self)


ext_mod_go_enums        = Extension("ggtk._go_enums",
                                    sources = ["ext/go_enums_wrap.cxx"],
                                    include_dirs=["../", boost_root])

ext_mod_go_graph        = Extension("ggtk._go_graph",
                                    sources = ["ext/go_graph_wrap.cxx"],
                                    include_dirs=["../", boost_root])

ext_mod_go_parsers      = Extension("ggtk._go_parsers",
                                    sources = ["ext/go_parsers_wrap.cxx"],
                                    include_dirs=["../", boost_root])

ext_mod_app_utilities   = Extension("ggtk._app_utilities",
                                    sources = ["ext/app_utilities_wrap.cxx"],
                                    include_dirs=["../", boost_root])

ext_mod_anno_parsers    = Extension("ggtk._anno_parsers",
                                    sources = ["ext/anno_parsers_wrap.cxx"],
                                    include_dirs=["../", boost_root])

ext_mod_annotation_data = Extension("ggtk._annotation_data",
                                    sources = ["ext/annotation_data_wrap.cxx"],
                                    include_dirs=["../", boost_root])

ext_mod_term_maps       = Extension("ggtk._term_maps",
                                    sources = ["ext/term_maps_wrap.cxx"],
                                    include_dirs=["../", boost_root])

ext_mod_term_sim        = Extension("ggtk._term_sim",
                                    sources = ["ext/term_sim_wrap.cxx"],
                                    include_dirs=["../", boost_root])

ext_mod_term_set_sim    = Extension("ggtk._term_set_sim",
                                    sources = ["ext/term_set_sim_wrap.cxx"],
                                    include_dirs=["../", boost_root])

ext_enrichment_tools    = Extension("ggtk._enrichment_tools",
                                    sources = ["ext/enrichment_tools_wrap.cxx"],
                                    include_dirs=["../", boost_root])

packages = ["ggtk", ]

setup(name="ggtk",
      version=ggtk_version,
      ext_modules=[ext_mod_go_enums,
                   ext_mod_go_graph,
                   ext_mod_go_parsers,
                   ext_mod_app_utilities,
                   ext_mod_anno_parsers,
                   ext_mod_annotation_data,
                   ext_mod_term_maps,
                   ext_mod_term_sim,
                   ext_mod_term_set_sim,
                   ext_enrichment_tools],
      packages=packages,
      cmdclass={'build_ext': build_ext_compiler_check})
















