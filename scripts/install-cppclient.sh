#!/bin/bash

ARGS="-it --rm -v $(realpath cppclient):/opt/jiffy/cppclient --entrypoint cp"
cmd_cli="/usr/local/lib/libjiffy_client.a /opt/jiffy/cppclient/lib/"
cmd_dir="/opt/jiffy/build/external/thrift_ep/lib/libthrift.a /opt/jiffy/build/external/thrift_ep/lib/libthriftnb.a /opt/jiffy/cppclient/lib/"

docker run --name jiffy-cppclient-client $ARGS jiffy-client:0.1.0 $cmd_cli
docker run --name jiffy-cppclient-directory $ARGS jiffy-directory:0.1.0 $cmd_dir