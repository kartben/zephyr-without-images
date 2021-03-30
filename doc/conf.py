# -*- coding: utf-8 -*-
#
# Zephyr documentation build configuration file, created by
# sphinx-quickstart on Fri May  8 11:43:01 2015.
#
# This file is execfile()d with the current directory set to its
# containing dir.
#
# Note that not all possible configuration values are present in this
# autogenerated file.
#
# All configuration values have a default; values that are commented out
# serve to show the default.

import sys
import os

if "ZEPHYR_BASE" not in os.environ:
    sys.exit("$ZEPHYR_BASE environment variable undefined.")
ZEPHYR_BASE = os.path.abspath(os.environ["ZEPHYR_BASE"])

if "ZEPHYR_BUILD" not in os.environ:
    sys.exit("$ZEPHYR_BUILD environment variable undefined.")
ZEPHYR_BUILD = os.path.abspath(os.environ["ZEPHYR_BUILD"])

# Add the 'extensions' directory to sys.path, to enable finding Sphinx
# extensions within.
sys.path.insert(0, os.path.join(ZEPHYR_BASE, 'doc', '_extensions'))

# Add the '_scripts' directory to sys.path, to enable finding utility
# modules.
sys.path.insert(0, os.path.join(ZEPHYR_BASE, 'doc', '_scripts'))

# Add the directory which contains the runners package as well,
# for autodoc directives on runners.xyz.
sys.path.insert(0, os.path.join(ZEPHYR_BASE, 'scripts', 'west_commands'))

import redirects

try:
    import west as west_found
except ImportError:
    west_found = False

# -- General configuration ------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'breathe', 'sphinx.ext.todo',
    'sphinx.ext.extlinks',
    'sphinx.ext.autodoc',
    'zephyr.application',
    'zephyr.html_redirects',
    'only.eager_only',
    'zephyr.dtcompatible-role',
    'zephyr.link-roles',
    'sphinx_tabs.tabs'
]

# Only use SVG converter when it is really needed, e.g. LaTeX.
if tags.has("svgconvert"):  # pylint: disable=undefined-variable
    extensions.append('sphinxcontrib.rsvgconverter')

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# General information about the project.
project = u'Zephyr Project'
copyright = u'2015-2021 Zephyr Project members and individual contributors'
author = u'The Zephyr Project'

# The following code tries to extract the information by reading the Makefile,
# when Sphinx is run directly (e.g. by Read the Docs).
try:
    version_major = None
    version_minor = None
    patchlevel = None
    extraversion = None
    for line in open(os.path.join(ZEPHYR_BASE, 'VERSION')):
        key, val = [x.strip() for x in line.split('=', 2)]
        if key == 'VERSION_MAJOR':
            version_major = val
        if key == 'VERSION_MINOR':
            version_minor = val
        elif key == 'PATCHLEVEL':
            patchlevel = val
        elif key == 'EXTRAVERSION':
            extraversion = val
        if version_major and version_minor and patchlevel and extraversion:
            break
except Exception:
    pass
finally:
    if version_major and version_minor and patchlevel and extraversion is not None:
        version = release = version_major + '.' + version_minor + '.' + patchlevel
        if extraversion != '':
            version = release = version + '-' + extraversion
    else:
        sys.stderr.write('Warning: Could not extract kernel version\n')
        version = release = "unknown version"

# The language for content autogenerated by Sphinx. Refer to documentation
# for a list of supported languages.
#
# This is also used if you do content translation via gettext catalogs.
# Usually you set "language" from the command line for these cases.
language = None

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
exclude_patterns = ['_build']
if not west_found:
    exclude_patterns.append('**/*west-apis*')
else:
    exclude_patterns.append('**/*west-not-found*')

# The reST default role (used for this markup: `text`) to use for all
# documents.

# This change will allow us to use bare back-tick notation to let
# Sphinx hunt for a reference, starting with normal "document"
# references such as :ref:, but also including :c: and :cpp: domains
# (potentially) helping with API (doxygen) references simply by using
# `name`

default_role = 'any'

# The name of the Pygments (syntax highlighting) style to use.
pygments_style = 'sphinx'

# Additional lexer for Pygments (syntax highlighting)
from lexer.DtsLexer import DtsLexer
from sphinx.highlighting import lexers
lexers['DTS'] = DtsLexer()

# If true, `todo` and `todoList` produce output, else they produce nothing.
todo_include_todos = False

