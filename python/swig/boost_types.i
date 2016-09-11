/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
%include <boost/unordered_set.hpp>

namespace boost{
  template <typename T1> class unordered_set{};
}

%template(BoostSet) boost::unordered_set<std::string>;
