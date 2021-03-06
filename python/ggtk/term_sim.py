# This file was automatically generated by SWIG (http://www.swig.org).
# Version 1.3.40
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.
# This file is compatible with both classic and new-style classes.

from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_term_sim', [dirname(__file__)])
        except ImportError:
            import _term_sim
            return _term_sim
        if fp is not None:
            try:
                _mod = imp.load_module('_term_sim', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _term_sim = swig_import_helper()
    del swig_import_helper
else:
    import _term_sim
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


class SwigPyIterator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SwigPyIterator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SwigPyIterator, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _term_sim.delete_SwigPyIterator
    __del__ = lambda self : None;
    def value(self): return _term_sim.SwigPyIterator_value(self)
    def incr(self, n = 1): return _term_sim.SwigPyIterator_incr(self, n)
    def decr(self, n = 1): return _term_sim.SwigPyIterator_decr(self, n)
    def distance(self, *args): return _term_sim.SwigPyIterator_distance(self, *args)
    def equal(self, *args): return _term_sim.SwigPyIterator_equal(self, *args)
    def copy(self): return _term_sim.SwigPyIterator_copy(self)
    def next(self): return _term_sim.SwigPyIterator_next(self)
    def __next__(self): return _term_sim.SwigPyIterator___next__(self)
    def previous(self): return _term_sim.SwigPyIterator_previous(self)
    def advance(self, *args): return _term_sim.SwigPyIterator_advance(self, *args)
    def __eq__(self, *args): return _term_sim.SwigPyIterator___eq__(self, *args)
    def __ne__(self, *args): return _term_sim.SwigPyIterator___ne__(self, *args)
    def __iadd__(self, *args): return _term_sim.SwigPyIterator___iadd__(self, *args)
    def __isub__(self, *args): return _term_sim.SwigPyIterator___isub__(self, *args)
    def __add__(self, *args): return _term_sim.SwigPyIterator___add__(self, *args)
    def __sub__(self, *args): return _term_sim.SwigPyIterator___sub__(self, *args)
    def __iter__(self): return self
SwigPyIterator_swigregister = _term_sim.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)

class SizeVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SizeVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SizeVector, name)
    __repr__ = _swig_repr
    def iterator(self): return _term_sim.SizeVector_iterator(self)
    def __iter__(self): return self.iterator()
    def __nonzero__(self): return _term_sim.SizeVector___nonzero__(self)
    def __bool__(self): return _term_sim.SizeVector___bool__(self)
    def __len__(self): return _term_sim.SizeVector___len__(self)
    def pop(self): return _term_sim.SizeVector_pop(self)
    def __getslice__(self, *args): return _term_sim.SizeVector___getslice__(self, *args)
    def __setslice__(self, *args): return _term_sim.SizeVector___setslice__(self, *args)
    def __delslice__(self, *args): return _term_sim.SizeVector___delslice__(self, *args)
    def __delitem__(self, *args): return _term_sim.SizeVector___delitem__(self, *args)
    def __getitem__(self, *args): return _term_sim.SizeVector___getitem__(self, *args)
    def __setitem__(self, *args): return _term_sim.SizeVector___setitem__(self, *args)
    def append(self, *args): return _term_sim.SizeVector_append(self, *args)
    def empty(self): return _term_sim.SizeVector_empty(self)
    def size(self): return _term_sim.SizeVector_size(self)
    def clear(self): return _term_sim.SizeVector_clear(self)
    def swap(self, *args): return _term_sim.SizeVector_swap(self, *args)
    def get_allocator(self): return _term_sim.SizeVector_get_allocator(self)
    def begin(self): return _term_sim.SizeVector_begin(self)
    def end(self): return _term_sim.SizeVector_end(self)
    def rbegin(self): return _term_sim.SizeVector_rbegin(self)
    def rend(self): return _term_sim.SizeVector_rend(self)
    def pop_back(self): return _term_sim.SizeVector_pop_back(self)
    def erase(self, *args): return _term_sim.SizeVector_erase(self, *args)
    def __init__(self, *args): 
        this = _term_sim.new_SizeVector(*args)
        try: self.this.append(this)
        except: self.this = this
    def push_back(self, *args): return _term_sim.SizeVector_push_back(self, *args)
    def front(self): return _term_sim.SizeVector_front(self)
    def back(self): return _term_sim.SizeVector_back(self)
    def assign(self, *args): return _term_sim.SizeVector_assign(self, *args)
    def resize(self, *args): return _term_sim.SizeVector_resize(self, *args)
    def insert(self, *args): return _term_sim.SizeVector_insert(self, *args)
    def reserve(self, *args): return _term_sim.SizeVector_reserve(self, *args)
    def capacity(self): return _term_sim.SizeVector_capacity(self)
    __swig_destroy__ = _term_sim.delete_SizeVector
    __del__ = lambda self : None;
