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
            fp, pathname, description = imp.find_module('_anno_parsers', [dirname(__file__)])
        except ImportError:
            import _anno_parsers
            return _anno_parsers
        if fp is not None:
            try:
                _mod = imp.load_module('_anno_parsers', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _anno_parsers = swig_import_helper()
    del swig_import_helper
else:
    import _anno_parsers
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
    __swig_destroy__ = _anno_parsers.delete_SwigPyIterator
    __del__ = lambda self : None;
    def value(self): return _anno_parsers.SwigPyIterator_value(self)
    def incr(self, n = 1): return _anno_parsers.SwigPyIterator_incr(self, n)
    def decr(self, n = 1): return _anno_parsers.SwigPyIterator_decr(self, n)
    def distance(self, *args): return _anno_parsers.SwigPyIterator_distance(self, *args)
    def equal(self, *args): return _anno_parsers.SwigPyIterator_equal(self, *args)
    def copy(self): return _anno_parsers.SwigPyIterator_copy(self)
    def next(self): return _anno_parsers.SwigPyIterator_next(self)
    def __next__(self): return _anno_parsers.SwigPyIterator___next__(self)
    def previous(self): return _anno_parsers.SwigPyIterator_previous(self)
    def advance(self, *args): return _anno_parsers.SwigPyIterator_advance(self, *args)
    def __eq__(self, *args): return _anno_parsers.SwigPyIterator___eq__(self, *args)
    def __ne__(self, *args): return _anno_parsers.SwigPyIterator___ne__(self, *args)
    def __iadd__(self, *args): return _anno_parsers.SwigPyIterator___iadd__(self, *args)
    def __isub__(self, *args): return _anno_parsers.SwigPyIterator___isub__(self, *args)
    def __add__(self, *args): return _anno_parsers.SwigPyIterator___add__(self, *args)
    def __sub__(self, *args): return _anno_parsers.SwigPyIterator___sub__(self, *args)
    def __iter__(self): return self
SwigPyIterator_swigregister = _anno_parsers.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)

class SizeVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SizeVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SizeVector, name)
    __repr__ = _swig_repr
    def iterator(self): return _anno_parsers.SizeVector_iterator(self)
    def __iter__(self): return self.iterator()
    def __nonzero__(self): return _anno_parsers.SizeVector___nonzero__(self)
    def __bool__(self): return _anno_parsers.SizeVector___bool__(self)
    def __len__(self): return _anno_parsers.SizeVector___len__(self)
    def pop(self): return _anno_parsers.SizeVector_pop(self)
    def __getslice__(self, *args): return _anno_parsers.SizeVector___getslice__(self, *args)
    def __setslice__(self, *args): return _anno_parsers.SizeVector___setslice__(self, *args)
    def __delslice__(self, *args): return _anno_parsers.SizeVector___delslice__(self, *args)
    def __delitem__(self, *args): return _anno_parsers.SizeVector___delitem__(self, *args)
    def __getitem__(self, *args): return _anno_parsers.SizeVector___getitem__(self, *args)
    def __setitem__(self, *args): return _anno_parsers.SizeVector___setitem__(self, *args)
    def append(self, *args): return _anno_parsers.SizeVector_append(self, *args)
    def empty(self): return _anno_parsers.SizeVector_empty(self)
    def size(self): return _anno_parsers.SizeVector_size(self)
    def clear(self): return _anno_parsers.SizeVector_clear(self)
    def swap(self, *args): return _anno_parsers.SizeVector_swap(self, *args)
    def get_allocator(self): return _anno_parsers.SizeVector_get_allocator(self)
    def begin(self): return _anno_parsers.SizeVector_begin(self)
    def end(self): return _anno_parsers.SizeVector_end(self)
    def rbegin(self): return _anno_parsers.SizeVector_rbegin(self)
    def rend(self): return _anno_parsers.SizeVector_rend(self)
    def pop_back(self): return _anno_parsers.SizeVector_pop_back(self)
    def erase(self, *args): return _anno_parsers.SizeVector_erase(self, *args)
    def __init__(self, *args): 
        this = _anno_parsers.new_SizeVector(*args)
        try: self.this.append(this)
        except: self.this = this
    def push_back(self, *args): return _anno_parsers.SizeVector_push_back(self, *args)
    def front(self): return _anno_parsers.SizeVector_front(self)
    def back(self): return _anno_parsers.SizeVector_back(self)
    def assign(self, *args): return _anno_parsers.SizeVector_assign(self, *args)
    def resize(self, *args): return _anno_parsers.SizeVector_resize(self, *args)
    def insert(self, *args): return _anno_parsers.SizeVector_insert(self, *args)
    def reserve(self, *args): return _anno_parsers.SizeVector_reserve(self, *args)
    def capacity(self): return _anno_parsers.SizeVector_capacity(self)
    __swig_destroy__ = _anno_parsers.delete_SizeVector
    __del__ = lambda self : None;
