'''
  Copyright (c) 2016 Paul W. Bible

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
'''

"""
The _BaseTermMap Module encapsulates the BaseTermMap base class.
"""

class BaseTermMap(object):
    """
    An abstract map class for go term maps
    Since the probability, information content,
    and depth maps will have the same inteface,
    this class should reduce redundant code.
    """

    def __init__(self, map_proxy):
        self.term_map = map_proxy

    def __contains__(self, term_key):
        """
        Adds functionality for built in methods
        """
        return self.term_map.hasTerm(term_key)

    def has_key(self, term_key):
        """
        Test if the map contains a key
        """
        return self.term_map.hasTerm(term_key)

    def __getitem__(self, term_key):
        """
        Implemented to provide bracket [] access for keys
        mymap["some_key"] --> probability
        """
        if term_key in self:
            return self.term_map.getValue(term_key)
        else:
            raise KeyError("%s key not found "%term_key)

    def _printMembers(self):
        """
        DEV: lets the developer peek at the members of the swig class
        """
        for val in dir(self.term_map):
            print val

    def values(self):
        """
        Returns the values of the map as a list
        """
        return self.term_map.getValues()

    def keys(self):
        """
        Returns the keys of the map as a list
        """
        return self.term_map.getKeys()

