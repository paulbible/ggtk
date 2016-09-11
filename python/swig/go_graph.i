/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
%module go_graph
%{
#include "ggtk/GoGraph.hpp"
#include "ggtk/GoEnums.hpp"
%}

%include "utility_types.i"
%include "boost_types.i"
%include "go_enums.i"

%include "ggtk/GoGraph.hpp"