SizeVector_swigregister = _anno_parsers.SizeVector_swigregister
SizeVector_swigregister(SizeVector)

class StringArray(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, StringArray, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, StringArray, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _anno_parsers.new_StringArray(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _anno_parsers.delete_StringArray
    __del__ = lambda self : None;
    def __getitem__(self, *args): return _anno_parsers.StringArray___getitem__(self, *args)
    def __setitem__(self, *args): return _anno_parsers.StringArray___setitem__(self, *args)
    def cast(self): return _anno_parsers.StringArray_cast(self)
    __swig_getmethods__["frompointer"] = lambda x: _anno_parsers.StringArray_frompointer
    if _newclass:frompointer = staticmethod(_anno_parsers.StringArray_frompointer)
StringArray_swigregister = _anno_parsers.StringArray_swigregister
StringArray_swigregister(StringArray)

def StringArray_frompointer(*args):
  return _anno_parsers.StringArray_frompointer(*args)
StringArray_frompointer = _anno_parsers.StringArray_frompointer

class StringVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, StringVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, StringVector, name)
    __repr__ = _swig_repr
    def iterator(self): return _anno_parsers.StringVector_iterator(self)
    def __iter__(self): return self.iterator()
    def __nonzero__(self): return _anno_parsers.StringVector___nonzero__(self)
    def __bool__(self): return _anno_parsers.StringVector___bool__(self)
    def __len__(self): return _anno_parsers.StringVector___len__(self)
    def pop(self): return _anno_parsers.StringVector_pop(self)
    def __getslice__(self, *args): return _anno_parsers.StringVector___getslice__(self, *args)
    def __setslice__(self, *args): return _anno_parsers.StringVector___setslice__(self, *args)
    def __delslice__(self, *args): return _anno_parsers.StringVector___delslice__(self, *args)
    def __delitem__(self, *args): return _anno_parsers.StringVector___delitem__(self, *args)
    def __getitem__(self, *args): return _anno_parsers.StringVector___getitem__(self, *args)
    def __setitem__(self, *args): return _anno_parsers.StringVector___setitem__(self, *args)
    def append(self, *args): return _anno_parsers.StringVector_append(self, *args)
    def empty(self): return _anno_parsers.StringVector_empty(self)
    def size(self): return _anno_parsers.StringVector_size(self)
    def clear(self): return _anno_parsers.StringVector_clear(self)
    def swap(self, *args): return _anno_parsers.StringVector_swap(self, *args)
    def get_allocator(self): return _anno_parsers.StringVector_get_allocator(self)
    def begin(self): return _anno_parsers.StringVector_begin(self)
    def end(self): return _anno_parsers.StringVector_end(self)
    def rbegin(self): return _anno_parsers.StringVector_rbegin(self)
    def rend(self): return _anno_parsers.StringVector_rend(self)
    def pop_back(self): return _anno_parsers.StringVector_pop_back(self)
    def erase(self, *args): return _anno_parsers.StringVector_erase(self, *args)
    def __init__(self, *args): 
        this = _anno_parsers.new_StringVector(*args)
        try: self.this.append(this)
        except: self.this = this
    def push_back(self, *args): return _anno_parsers.StringVector_push_back(self, *args)
    def front(self): return _anno_parsers.StringVector_front(self)
    def back(self): return _anno_parsers.StringVector_back(self)
    def assign(self, *args): return _anno_parsers.StringVector_assign(self, *args)
    def resize(self, *args): return _anno_parsers.StringVector_resize(self, *args)
    def insert(self, *args): return _anno_parsers.StringVector_insert(self, *args)
    def reserve(self, *args): return _anno_parsers.StringVector_reserve(self, *args)
    def capacity(self): return _anno_parsers.StringVector_capacity(self)
    __swig_destroy__ = _anno_parsers.delete_StringVector
    __del__ = lambda self : None;
StringVector_swigregister = _anno_parsers.StringVector_swigregister
StringVector_swigregister(StringVector)

class DoubleVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DoubleVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DoubleVector, name)
    __repr__ = _swig_repr
    def iterator(self): return _anno_parsers.DoubleVector_iterator(self)
    def __iter__(self): return self.iterator()
    def __nonzero__(self): return _anno_parsers.DoubleVector___nonzero__(self)
    def __bool__(self): return _anno_parsers.DoubleVector___bool__(self)
    def __len__(self): return _anno_parsers.DoubleVector___len__(self)
    def pop(self): return _anno_parsers.DoubleVector_pop(self)
    def __getslice__(self, *args): return _anno_parsers.DoubleVector___getslice__(self, *args)
    def __setslice__(self, *args): return _anno_parsers.DoubleVector___setslice__(self, *args)
    def __delslice__(self, *args): return _anno_parsers.DoubleVector___delslice__(self, *args)
    def __delitem__(self, *args): return _anno_parsers.DoubleVector___delitem__(self, *args)
    def __getitem__(self, *args): return _anno_parsers.DoubleVector___getitem__(self, *args)
    def __setitem__(self, *args): return _anno_parsers.DoubleVector___setitem__(self, *args)
    def append(self, *args): return _anno_parsers.DoubleVector_append(self, *args)
    def empty(self): return _anno_parsers.DoubleVector_empty(self)
    def size(self): return _anno_parsers.DoubleVector_size(self)
    def clear(self): return _anno_parsers.DoubleVector_clear(self)
    def swap(self, *args): return _anno_parsers.DoubleVector_swap(self, *args)
    def get_allocator(self): return _anno_parsers.DoubleVector_get_allocator(self)
    def begin(self): return _anno_parsers.DoubleVector_begin(self)
    def end(self): return _anno_parsers.DoubleVector_end(self)
    def rbegin(self): return _anno_parsers.DoubleVector_rbegin(self)
    def rend(self): return _anno_parsers.DoubleVector_rend(self)
    def pop_back(self): return _anno_parsers.DoubleVector_pop_back(self)
    def erase(self, *args): return _anno_parsers.DoubleVector_erase(self, *args)
    def __init__(self, *args): 
        this = _anno_parsers.new_DoubleVector(*args)
        try: self.this.append(this)
        except: self.this = this
    def push_back(self, *args): return _anno_parsers.DoubleVector_push_back(self, *args)
    def front(self): return _anno_parsers.DoubleVector_front(self)
    def back(self): return _anno_parsers.DoubleVector_back(self)
    def assign(self, *args): return _anno_parsers.DoubleVector_assign(self, *args)
    def resize(self, *args): return _anno_parsers.DoubleVector_resize(self, *args)
    def insert(self, *args): return _anno_parsers.DoubleVector_insert(self, *args)
    def reserve(self, *args): return _anno_parsers.DoubleVector_reserve(self, *args)
    def capacity(self): return _anno_parsers.DoubleVector_capacity(self)
    __swig_destroy__ = _anno_parsers.delete_DoubleVector
    __del__ = lambda self : None;
