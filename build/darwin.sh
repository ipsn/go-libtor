#!/bin/bash

brew install pkg-config openssl@1.1 autoconf automake
export PKG_CONFIG_PATH="PKG_CONFIG_PATH:/usr/local/opt/openssl@1.1/lib/pkgconfig/"
if [ "$?" != "0" ] ; then
 echo "Install failed"
 exit 1
fi

mv /tmp/go-libtor.tar .
if [ "$?" != "0" ] ; then
 echo "move failed"
 exit 1
fi
tar xf go-libtor.tar
if [ "$?" != "0" ] ; then
 echo "unpack failed"
 exit 1
fi

cd go-libtor/

go version
go env
autoconf --version
automake --version
make --version
gcc --version

echo "Building"

go run build/wrap.go
if [ "$?" != "0" ] ; then
 echo "Error building"
 exit 1
fi

mkdir -p .ssh
echo "$GITHUB_ED25519_KEY" > .ssh/id_ed25519

git add .
if [ -n "$(git status --porcelain)" ]; then
 echo "New files, updating"
 git commit --author="Jorropo-berty-bot <github@action>" -m "Updated libtor dependencies."
 tag=`git describe --tags --abbrev=0` && git tag "`echo $tag | cut -d '.' -f -2`.$((`echo $tag | cut -d '.' -f 3`+1))"
fi

git push upstream master --tags
