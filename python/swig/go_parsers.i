/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
%module go_parsers
%{

#include "ggtk/RelationshipPolicyInterface.hpp"
#include "ggtk/AllowedSetRelationshipPolicy.hpp"
#include "ggtk/StandardRelationshipPolicy.hpp"

#include "ggtk/GoParserInterface.hpp"
#include "ggtk/AllowedRelationshipOboGoParser.hpp"
#include "ggtk/AllowedRelationshipXmlGoParser.hpp"
#include "ggtk/RapidXmlGoParser.hpp"
#include "ggtk/StandardOboGoParser.hpp"
#include "ggtk/StandardXmlGoParser.hpp"
%}

%include "utility_types.i"
%include "boost_types.i"

%newobject GoParserInterface::parseGoFile;
%newobject GoParserInterface::clone;


%include "ggtk/RelationshipPolicyInterface.hpp"
%include "ggtk/AllowedSetRelationshipPolicy.hpp"
%include "ggtk/StandardRelationshipPolicy.hpp"

%include "ggtk/GoParserInterface.hpp"
%include "ggtk/AllowedRelationshipOboGoParser.hpp"
%include "ggtk/AllowedRelationshipXmlGoParser.hpp"
%include "ggtk/RapidXmlGoParser.hpp"
%include "ggtk/StandardOboGoParser.hpp"
%include "ggtk/StandardXmlGoParser.hpp"