DoubleVector_swigregister = _anno_parsers.DoubleVector_swigregister
DoubleVector_swigregister(DoubleVector)

class BoostSet(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, BoostSet, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, BoostSet, name)
    __repr__ = _swig_repr
    def __init__(self): 
        this = _anno_parsers.new_BoostSet()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _anno_parsers.delete_BoostSet
    __del__ = lambda self : None;
BoostSet_swigregister = _anno_parsers.BoostSet_swigregister
BoostSet_swigregister(BoostSet)

NUM_ONTOLOGIES = _anno_parsers.NUM_ONTOLOGIES
NUM_EVIDENCES = _anno_parsers.NUM_EVIDENCES
NUM_RELATIONSHIPS = _anno_parsers.NUM_RELATIONSHIPS

def getRootTermBP():
  return _anno_parsers.getRootTermBP()
getRootTermBP = _anno_parsers.getRootTermBP

def getRootTermMF():
  return _anno_parsers.getRootTermMF()
getRootTermMF = _anno_parsers.getRootTermMF

def getRootTermCC():
  return _anno_parsers.getRootTermCC()
getRootTermCC = _anno_parsers.getRootTermCC
BP = _anno_parsers.BP
MF = _anno_parsers.MF
CC = _anno_parsers.CC
ONTO_ERROR = _anno_parsers.ONTO_ERROR