SizeVector_swigregister = _term_sim.SizeVector_swigregister
SizeVector_swigregister(SizeVector)

class StringArray(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, StringArray, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, StringArray, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_StringArray(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _term_sim.delete_StringArray
    __del__ = lambda self : None;
    def __getitem__(self, *args): return _term_sim.StringArray___getitem__(self, *args)
    def __setitem__(self, *args): return _term_sim.StringArray___setitem__(self, *args)
    def cast(self): return _term_sim.StringArray_cast(self)
    __swig_getmethods__["frompointer"] = lambda x: _term_sim.StringArray_frompointer
    if _newclass:frompointer = staticmethod(_term_sim.StringArray_frompointer)
StringArray_swigregister = _term_sim.StringArray_swigregister
StringArray_swigregister(StringArray)

def StringArray_frompointer(*args):
  return _term_sim.StringArray_frompointer(*args)
StringArray_frompointer = _term_sim.StringArray_frompointer

class StringVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, StringVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, StringVector, name)
    __repr__ = _swig_repr
    def iterator(self): return _term_sim.StringVector_iterator(self)
    def __iter__(self): return self.iterator()
    def __nonzero__(self): return _term_sim.StringVector___nonzero__(self)
    def __bool__(self): return _term_sim.StringVector___bool__(self)
    def __len__(self): return _term_sim.StringVector___len__(self)
    def pop(self): return _term_sim.StringVector_pop(self)
    def __getslice__(self, *args): return _term_sim.StringVector___getslice__(self, *args)
    def __setslice__(self, *args): return _term_sim.StringVector___setslice__(self, *args)
    def __delslice__(self, *args): return _term_sim.StringVector___delslice__(self, *args)
    def __delitem__(self, *args): return _term_sim.StringVector___delitem__(self, *args)
    def __getitem__(self, *args): return _term_sim.StringVector___getitem__(self, *args)
    def __setitem__(self, *args): return _term_sim.StringVector___setitem__(self, *args)
    def append(self, *args): return _term_sim.StringVector_append(self, *args)
    def empty(self): return _term_sim.StringVector_empty(self)
    def size(self): return _term_sim.StringVector_size(self)
    def clear(self): return _term_sim.StringVector_clear(self)
    def swap(self, *args): return _term_sim.StringVector_swap(self, *args)
    def get_allocator(self): return _term_sim.StringVector_get_allocator(self)
    def begin(self): return _term_sim.StringVector_begin(self)
    def end(self): return _term_sim.StringVector_end(self)
    def rbegin(self): return _term_sim.StringVector_rbegin(self)
    def rend(self): return _term_sim.StringVector_rend(self)
    def pop_back(self): return _term_sim.StringVector_pop_back(self)
    def erase(self, *args): return _term_sim.StringVector_erase(self, *args)
    def __init__(self, *args): 
        this = _term_sim.new_StringVector(*args)
        try: self.this.append(this)
        except: self.this = this
    def push_back(self, *args): return _term_sim.StringVector_push_back(self, *args)
    def front(self): return _term_sim.StringVector_front(self)
    def back(self): return _term_sim.StringVector_back(self)
    def assign(self, *args): return _term_sim.StringVector_assign(self, *args)
    def resize(self, *args): return _term_sim.StringVector_resize(self, *args)
    def insert(self, *args): return _term_sim.StringVector_insert(self, *args)
    def reserve(self, *args): return _term_sim.StringVector_reserve(self, *args)
    def capacity(self): return _term_sim.StringVector_capacity(self)
    __swig_destroy__ = _term_sim.delete_StringVector
    __del__ = lambda self : None;
StringVector_swigregister = _term_sim.StringVector_swigregister
StringVector_swigregister(StringVector)

class DoubleVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DoubleVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DoubleVector, name)
    __repr__ = _swig_repr
    def iterator(self): return _term_sim.DoubleVector_iterator(self)
    def __iter__(self): return self.iterator()
    def __nonzero__(self): return _term_sim.DoubleVector___nonzero__(self)
    def __bool__(self): return _term_sim.DoubleVector___bool__(self)
    def __len__(self): return _term_sim.DoubleVector___len__(self)
    def pop(self): return _term_sim.DoubleVector_pop(self)
    def __getslice__(self, *args): return _term_sim.DoubleVector___getslice__(self, *args)
    def __setslice__(self, *args): return _term_sim.DoubleVector___setslice__(self, *args)
    def __delslice__(self, *args): return _term_sim.DoubleVector___delslice__(self, *args)
    def __delitem__(self, *args): return _term_sim.DoubleVector___delitem__(self, *args)
    def __getitem__(self, *args): return _term_sim.DoubleVector___getitem__(self, *args)
    def __setitem__(self, *args): return _term_sim.DoubleVector___setitem__(self, *args)
    def append(self, *args): return _term_sim.DoubleVector_append(self, *args)
    def empty(self): return _term_sim.DoubleVector_empty(self)
    def size(self): return _term_sim.DoubleVector_size(self)
    def clear(self): return _term_sim.DoubleVector_clear(self)
    def swap(self, *args): return _term_sim.DoubleVector_swap(self, *args)
    def get_allocator(self): return _term_sim.DoubleVector_get_allocator(self)
    def begin(self): return _term_sim.DoubleVector_begin(self)
    def end(self): return _term_sim.DoubleVector_end(self)
    def rbegin(self): return _term_sim.DoubleVector_rbegin(self)
    def rend(self): return _term_sim.DoubleVector_rend(self)
    def pop_back(self): return _term_sim.DoubleVector_pop_back(self)
    def erase(self, *args): return _term_sim.DoubleVector_erase(self, *args)
    def __init__(self, *args): 
        this = _term_sim.new_DoubleVector(*args)
        try: self.this.append(this)
        except: self.this = this
    def push_back(self, *args): return _term_sim.DoubleVector_push_back(self, *args)
    def front(self): return _term_sim.DoubleVector_front(self)
    def back(self): return _term_sim.DoubleVector_back(self)
    def assign(self, *args): return _term_sim.DoubleVector_assign(self, *args)
    def resize(self, *args): return _term_sim.DoubleVector_resize(self, *args)
    def insert(self, *args): return _term_sim.DoubleVector_insert(self, *args)
    def reserve(self, *args): return _term_sim.DoubleVector_reserve(self, *args)
    def capacity(self): return _term_sim.DoubleVector_capacity(self)
    __swig_destroy__ = _term_sim.delete_DoubleVector
    __del__ = lambda self : None;
