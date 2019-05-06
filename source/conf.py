# http://www.sphinx-doc.org/en/master/config
# -- Project information -----------------------------------------------------

project = 'C 与 C++'
copyright = '2019, Zombie110year'
author = 'Zombie110year'

version = "0.1"
# The full version, including alpha/beta/rc tags
release = '0.1.0rc'


# -- General configuration ---------------------------------------------------

# http://www.sphinx-doc.org/en/master/usage/extensions/
extensions = [
    'sphinx.ext.graphviz', # graphviz
    'sphinx.ext.mathjax',  # 渲染数学公式
    'sphinx.ext.todo',     # to do 指令
    'sphinx.ext.autosectionlabel', # 为标题自动生成标签, 可通过 ref 角色引用
]

templates_path = ['_templates']
language = 'zh_CN'
exclude_patterns = []
# 为拥有 caption 属性的图片 表格 代码块自动编号.
numfig = True
numfig_format = {
    'figure': "图 %s",
    'table': "表 %s",
    'code-block': "代码清单 %s",
    'section': "章节 %s",
}
numfig_secnum_depth = 0 # 全体从 1 开始编号
highlight_language = 'cpp' # 默认采用 Pygment 的 c++ 高亮模式
# 'default', 'emacs', 'friendly', 'colorful', 'autumn', 'murphy', 'manni', 'monokai', 'perldoc', 'pastie', 'borland', 'trac', 'native', 'fruity', 'bw', 'vim', 'vs', 'tango', 'rrt', 'xcode', 'igor', 'paraiso-light', 'paraiso-dark', 'lovelace', 'algol', 'algol_nu', 'arduino', 'rainbow_dash', 'abap'
pygments_style = 'friendly'

# -- Extensions' configuration -----------------------------------------------
# 引用时需要加上所在文件名前缀, 例如 :ref:`index:C 与 C++` 将会引用到 index.rst 中的 C 与 C++ 标题.
autosectionlabel_prefix_document = True
# 为前 3 级标题生成标签
autosectionlabel_maxdepth = 3
# 让 graphviz 图像输出为 svg
graphviz_output_format = 'svg'
# 不在输出中显示 todo 指令
todo_include_todos = False

# -- Options for Math rendering ----------------------------------------------
math_number_all = True # 为所有块级公式编号

# -- Options for HTML output -------------------------------------------------
html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
html_logo = "_images/logo.cpp.iso.webp"
html_favicon = "_images/logo.cpp.iso.ico"
html_sourcelink_suffix = ".rst"
html_experimental_html5_writer = True

# -- Options for EPUB output -------------------------------------------------
epub_basename = "c-and-cpp.v{}".format(release) # 生成的文件名
epub_title = "C 与 C++"
epub_description = "从 C 到 C++ 的语法, 设计模式, 以及 *nix 操作系统上的编程"
epub_contributor = "Zombie110year"
epub_theme = "epub"
epub_cover = ()
epub_pre_files = [
    ('index.html', '目录'),
]
epub_exclude_files = ['search.html', 'genindex.html']
epub_max_image_width = 400 # 400px
epub_show_urls = 'footnote'
# -- Options for PDF output --------------------------------------------------
# 不在 readthedocs 上编译
latex_engine = 'xelatex'
# latex_logo = '_images/logo.cpp.iso.svg'
latex_show_pagerefs = True # 渲染内部引用时增加对应的行号
latex_show_urls = 'footnote' # 在页面脚注中显示 URL 链接
latex_elements = {
    'papersize': 'a4paper', # A4 纸
    # 文档前缀, 进行宏包以及字体设置
    'preamble' : r"""
\usepackage{xeCJK}
\usepackage{indentfirst}
\setlength{\parindent}{2em}
\setCJKmainfont{Source Han Serif SC}
\setmainfont{Source Han Sans SC}
\setmonofont{Sarasa Mono SC}
""",
    'babel': '', # 不用 babel 宏包
    'extraclassoptions': 'openany,oneside', # 单页样式 (电子书)
    'maketitle': r"\maketitle"
}
latex_documents = [
    # 主页, 输出文件名, 标题, 作者, 文档类型
    ("index", "c-and-cpp.v{}.tex".format(release), "C 与 C++", author, "book")
]
