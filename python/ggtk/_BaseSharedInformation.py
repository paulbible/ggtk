#==============================================================================
#  Copyright (c) 2016 Paul W. Bible
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================
"""
The _BaseSharedInformation module encapsulates the BaseSharedInformation class.
"""
class BaseSharedInformation(object):
    """
    An abstract shared infromation class to provide a nice interface
    to python for a number of C++ shared information classes.
    """
    def __init__(self, si_proxy):
        self.term_si = si_proxy

    def _printMembers(self):
        """
        DEV: lets the developer peek at the members of the swig class
        """
        for val in dir(self.term_so):
            print val

    def sharedInformation(self, term_a, term_b=None):
        """
        Return the shared information the two terms
        """
        if term_b == None:
            return self.term_si.sharedInformation(term_a)
        else:
            return self.term_si.sharedInformation(term_a, term_b)

    def maxInformationContent(self, term):
        """
        Return the maximun information allowed by the corpus for normalization
        """
        return self.term_si.maxInformationContent(term)

    def hasTerm(self, term):
        """
        Returns true if the term can be found in the databse, false otherwise
        """
        return self.term_si.hasTerm(term)

