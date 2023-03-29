#!/bin/bash

# directory/storage/client/ALL
MODULE=$1
MODULES=("directory" "storage" "client")

# if no proxy required, set PROXY="OFF"
PROXY="ON"
PROXY_SERVER=$(head -n 1 scripts/proxy.conf)
# PROXY_SERVER=$http_proxy

BUILD_ARGS=""
if [ "$PROXY" == "ON" ]; then
    BUILD_ARGS="--build-arg http_proxy=$PROXY_SERVER --build-arg https_proxy=$PROXY_SERVER"
fi

if [ -z "$MODULE" ] || [ "$MODULE" == "ALL" ]; then
    for mod in "${MODULES[@]}"
    do
        docker build $BUILD_ARGS -t jiffy-$mod:0.1.0 -f docker/Dockerfile.$mod .
    done
elif [ "$MODULE" == "directory" ] || [ "$MODULE" == "storage" ] || [ "$MODULE" == "client" ]; then
    docker build $BUILD_ARGS -t jiffy-$MODULE:0.1.0 -f docker/Dockerfile.$MODULE .
else
    echo "Usage: build-image.sh [directory | storage | client | ALL]"
fi

# build jiffy-directory
# docker build $BUILD_ARGS -t jiffy-directory:0.1.0 -f docker/Dockerfile.directory .

# build jiffy-storage
# docker build $BUILD_ARGS -t jiffy-storage:0.1.0 -f docker/Dockerfile.storage .

#build jiffy-client
# docker build $BUILD_ARGS -t jiffy-client:0.1.0 -f docker/Dockerfile.client .