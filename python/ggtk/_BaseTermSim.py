'''
  Copyright (c) 2016 Paul W. Bible

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
'''
"""
_BaseTermSim Module encapsulates the base class BaseTermSim.
"""
class BaseTermSim(object):
    """
    An abstract term similarity class to provide a nice interface
    to python for a number of C++ term similarity classes.
    """
    def __init__(self, sim_proxy):
        """
        Constructs the class using a swig proxy object
        """
        self.term_sim = sim_proxy

    def _printMembers(self):
        """
        DEV: lets the developer peek at the members of the swig class
        """
        for val in dir(self.term_map):
            print val

    def calculateTermSimilarity(self, term_a, term_b):
        """
        Return the similarity between the two terms
        """
        return self.term_sim.calculateTermSimilarity(term_a, term_b)

    def calculateNormalizedTermSimilarity(self, term_a, term_b):
        """
        Return the similarity between the two terms
        """
        return self.term_sim.calculateNormalizedTermSimilarity(term_a, term_b)

    def termSimilarity(self, term_a, term_b):
        """
        Return the similarity between the two terms, a shorter method name
        """
        return self.term_sim.calculateNormalizedTermSimilarity(term_a, term_b)
