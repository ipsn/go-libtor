FROM golang:alpine

RUN apk add --no-cache git gcc musl-dev linux-headers

ADD . $GOPATH/src/github.com/ipsn/go-libtor
RUN cd $GOPATH/src/github.com/ipsn/go-libtor && go get && go install
