cd build/html && git init && git checkout -b gh-pages && git add -A && git commit -m "update"
git remote add publish git@github.com:zombie110year/c-cpp.git
git push -f publish gh-pages
