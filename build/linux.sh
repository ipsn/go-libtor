#!/bin/bash

sudo apt update
sudo apt install autoconf automake make libssl-dev libevent-dev zlib1g-dev -y
if [ "$?" != "0" ] ; then
 echo "Install failed"
 exit 1
fi

go version
go env
autoconf --version
automake --version
make --version
gcc --version

echo "Building"

go run build/wrap.go --update
if [ "$?" != "0" ] ; then
 echo "Error building"
 exit 1
fi

cd ..
tar cvf /tmp/go-libtor.tar go-libtor/
