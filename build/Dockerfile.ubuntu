FROM golang:latest

ADD . $GOPATH/src/github.com/ipsn/go-libtor
RUN cd $GOPATH/src/github.com/ipsn/go-libtor && go get && go install
