#!/usr/bin/env bash

#
# Script: client.sh
# Usage: ./client.sh
#
# Send a simple HTTP message
#

# Set defaults
set -o nounset -o errexit -o errtrace -o pipefail

# Port for socket
PORT="666"

# Execute request
curl \
    -X POST \
    -H "Content-Type: text/plain" \
    -d "Client test message" \
    "http://localhost:${PORT}"