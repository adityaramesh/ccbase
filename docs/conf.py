import os
import sphinx_rtd_theme as theme

project = 'CCBase'
copyright = '2014, Aditya Ramesh'
version = '1.0'
release = '1.0'

exclude_patterns = []
templates_path = ['_templates']
extensions = ['sphinx.ext.todo', 'sphinx.ext.mathjax']
source_suffix = '.rst'
master_doc = 'index'

pygments_style = 'sphinx'
highlight_language = 'cpp'

todo_include_todos = True

#
# HTML output options
#

html_theme = 'sphinx_rtd_theme'
html_theme_path = [theme.get_html_theme_path()]

# Add any paths that contain custom static files (such as stylesheets) here,
# relative to this directory. They are copied after the builtin static files, so
# a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# If true, SmartyPants will be used to convert quotes and dashes to
# typographically correct entities.
html_use_smartypants = True

# If true, links to the reST sources are added to the pages.
html_show_sourcelink = True
