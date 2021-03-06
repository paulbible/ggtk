.. GGTK documentation master file, created by
   sphinx-quickstart on Sat Sep 10 11:40:14 2016.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.


GGTK: The GO Graph Tool Kit
===========================

.. _C++ documentation:
   https://paulbible.github.io/ggtk/ggtk/index.html

.. _GitHub Project:
   https://github.com/paulbible/ggtk

GGTK is a set of modular tools for working with the Gene Ontology Graph. These pages provide documentation for the Python interface for GGTK. The `C++ documentation`_ provides details about the GGTK API. The `GitHub Project`_ hosts all the code for GGTK.


Getting Started
===============

.. _Python 2.7:
   https://www.python.org/downloads/release

.. _setuptools package:
   https://pypi.python.org/pypi/setuptools

.. _Boost C++ Libraries:
   http://www.boost.org

.. _here:
      https://wiki.python.org/moin/WindowsCompilers

The major requirements for using the Python interface to GGTK are `Python 2.7`_, the `setuptools package`_, a c++ compiler, and the `Boost C++ Libraries`_ version 1.54 or higher. Windows user may need to download a C++ compiler that is compatible with their Python release. See `here`_ for more information.

GGTK requires that you set the environment variable `BOOST` to the location of the Boost directory.::

    export BOOST=/path/to/boost_1_54_0

Once you have downloaded the GGTK project folder. Enter the python diretory and enter the following commands::

    cd python
    python setup.py build
    python setup.py install


After Python has built and installed the package you may optionally run the tests. You may need to unzip the examples files::

    cd tests
    python test_all.py


These tests will take about 5-10 minutes to complete.


Example Code
============

A few example programs are provided to illustrate a few typical use cases of GGTK. The source code of the tests, under GGTK_HOME/python/tests, provides more comprehensive usage examples beyond those described there.

.. toctree::
   :maxdepth: 2

   code_examples



GGTK Python API
===============

These pages document the available functions and signatures of the GGTK Python modules.

.. toctree::
   :maxdepth: 2

   ggtk_api



License
=======

.. _Boost Software License - Version 1.0:
   http://www.boost.org/LICENSE_1_0.txt

.. _available here:
   http://www.boost.org/users/license.html

GGTK is released under the `Boost Software License - Version 1.0`_. More details are `available here`_.



