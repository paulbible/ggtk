/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
%module anno_parsers
%{
#include "ggtk/EvidencePolicyInterface.hpp"
#include "ggtk/AllowedSetEvidencePolicy.hpp"
#include "ggtk/DisallowedSetEvidencePolicy.hpp"
#include "ggtk/ExperimentalEvidencePolicy.hpp"

#include "ggtk/AnnotationParserInterface.hpp"
#include "ggtk/EntrezGene2GoAnnotationParser.hpp"
#include "ggtk/GoaAnnotationParser.hpp"
#include "ggtk/GafAnnotationParser.hpp"
#include "ggtk/MgiAnnotationParser.hpp"
%}

%newobject AnnotationParserInterface::parseAnnotationFile;
%newobject AnnotationParserInterface::clone;

%include "utility_types.i"
%include "boost_types.i"
%include "go_enums.i"

%include "ggtk/EvidencePolicyInterface.hpp"
%include "ggtk/AllowedSetEvidencePolicy.hpp"
%include "ggtk/DisallowedSetEvidencePolicy.hpp"
%include "ggtk/ExperimentalEvidencePolicy.hpp"

%include "ggtk/AnnotationParserInterface.hpp"
%include "ggtk/EntrezGene2GoAnnotationParser.hpp"
%include "ggtk/GoaAnnotationParser.hpp"
%include "ggtk/GafAnnotationParser.hpp"
%include "ggtk/MgiAnnotationParser.hpp"