DoubleVector_swigregister = _term_sim.DoubleVector_swigregister
DoubleVector_swigregister(DoubleVector)

class BoostSet(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, BoostSet, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, BoostSet, name)
    __repr__ = _swig_repr
    def __init__(self): 
        this = _term_sim.new_BoostSet()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _term_sim.delete_BoostSet
    __del__ = lambda self : None;
BoostSet_swigregister = _term_sim.BoostSet_swigregister
BoostSet_swigregister(BoostSet)

class SharedInformationInterface(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SharedInformationInterface, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SharedInformationInterface, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    def sharedInformation(self, *args): return _term_sim.SharedInformationInterface_sharedInformation(self, *args)
    def maxInformationContent(self, *args): return _term_sim.SharedInformationInterface_maxInformationContent(self, *args)
    def hasTerm(self, *args): return _term_sim.SharedInformationInterface_hasTerm(self, *args)
    def isSameOntology(self, *args): return _term_sim.SharedInformationInterface_isSameOntology(self, *args)
    __swig_destroy__ = _term_sim.delete_SharedInformationInterface
    __del__ = lambda self : None;
SharedInformationInterface_swigregister = _term_sim.SharedInformationInterface_swigregister
SharedInformationInterface_swigregister(SharedInformationInterface)

class AncestorMeanSharedInformation(SharedInformationInterface):
    __swig_setmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, AncestorMeanSharedInformation, name, value)
    __swig_getmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, AncestorMeanSharedInformation, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_AncestorMeanSharedInformation(*args)
        try: self.this.append(this)
        except: self.this = this
    def sharedInformation(self, *args): return _term_sim.AncestorMeanSharedInformation_sharedInformation(self, *args)
    def maxInformationContent(self, *args): return _term_sim.AncestorMeanSharedInformation_maxInformationContent(self, *args)
    def hasTerm(self, *args): return _term_sim.AncestorMeanSharedInformation_hasTerm(self, *args)
    def isSameOntology(self, *args): return _term_sim.AncestorMeanSharedInformation_isSameOntology(self, *args)
    __swig_destroy__ = _term_sim.delete_AncestorMeanSharedInformation
    __del__ = lambda self : None;
