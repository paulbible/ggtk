/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
%module term_set_sim
%{
#include "ggtk/TermSimilarityInterface.hpp"
#include "ggtk/TermSetSimilarityInterface.hpp"

#include "ggtk/AllPairsAverageSetSimilarity.hpp"
#include "ggtk/AllPairsMaxSetSimilarity.hpp"
#include "ggtk/BestMatchAverageSetSimilarity.hpp"
#include "ggtk/GentlemanSimUISetSimilarity.hpp"
#include "ggtk/PesquitaSimGICSetSimilarity.hpp"
#include "ggtk/JaccardSetSimilarity.hpp"
#include "ggtk/MazanduSimDICSetSimilarity.hpp"
#include "ggtk/MazanduSimUICSetSimilarity.hpp"

%}

%include "utility_types.i"
%include "boost_types.i"

%include "ggtk/TermSimilarityInterface.hpp"
%include "ggtk/TermSetSimilarityInterface.hpp"

%include "ggtk/AllPairsAverageSetSimilarity.hpp"
%include "ggtk/AllPairsMaxSetSimilarity.hpp"
%include "ggtk/BestMatchAverageSetSimilarity.hpp"
%include "ggtk/GentlemanSimUISetSimilarity.hpp"
%include "ggtk/PesquitaSimGICSetSimilarity.hpp"
%include "ggtk/MazanduSimDICSetSimilarity.hpp"
%include "ggtk/MazanduSimUICSetSimilarity.hpp"
%include "ggtk/JaccardSetSimilarity.hpp"

