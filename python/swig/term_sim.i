/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
%module term_sim
%{
#include "ggtk/SharedInformationInterface.hpp"
#include "ggtk/AncestorMeanSharedInformation.hpp"
#include "ggtk/CoutoGraSMSharedInformation.hpp"
#include "ggtk/CoutoGraSMAdjustedSharedInformation.hpp"
#include "ggtk/ExclusivelyInheritedSharedInformation.hpp"
#include "ggtk/FrontierSharedInformation.hpp"
#include "ggtk/MICASharedInformation.hpp"

#include "ggtk/TermSimilarityInterface.hpp"
#include "ggtk/JiangConrathSimilarity.hpp"
#include "ggtk/LinSimilarity.hpp"
#include "ggtk/ModularJiangConrath.hpp"
#include "ggtk/ModularLin.hpp"
#include "ggtk/ModularResnik.hpp"
#include "ggtk/PekarStaabSimilarity.hpp"
#include "ggtk/PrecomputedMatrixTermSimilarity.hpp"
#include "ggtk/RelevanceSimilarity.hpp"
#include "ggtk/ResnikSimilarity.hpp"

#include "ggtk/TermSimilarityWriter.hpp"
%}

%include "utility_types.i"
%include "boost_types.i"

%include "ggtk/SharedInformationInterface.hpp"
%include "ggtk/AncestorMeanSharedInformation.hpp"
%include "ggtk/CoutoGraSMSharedInformation.hpp"
%include "ggtk/CoutoGraSMAdjustedSharedInformation.hpp"
%include "ggtk/ExclusivelyInheritedSharedInformation.hpp"
%include "ggtk/FrontierSharedInformation.hpp"
%include "ggtk/MICASharedInformation.hpp"

%include "ggtk/TermSimilarityInterface.hpp"
%include "ggtk/JiangConrathSimilarity.hpp"
%include "ggtk/LinSimilarity.hpp"
%include "ggtk/ModularJiangConrath.hpp"
%include "ggtk/ModularLin.hpp"
%include "ggtk/ModularResnik.hpp"
%include "ggtk/PekarStaabSimilarity.hpp"
%include "ggtk/PrecomputedMatrixTermSimilarity.hpp"
%include "ggtk/RelevanceSimilarity.hpp"
%include "ggtk/ResnikSimilarity.hpp"

%include "ggtk/TermSimilarityWriter.hpp"