AncestorMeanSharedInformation_swigregister = _term_sim.AncestorMeanSharedInformation_swigregister
AncestorMeanSharedInformation_swigregister(AncestorMeanSharedInformation)

class CoutoGraSMSharedInformation(SharedInformationInterface):
    __swig_setmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, CoutoGraSMSharedInformation, name, value)
    __swig_getmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, CoutoGraSMSharedInformation, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_CoutoGraSMSharedInformation(*args)
        try: self.this.append(this)
        except: self.this = this
    def getCommonDisjointAncestors(self, *args): return _term_sim.CoutoGraSMSharedInformation_getCommonDisjointAncestors(self, *args)
    def isDisjoint(self, *args): return _term_sim.CoutoGraSMSharedInformation_isDisjoint(self, *args)
    def getNumPaths(self, *args): return _term_sim.CoutoGraSMSharedInformation_getNumPaths(self, *args)
    def sharedInformation(self, *args): return _term_sim.CoutoGraSMSharedInformation_sharedInformation(self, *args)
    def maxInformationContent(self, *args): return _term_sim.CoutoGraSMSharedInformation_maxInformationContent(self, *args)
    def hasTerm(self, *args): return _term_sim.CoutoGraSMSharedInformation_hasTerm(self, *args)
    def isSameOntology(self, *args): return _term_sim.CoutoGraSMSharedInformation_isSameOntology(self, *args)
    __swig_destroy__ = _term_sim.delete_CoutoGraSMSharedInformation
    __del__ = lambda self : None;
CoutoGraSMSharedInformation_swigregister = _term_sim.CoutoGraSMSharedInformation_swigregister
CoutoGraSMSharedInformation_swigregister(CoutoGraSMSharedInformation)

class CoutoGraSMAdjustedSharedInformation(SharedInformationInterface):
    __swig_setmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, CoutoGraSMAdjustedSharedInformation, name, value)
    __swig_getmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, CoutoGraSMAdjustedSharedInformation, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_CoutoGraSMAdjustedSharedInformation(*args)
        try: self.this.append(this)
        except: self.this = this
    def getCommonDisjointAncestors(self, *args): return _term_sim.CoutoGraSMAdjustedSharedInformation_getCommonDisjointAncestors(self, *args)
    def isDisjoint(self, *args): return _term_sim.CoutoGraSMAdjustedSharedInformation_isDisjoint(self, *args)
    def getNumPaths(self, *args): return _term_sim.CoutoGraSMAdjustedSharedInformation_getNumPaths(self, *args)
    def sharedInformation(self, *args): return _term_sim.CoutoGraSMAdjustedSharedInformation_sharedInformation(self, *args)
    def maxInformationContent(self, *args): return _term_sim.CoutoGraSMAdjustedSharedInformation_maxInformationContent(self, *args)
    def hasTerm(self, *args): return _term_sim.CoutoGraSMAdjustedSharedInformation_hasTerm(self, *args)
    def isSameOntology(self, *args): return _term_sim.CoutoGraSMAdjustedSharedInformation_isSameOntology(self, *args)
    __swig_destroy__ = _term_sim.delete_CoutoGraSMAdjustedSharedInformation
    __del__ = lambda self : None;
CoutoGraSMAdjustedSharedInformation_swigregister = _term_sim.CoutoGraSMAdjustedSharedInformation_swigregister
CoutoGraSMAdjustedSharedInformation_swigregister(CoutoGraSMAdjustedSharedInformation)

