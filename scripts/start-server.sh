#!/bin/bash

SERVER=$1
SERVERS=("directory" "storage")

START_ARGS="-d --rm --privileged --net=host -v $(realpath docker):/opt/jiffy/docker"

if [ -z "$SERVER" ] || [ "$SERVER" == "ALL" ]; then
    for server in "${SERVERS[@]}"
    do
        docker run --name jiffy-$server $START_ARGS jiffy-$server:0.1.0
    done
elif [ "$SERVER" == "directory" ] || [ "$SERVER" == "storage" ]; then
    docker run --name jiffy-$SERVER $START_ARGS jiffy-$SERVER:0.1.0
else
    echo "Usage: start-server.sh [directory | storage | ALL]"
fi