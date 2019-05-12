#! /usr/bin/bash

echo 需要安装 texlive 以及 Sarasa, Source Han 字体
echo 在项目根目录以 ./tools/build-pdf.sh 的方式运行
version='0.1.0rc'
file_basename="c-cpp.v${version}"
echo ${file_basename}

cd build/latex
xelatex "${file_basename}.tex"
xelatex "${file_basename}.tex"

cp "${file_basename}.pdf" ..
# 放到 build 目录中