class ExclusivelyInheritedSharedInformation(SharedInformationInterface):
    __swig_setmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, ExclusivelyInheritedSharedInformation, name, value)
    __swig_getmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, ExclusivelyInheritedSharedInformation, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_ExclusivelyInheritedSharedInformation(*args)
        try: self.this.append(this)
        except: self.this = this
    def getCommonDisjointAncestors(self, *args): return _term_sim.ExclusivelyInheritedSharedInformation_getCommonDisjointAncestors(self, *args)
    def sharedInformation(self, *args): return _term_sim.ExclusivelyInheritedSharedInformation_sharedInformation(self, *args)
    def maxInformationContent(self, *args): return _term_sim.ExclusivelyInheritedSharedInformation_maxInformationContent(self, *args)
    def hasTerm(self, *args): return _term_sim.ExclusivelyInheritedSharedInformation_hasTerm(self, *args)
    def isSameOntology(self, *args): return _term_sim.ExclusivelyInheritedSharedInformation_isSameOntology(self, *args)
    __swig_destroy__ = _term_sim.delete_ExclusivelyInheritedSharedInformation
    __del__ = lambda self : None;
ExclusivelyInheritedSharedInformation_swigregister = _term_sim.ExclusivelyInheritedSharedInformation_swigregister
ExclusivelyInheritedSharedInformation_swigregister(ExclusivelyInheritedSharedInformation)

class FrontierSharedInformation(SharedInformationInterface):
    __swig_setmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, FrontierSharedInformation, name, value)
    __swig_getmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, FrontierSharedInformation, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_FrontierSharedInformation(*args)
        try: self.this.append(this)
        except: self.this = this
    def getCommonDisjointAncestors(self, *args): return _term_sim.FrontierSharedInformation_getCommonDisjointAncestors(self, *args)
    def sharedInformation(self, *args): return _term_sim.FrontierSharedInformation_sharedInformation(self, *args)
    def maxInformationContent(self, *args): return _term_sim.FrontierSharedInformation_maxInformationContent(self, *args)
    def hasTerm(self, *args): return _term_sim.FrontierSharedInformation_hasTerm(self, *args)
    def isSameOntology(self, *args): return _term_sim.FrontierSharedInformation_isSameOntology(self, *args)
    __swig_destroy__ = _term_sim.delete_FrontierSharedInformation
    __del__ = lambda self : None;
FrontierSharedInformation_swigregister = _term_sim.FrontierSharedInformation_swigregister
FrontierSharedInformation_swigregister(FrontierSharedInformation)

class MICASharedInformation(SharedInformationInterface):
    __swig_setmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, MICASharedInformation, name, value)
    __swig_getmethods__ = {}
    for _s in [SharedInformationInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, MICASharedInformation, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_MICASharedInformation(*args)
        try: self.this.append(this)
        except: self.this = this
    def sharedInformation(self, *args): return _term_sim.MICASharedInformation_sharedInformation(self, *args)
    def maxInformationContent(self, *args): return _term_sim.MICASharedInformation_maxInformationContent(self, *args)
    def hasTerm(self, *args): return _term_sim.MICASharedInformation_hasTerm(self, *args)
    def isSameOntology(self, *args): return _term_sim.MICASharedInformation_isSameOntology(self, *args)
    __swig_destroy__ = _term_sim.delete_MICASharedInformation
    __del__ = lambda self : None;
MICASharedInformation_swigregister = _term_sim.MICASharedInformation_swigregister
MICASharedInformation_swigregister(MICASharedInformation)

class TermSimilarityInterface(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TermSimilarityInterface, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TermSimilarityInterface, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    def calculateTermSimilarity(self, *args): return _term_sim.TermSimilarityInterface_calculateTermSimilarity(self, *args)
    def calculateNormalizedTermSimilarity(self, *args): return _term_sim.TermSimilarityInterface_calculateNormalizedTermSimilarity(self, *args)
    __swig_destroy__ = _term_sim.delete_TermSimilarityInterface
    __del__ = lambda self : None;
TermSimilarityInterface_swigregister = _term_sim.TermSimilarityInterface_swigregister
TermSimilarityInterface_swigregister(TermSimilarityInterface)

class JiangConrathSimilarity(TermSimilarityInterface):
    __swig_setmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, JiangConrathSimilarity, name, value)
    __swig_getmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, JiangConrathSimilarity, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_JiangConrathSimilarity(*args)
        try: self.this.append(this)
        except: self.this = this
    def calculateTermSimilarity(self, *args): return _term_sim.JiangConrathSimilarity_calculateTermSimilarity(self, *args)
    def calculateNormalizedTermSimilarity(self, *args): return _term_sim.JiangConrathSimilarity_calculateNormalizedTermSimilarity(self, *args)
    def getMICA(self, *args): return _term_sim.JiangConrathSimilarity_getMICA(self, *args)
    __swig_destroy__ = _term_sim.delete_JiangConrathSimilarity
    __del__ = lambda self : None;
JiangConrathSimilarity_swigregister = _term_sim.JiangConrathSimilarity_swigregister
JiangConrathSimilarity_swigregister(JiangConrathSimilarity)

class LinSimilarity(TermSimilarityInterface):
    __swig_setmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, LinSimilarity, name, value)
    __swig_getmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, LinSimilarity, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_LinSimilarity(*args)
        try: self.this.append(this)
        except: self.this = this
    def calculateTermSimilarity(self, *args): return _term_sim.LinSimilarity_calculateTermSimilarity(self, *args)
    def calculateNormalizedTermSimilarity(self, *args): return _term_sim.LinSimilarity_calculateNormalizedTermSimilarity(self, *args)
    def getMICA(self, *args): return _term_sim.LinSimilarity_getMICA(self, *args)
    __swig_destroy__ = _term_sim.delete_LinSimilarity
    __del__ = lambda self : None;