def ontologyStringToCode(*args):
  return _anno_parsers.ontologyStringToCode(*args)
ontologyStringToCode = _anno_parsers.ontologyStringToCode

def ontologyToString(*args):
  return _anno_parsers.ontologyToString(*args)
ontologyToString = _anno_parsers.ontologyToString
EXP = _anno_parsers.EXP
IDA = _anno_parsers.IDA
IPI = _anno_parsers.IPI
IMP = _anno_parsers.IMP
IGI = _anno_parsers.IGI
IEP = _anno_parsers.IEP
ISS = _anno_parsers.ISS
ISO = _anno_parsers.ISO
ISA = _anno_parsers.ISA
ISM = _anno_parsers.ISM
IGC = _anno_parsers.IGC
IBA = _anno_parsers.IBA
IBD = _anno_parsers.IBD
IKR = _anno_parsers.IKR
IRD = _anno_parsers.IRD
RCA = _anno_parsers.RCA
TAS = _anno_parsers.TAS
NAS = _anno_parsers.NAS
IC = _anno_parsers.IC
ND = _anno_parsers.ND
IEA = _anno_parsers.IEA
NR = _anno_parsers.NR
ECODE_ERROR = _anno_parsers.ECODE_ERROR

def evidenceStringToCode(*args):
  return _anno_parsers.evidenceStringToCode(*args)
evidenceStringToCode = _anno_parsers.evidenceStringToCode

def evidenceToString(*args):
  return _anno_parsers.evidenceToString(*args)
evidenceToString = _anno_parsers.evidenceToString
IS_A = _anno_parsers.IS_A
PART_OF = _anno_parsers.PART_OF
REGULATES = _anno_parsers.REGULATES
POSITIVELY_REGULATES = _anno_parsers.POSITIVELY_REGULATES
NEGATIVELY_REGULATES = _anno_parsers.NEGATIVELY_REGULATES
REL_ERROR = _anno_parsers.REL_ERROR

def relationshipStringToCode(*args):
  return _anno_parsers.relationshipStringToCode(*args)
relationshipStringToCode = _anno_parsers.relationshipStringToCode

def relationshipToString(*args):
  return _anno_parsers.relationshipToString(*args)
