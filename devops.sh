#!/bin/bash

./scripts/build-image.sh ALL
docker rmi $(docker images -f "dangling=true" -q)
./scripts/install-cppclient.sh
./scripts/server-ctl.sh start ALL