LinSimilarity_swigregister = _term_sim.LinSimilarity_swigregister
LinSimilarity_swigregister(LinSimilarity)

class ModularJiangConrath(TermSimilarityInterface):
    __swig_setmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, ModularJiangConrath, name, value)
    __swig_getmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, ModularJiangConrath, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_ModularJiangConrath(*args)
        try: self.this.append(this)
        except: self.this = this
    def calculateTermSimilarity(self, *args): return _term_sim.ModularJiangConrath_calculateTermSimilarity(self, *args)
    def calculateNormalizedTermSimilarity(self, *args): return _term_sim.ModularJiangConrath_calculateNormalizedTermSimilarity(self, *args)
    def setSharedInformationCalculator(self, *args): return _term_sim.ModularJiangConrath_setSharedInformationCalculator(self, *args)
    __swig_destroy__ = _term_sim.delete_ModularJiangConrath
    __del__ = lambda self : None;
ModularJiangConrath_swigregister = _term_sim.ModularJiangConrath_swigregister
ModularJiangConrath_swigregister(ModularJiangConrath)

class ModularLin(TermSimilarityInterface):
    __swig_setmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, ModularLin, name, value)
    __swig_getmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, ModularLin, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_ModularLin(*args)
        try: self.this.append(this)
        except: self.this = this
    def calculateTermSimilarity(self, *args): return _term_sim.ModularLin_calculateTermSimilarity(self, *args)
    def calculateNormalizedTermSimilarity(self, *args): return _term_sim.ModularLin_calculateNormalizedTermSimilarity(self, *args)
    def setSharedInformationCalculator(self, *args): return _term_sim.ModularLin_setSharedInformationCalculator(self, *args)
    __swig_destroy__ = _term_sim.delete_ModularLin
    __del__ = lambda self : None;
ModularLin_swigregister = _term_sim.ModularLin_swigregister
ModularLin_swigregister(ModularLin)

class ModularResnik(TermSimilarityInterface):
    __swig_setmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, ModularResnik, name, value)
    __swig_getmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, ModularResnik, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_ModularResnik(*args)
        try: self.this.append(this)
        except: self.this = this
    def calculateTermSimilarity(self, *args): return _term_sim.ModularResnik_calculateTermSimilarity(self, *args)
    def calculateNormalizedTermSimilarity(self, *args): return _term_sim.ModularResnik_calculateNormalizedTermSimilarity(self, *args)
    def setSharedInformationCalculator(self, *args): return _term_sim.ModularResnik_setSharedInformationCalculator(self, *args)
    __swig_destroy__ = _term_sim.delete_ModularResnik
    __del__ = lambda self : None;
ModularResnik_swigregister = _term_sim.ModularResnik_swigregister
ModularResnik_swigregister(ModularResnik)

class PekarStaabSimilarity(TermSimilarityInterface):
    __swig_setmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, PekarStaabSimilarity, name, value)
    __swig_getmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, PekarStaabSimilarity, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_PekarStaabSimilarity(*args)
        try: self.this.append(this)
        except: self.this = this
    def calculateTermSimilarity(self, *args): return _term_sim.PekarStaabSimilarity_calculateTermSimilarity(self, *args)
    def calculateNormalizedTermSimilarity(self, *args): return _term_sim.PekarStaabSimilarity_calculateNormalizedTermSimilarity(self, *args)
    def getLCA(self, *args): return _term_sim.PekarStaabSimilarity_getLCA(self, *args)
    __swig_destroy__ = _term_sim.delete_PekarStaabSimilarity
    __del__ = lambda self : None;
