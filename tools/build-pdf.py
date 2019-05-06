#! /usr/bin/python3
# coding: utf-8
"""
环境:

1. 安装 texlive 2017 或以上
2. 安装 Adobe 思源字体
3. 安装 Sarasa 更纱字体
"""
from subprocess import run, PIPE

texlive_cmd = "xelatex"


def check_env():
    """检查环境
    """
    source_id = "SourceHan"
    sarasa_id = "Sarasa"

    output = run(['fc-list', ':lang=zh'], encoding='utf-8', capture_output=True).stdout

    have_texlive = True if run(['which', texlive_cmd]).returncode == 0 else False
    have_sarasa = True if sarasa_id in output else False
    have_source = True if source_id in output else False

    return have_texlive and have_source and have_sarasa

def build_pdf():
    """将 tex 文件编译成 pdf 文件
    """
    run(["make"], shell=True, cwd="../build/latex/")


if __name__ == "__main__":
    if check_env():
       build_pdf()
