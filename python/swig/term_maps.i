/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
%module term_maps
%{
#include "ggtk/TermProbabilityMap.hpp"
#include "ggtk/TermInformationContentMap.hpp"
#include "ggtk/TermDepthMap.hpp"
%}

%include "utility_types.i"
%include "boost_types.i"
%include "ggtk/TermProbabilityMap.hpp"
%include "ggtk/TermInformationContentMap.hpp"
%include "ggtk/TermDepthMap.hpp"