rst_epilog = """
.. include:: /substitutions.txt
"""

# -- Options for HTML output ----------------------------------------------

import sphinx_rtd_theme
html_theme = "sphinx_rtd_theme"
html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]
html_theme_options = {
    'prev_next_buttons_location': None
}

if tags.has('release'):  # pylint: disable=undefined-variable
    is_release = True
    docs_title = 'Docs / %s' %(version)
else:
    is_release = False
    docs_title = 'Docs / Latest'

# The name for this set of Sphinx documents.  If None, it defaults to
# "<project> v<release> documentation".
html_title = "Zephyr Project Documentation"

# The name of an image file (relative to this directory) to place at the top
# of the sidebar.
html_logo = 'images/Zephyr-Kite-logo.png'

# The name of an image file (within the static path) to use as favicon of the
# docs.  This file should be a Windows icon file (.ico) being 16x16 or 32x32
# pixels large.
html_favicon = 'images/zp_favicon.png'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['{}/doc/_static'.format(ZEPHYR_BASE)]

# If not '', a 'Last updated on:' timestamp is inserted at every page bottom,
# using the given strftime format.
html_last_updated_fmt = '%b %d, %Y'

# If false, no module index is generated.
html_domain_indices = False

# If true, the index is split into individual pages for each letter.
html_split_index = True

# If true, links to the reST sources are added to the pages.
html_show_sourcelink = False

# If true, "Created using Sphinx" is shown in the HTML footer. Default is True.
html_show_sphinx = False

# The name of a javascript file (relative to the configuration directory) that
# implements a search results scorer. If empty, the default will be used.
html_search_scorer = '_static/js/scorer.js'

html_redirect_pages = redirects.REDIRECTS

# -- Options for LaTeX output ---------------------------------------------

latex_elements = {
    # Additional stuff for the LaTeX preamble.
    'preamble': r'\setcounter{tocdepth}{2}',
}

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
latex_documents = [
  ('index', 'zephyr.tex', u'Zephyr Project Documentation',
   u'many', 'manual'),
]

breathe_projects = {
    "Zephyr": "{}/doxygen/xml".format(ZEPHYR_BUILD),
    "doc-examples": "{}/doxygen/xml".format(ZEPHYR_BUILD)
}
breathe_default_project = "Zephyr"

breathe_domain_by_extension = {
    "h": "c",
    "c": "c",
}
breathe_separate_member_pages = True
breathe_show_enumvalue_initializer = True

# Qualifiers to a function are causing Sphihx/Breathe to warn about
# Error when parsing function declaration and more.  This is a list
# of strings that the parser additionally should accept as
# attributes.
cpp_id_attributes = [
    '__syscall', '__deprecated', '__may_alias',
    '__used', '__unused', '__weak',
    '__DEPRECATED_MACRO', 'FUNC_NORETURN',
    '__subsystem',
]
c_id_attributes = cpp_id_attributes

# docs_title is used in the breadcrumb title in the zephyr docs theme
html_context = {
    'show_license': True,
    'docs_title': docs_title,
    'is_release': is_release,
    'theme_logo_only': False,
    'current_version': version,
    'versions': (("latest", "/"),
                 ("2.5.0", "/2.5.0/"),
                 ("2.4.0", "/2.4.0/"),
                 ("2.3.0", "/2.3.0/"),
                 ("2.2.0", "/2.2.0/"),
                 ("1.14.1", "/1.14.1/"),
                )
}


extlinks = {'jira': ('https://jira.zephyrproject.org/browse/%s', ''),
            'github': ('https://github.com/zephyrproject-rtos/zephyr/issues/%s', '')
           }

# some configuration for linkcheck builder
#   noticed that we're getting false-positive link errors on JIRA, I suspect
#   because it's taking too long for the server to respond so bump up the
#   timeout (default=5) and turn off anchor checks (so only a HEAD request is
#   done - much faster) Leave the ignore commented in case we want to remove
#   jira link checks later...

linkcheck_timeout = 30
linkcheck_workers = 10
# linkcheck_ignore = [r'https://jira\.zephyrproject\.org/']
linkcheck_anchors = False

def setup(app):
    app.add_css_file("css/zephyr-custom.css")

    app.add_js_file("https://www.googletagmanager.com/gtag/js?id=UA-831873-47")
    app.add_js_file("js/ga-tracker.js")
    app.add_js_file("js/zephyr-custom.js")
