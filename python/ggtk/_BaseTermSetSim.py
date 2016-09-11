'''
  Copyright (c) 2016 Paul W. Bible

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
'''

"""
The _BaseTermSetSim module encapsulates BaseTermSetSim class.
"""
import app_utilities

class BaseTermSetSim(object):
    """
    An abstract term set similarity class to provide a nice interface
    to python for a number of C++ term set similarity classes.
    """
    def __init__(self, sim_proxy):
        self.set_sim = sim_proxy

    def _printMembers(self):
        """
        DEV: lets the developer peek at the members of the swig class
        """
        for val in dir(self.set_sim):
            print val

    def calculateSimilarity(self, term_set_a, term_set_b):
        """
        Return the similarity between the two sets of terms
        """
        s1 = app_utilities.vecToSet(term_set_a)
        s2 = app_utilities.vecToSet(term_set_b)
        return self.set_sim.calculateSimilarity(s1, s2)

