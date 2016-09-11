#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import unittest

if __name__ == '__main__':
    suite = unittest.TestLoader().discover(".")
    unittest.TextTestRunner(verbosity=2).run(suite)

