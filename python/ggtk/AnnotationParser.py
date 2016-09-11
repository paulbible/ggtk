#==============================================================================
#  Copyright (c) 2016 Paul W. Bible
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================
"""
The AnnotationParser.py module provides a means for parsing different type of Gene Ontolog Annotation files.
"""
import anno_parsers
import _AnnotationData
from exceptions import IOError, ValueError

def parse(fname, format="gaf", evidence_codes=None):
    """
    Parse a Gene Ontology Annotation file.

    Options for Format are {'gaf', 'mgi', 'entrez'}.

    If evidence_codes is "exp", Only experimental evidence
    codes will be used. If evidence_codes is a list, 
    the parser will restrict annotaitons to only those given in the list.
    """
    if evidence_codes:
        if evidence_codes == 'exp':
           ecode_policy = anno_parsers.ExperimentalEvidencePolicy()
        else:
            ecode_policy = anno_parsers.AllowedSetEvidencePolicy()
            for e_code in evidence_codes:
                ecode_policy.addEvidence(e_code)
            if ecode_policy.isEmpty():
                raise ValueError('GGTK Invalid Evidence Codes: No valid evidence codes in the set.')

        if format == 'gaf' or format == 'goa':
            p = anno_parsers.GafAnnotationParser(ecode_policy)
        elif format == 'mgi':
            p = anno_parsers.MgiAnnotationParser(ecode_policy)
        elif format == 'entrez':
            p = anno_parsers.EntrezGene2GoAnnotationParser(ecode_policy)
        else:
            raise ValueError('GGTK Parser Not Defined: No parser of type %s is defined.' % format)
    
        if not p.isFileGood(fname):
            raise IOError('GGTK File Error: File not found or incorrectly formatted.')
        anno_proxy = p.parseAnnotationFile(fname)
        return _AnnotationData.AnnotationData(anno_proxy)

    else:
        if format == 'gaf' or format == 'goa':
            p = anno_parsers.GafAnnotationParser()
            if not p.isFileGood(fname):
                raise IOError('GGTK File Error: File not found or incorrectly formatted.')
            anno_proxy = p.parseAnnotationFile(fname)
            return _AnnotationData.AnnotationData(anno_proxy)

        elif format == 'mgi':
            p = anno_parsers.MgiAnnotationParser()
            if not p.isFileGood(fname):
                raise IOError('GGTK File Error: File not found or incorrectly formatted.')
            anno_proxy = p.parseAnnotationFile(fname)
            return _AnnotationData.AnnotationData(anno_proxy)

        elif format == 'entrez':
            p = anno_parsers.EntrezGene2GoAnnotationParser()
            if not p.isFileGood(fname):
                raise IOError('GGTK File Error: File not found or incorrectly formatted.')
            anno_proxy = p.parseAnnotationFile(fname)
            return _AnnotationData.AnnotationData(anno_proxy)
        else:
            raise ValueError('GGTK Parser Not Defined: No parser of type %s is defined.' % format)


