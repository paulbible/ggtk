/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
%include <std_string.i>
%include <carrays.i>
%include <std_common.i>
%include <std_vector.i>

%template(SizeVector) std::vector<size_t>;


%array_class(std::string, StringArray)
%template(StringVector) std::vector<std::string>;
%template(DoubleVector) std::vector<double>;

