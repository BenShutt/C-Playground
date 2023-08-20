#!/usr/bin/env bash

#
# Script: client.sh
# Usage: ./client.sh
#
# Send a message to the server
#

# Set defaults
set -o nounset -o errexit -o errtrace -o pipefail

# Execute request
curl \
    -X POST \
    -H "Content-Type: text/plain" \
    -d "Client test message" \
    http://localhost:666