PekarStaabSimilarity_swigregister = _term_sim.PekarStaabSimilarity_swigregister
PekarStaabSimilarity_swigregister(PekarStaabSimilarity)

class PrecomputedMatrixTermSimilarity(TermSimilarityInterface):
    __swig_setmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, PrecomputedMatrixTermSimilarity, name, value)
    __swig_getmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, PrecomputedMatrixTermSimilarity, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_PrecomputedMatrixTermSimilarity(*args)
        try: self.this.append(this)
        except: self.this = this
    def calculateTermSimilarity(self, *args): return _term_sim.PrecomputedMatrixTermSimilarity_calculateTermSimilarity(self, *args)
    def calculateNormalizedTermSimilarity(self, *args): return _term_sim.PrecomputedMatrixTermSimilarity_calculateNormalizedTermSimilarity(self, *args)
    def projectTermSet(self, *args): return _term_sim.PrecomputedMatrixTermSimilarity_projectTermSet(self, *args)
    __swig_destroy__ = _term_sim.delete_PrecomputedMatrixTermSimilarity
    __del__ = lambda self : None;
PrecomputedMatrixTermSimilarity_swigregister = _term_sim.PrecomputedMatrixTermSimilarity_swigregister
PrecomputedMatrixTermSimilarity_swigregister(PrecomputedMatrixTermSimilarity)

class RelevanceSimilarity(TermSimilarityInterface):
    __swig_setmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, RelevanceSimilarity, name, value)
    __swig_getmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, RelevanceSimilarity, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_RelevanceSimilarity(*args)
        try: self.this.append(this)
        except: self.this = this
    def calculateTermSimilarity(self, *args): return _term_sim.RelevanceSimilarity_calculateTermSimilarity(self, *args)
    def calculateNormalizedTermSimilarity(self, *args): return _term_sim.RelevanceSimilarity_calculateNormalizedTermSimilarity(self, *args)
    def getMICA(self, *args): return _term_sim.RelevanceSimilarity_getMICA(self, *args)
    __swig_destroy__ = _term_sim.delete_RelevanceSimilarity
    __del__ = lambda self : None;
RelevanceSimilarity_swigregister = _term_sim.RelevanceSimilarity_swigregister
RelevanceSimilarity_swigregister(RelevanceSimilarity)

class ResnikSimilarity(TermSimilarityInterface):
    __swig_setmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, ResnikSimilarity, name, value)
    __swig_getmethods__ = {}
    for _s in [TermSimilarityInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, ResnikSimilarity, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_ResnikSimilarity(*args)
        try: self.this.append(this)
        except: self.this = this
    def calculateTermSimilarity(self, *args): return _term_sim.ResnikSimilarity_calculateTermSimilarity(self, *args)
    def calculateNormalizedTermSimilarity(self, *args): return _term_sim.ResnikSimilarity_calculateNormalizedTermSimilarity(self, *args)
    def getMICA(self, *args): return _term_sim.ResnikSimilarity_getMICA(self, *args)
    __swig_destroy__ = _term_sim.delete_ResnikSimilarity
    __del__ = lambda self : None;
ResnikSimilarity_swigregister = _term_sim.ResnikSimilarity_swigregister
ResnikSimilarity_swigregister(ResnikSimilarity)

class TermSimilarityWriter(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TermSimilarityWriter, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TermSimilarityWriter, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _term_sim.new_TermSimilarityWriter(*args)
        try: self.this.append(this)
        except: self.this = this
    def writeSimilarityMatrix(self, *args): return _term_sim.TermSimilarityWriter_writeSimilarityMatrix(self, *args)
    def writeSimilarityMatrixBP(self, *args): return _term_sim.TermSimilarityWriter_writeSimilarityMatrixBP(self, *args)
    def writeSimilarityMatrixMF(self, *args): return _term_sim.TermSimilarityWriter_writeSimilarityMatrixMF(self, *args)
    def writeSimilarityMatrixCC(self, *args): return _term_sim.TermSimilarityWriter_writeSimilarityMatrixCC(self, *args)
    __swig_destroy__ = _term_sim.delete_TermSimilarityWriter
    __del__ = lambda self : None;
TermSimilarityWriter_swigregister = _term_sim.TermSimilarityWriter_swigregister
TermSimilarityWriter_swigregister(TermSimilarityWriter)



