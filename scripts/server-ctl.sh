#!/bin/bash

CMD=$1
SERVER=$2
SERVERS=("directory" "storage")

START_ARGS="-d --rm --privileged --net=host -v $(realpath docker):/opt/jiffy/docker"
if [ "$CMD" == "start" ]; then
    if [ -z "$SERVER" ] || [ "$SERVER" == "ALL" ]; then
        for server in "${SERVERS[@]}"
        do
            docker run --name jiffy-$server $START_ARGS jiffy-$server:0.1.0
        done
    elif [ "$SERVER" == "directory" ] || [ "$SERVER" == "storage" ]; then
        docker run --name jiffy-$SERVER $START_ARGS jiffy-$SERVER:0.1.0
    else
        echo "Usage: server-ctl.sh [start | stop] [directory | storage | ALL]"
    fi
elif [ "$CMD" == "stop" ]; then
    if [ -z "$SERVER" ] || [ "$SERVER" == "ALL" ]; then
        servers=""
        for server in "${SERVERS[@]}"
        do
            servers="${servers} jiffy-${server}"
        done
        docker stop -t 1 $servers
    elif [ "$SERVER" == "directory" ] || [ "$SERVER" == "storage" ]; then
        docker stop -t 1 jiffy-$SERVER
    else
        echo "Usage: server-ctl.sh [start | stop] [directory | storage | ALL]"
    fi
else
    echo "Usage: server-ctl.sh [start | stop] [directory | storage | ALL]"
fi