relationshipToString = _anno_parsers.relationshipToString
class EvidencePolicyInterface(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, EvidencePolicyInterface, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, EvidencePolicyInterface, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    def isAllowed(self, *args): return _anno_parsers.EvidencePolicyInterface_isAllowed(self, *args)
    __swig_destroy__ = _anno_parsers.delete_EvidencePolicyInterface
    __del__ = lambda self : None;
EvidencePolicyInterface_swigregister = _anno_parsers.EvidencePolicyInterface_swigregister
EvidencePolicyInterface_swigregister(EvidencePolicyInterface)
cvar = _anno_parsers.cvar

class AllowedSetEvidencePolicy(EvidencePolicyInterface):
    __swig_setmethods__ = {}
    for _s in [EvidencePolicyInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, AllowedSetEvidencePolicy, name, value)
    __swig_getmethods__ = {}
    for _s in [EvidencePolicyInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, AllowedSetEvidencePolicy, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _anno_parsers.new_AllowedSetEvidencePolicy(*args)
        try: self.this.append(this)
        except: self.this = this
    def isAllowed(self, *args): return _anno_parsers.AllowedSetEvidencePolicy_isAllowed(self, *args)
    def addEvidence(self, *args): return _anno_parsers.AllowedSetEvidencePolicy_addEvidence(self, *args)
    def isEmpty(self): return _anno_parsers.AllowedSetEvidencePolicy_isEmpty(self)
    __swig_destroy__ = _anno_parsers.delete_AllowedSetEvidencePolicy
    __del__ = lambda self : None;
AllowedSetEvidencePolicy_swigregister = _anno_parsers.AllowedSetEvidencePolicy_swigregister
AllowedSetEvidencePolicy_swigregister(AllowedSetEvidencePolicy)

class DisallowedSetEvidencePolicy(EvidencePolicyInterface):
    __swig_setmethods__ = {}
    for _s in [EvidencePolicyInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, DisallowedSetEvidencePolicy, name, value)
    __swig_getmethods__ = {}
    for _s in [EvidencePolicyInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, DisallowedSetEvidencePolicy, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _anno_parsers.new_DisallowedSetEvidencePolicy(*args)
        try: self.this.append(this)
        except: self.this = this
    def isAllowed(self, *args): return _anno_parsers.DisallowedSetEvidencePolicy_isAllowed(self, *args)
    def addEvidence(self, *args): return _anno_parsers.DisallowedSetEvidencePolicy_addEvidence(self, *args)
    def isEmpty(self): return _anno_parsers.DisallowedSetEvidencePolicy_isEmpty(self)
    __swig_destroy__ = _anno_parsers.delete_DisallowedSetEvidencePolicy
    __del__ = lambda self : None;
DisallowedSetEvidencePolicy_swigregister = _anno_parsers.DisallowedSetEvidencePolicy_swigregister
DisallowedSetEvidencePolicy_swigregister(DisallowedSetEvidencePolicy)

class ExperimentalEvidencePolicy(AllowedSetEvidencePolicy):
    __swig_setmethods__ = {}
    for _s in [AllowedSetEvidencePolicy]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, ExperimentalEvidencePolicy, name, value)
    __swig_getmethods__ = {}
    for _s in [AllowedSetEvidencePolicy]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, ExperimentalEvidencePolicy, name)
    __repr__ = _swig_repr
    def __init__(self): 
        this = _anno_parsers.new_ExperimentalEvidencePolicy()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _anno_parsers.delete_ExperimentalEvidencePolicy
    __del__ = lambda self : None;
ExperimentalEvidencePolicy_swigregister = _anno_parsers.ExperimentalEvidencePolicy_swigregister
ExperimentalEvidencePolicy_swigregister(ExperimentalEvidencePolicy)

class AnnotationParserInterface(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, AnnotationParserInterface, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, AnnotationParserInterface, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    def parseAnnotationFile(self, *args): return _anno_parsers.AnnotationParserInterface_parseAnnotationFile(self, *args)
    def isFileGood(self, *args): return _anno_parsers.AnnotationParserInterface_isFileGood(self, *args)
    def clone(self): return _anno_parsers.AnnotationParserInterface_clone(self)
    __swig_destroy__ = _anno_parsers.delete_AnnotationParserInterface
    __del__ = lambda self : None;
AnnotationParserInterface_swigregister = _anno_parsers.AnnotationParserInterface_swigregister
AnnotationParserInterface_swigregister(AnnotationParserInterface)

class EntrezGene2GoAnnotationParser(AnnotationParserInterface):
    __swig_setmethods__ = {}
    for _s in [AnnotationParserInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, EntrezGene2GoAnnotationParser, name, value)
    __swig_getmethods__ = {}
    for _s in [AnnotationParserInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, EntrezGene2GoAnnotationParser, name)
    __repr__ = _swig_repr
    def parseAnnotationFile(self, *args): return _anno_parsers.EntrezGene2GoAnnotationParser_parseAnnotationFile(self, *args)
    def isFileGood(self, *args): return _anno_parsers.EntrezGene2GoAnnotationParser_isFileGood(self, *args)
    def clone(self): return _anno_parsers.EntrezGene2GoAnnotationParser_clone(self)
    def __init__(self, *args): 
        this = _anno_parsers.new_EntrezGene2GoAnnotationParser(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _anno_parsers.delete_EntrezGene2GoAnnotationParser
    __del__ = lambda self : None;
EntrezGene2GoAnnotationParser_swigregister = _anno_parsers.EntrezGene2GoAnnotationParser_swigregister
EntrezGene2GoAnnotationParser_swigregister(EntrezGene2GoAnnotationParser)

class GoaAnnotationParser(AnnotationParserInterface):
    __swig_setmethods__ = {}
    for _s in [AnnotationParserInterface]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, GoaAnnotationParser, name, value)
    __swig_getmethods__ = {}
    for _s in [AnnotationParserInterface]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, GoaAnnotationParser, name)
    __repr__ = _swig_repr
    def parseAnnotationFile(self, *args): return _anno_parsers.GoaAnnotationParser_parseAnnotationFile(self, *args)
    def isFileGood(self, *args): return _anno_parsers.GoaAnnotationParser_isFileGood(self, *args)
    def __init__(self, *args): 
        this = _anno_parsers.new_GoaAnnotationParser(*args)
        try: self.this.append(this)
        except: self.this = this
    def clone(self): return _anno_parsers.GoaAnnotationParser_clone(self)
    __swig_destroy__ = _anno_parsers.delete_GoaAnnotationParser
    __del__ = lambda self : None;
GoaAnnotationParser_swigregister = _anno_parsers.GoaAnnotationParser_swigregister
GoaAnnotationParser_swigregister(GoaAnnotationParser)

class GafAnnotationParser(GoaAnnotationParser):
    __swig_setmethods__ = {}
    for _s in [GoaAnnotationParser]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, GafAnnotationParser, name, value)
    __swig_getmethods__ = {}
    for _s in [GoaAnnotationParser]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, GafAnnotationParser, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _anno_parsers.new_GafAnnotationParser(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _anno_parsers.delete_GafAnnotationParser
    __del__ = lambda self : None;
GafAnnotationParser_swigregister = _anno_parsers.GafAnnotationParser_swigregister
GafAnnotationParser_swigregister(GafAnnotationParser)

class MgiAnnotationParser(GoaAnnotationParser):
    __swig_setmethods__ = {}
    for _s in [GoaAnnotationParser]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, MgiAnnotationParser, name, value)
    __swig_getmethods__ = {}
    for _s in [GoaAnnotationParser]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, MgiAnnotationParser, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _anno_parsers.new_MgiAnnotationParser(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _anno_parsers.delete_MgiAnnotationParser
    __del__ = lambda self : None;
MgiAnnotationParser_swigregister = _anno_parsers.MgiAnnotationParser_swigregister
MgiAnnotationParser_swigregister(MgiAnnotationParser)


