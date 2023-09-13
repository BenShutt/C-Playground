#!/usr/bin/env bash

#
# Script: client.sh
# Usage: ./client.sh <arguments>
# See README.md for arguments.
#
# Run the Client Swift Package executable.
#

# Set defaults
set -o nounset -o errtrace -o pipefail

# Check that Swift is installed
swift -version &>/dev/null
if [[ $? != 0 ]]; then
    echo "Please ensure that Swift is installed. Exiting..." >&2
    exit 1
fi

# From here, ensure errexit is enabled
set -o errexit

# Build the Swift Package
echo "Building the Swift Package..."
swift build --configuration release

# Move into build directory
cd ".build/release/"

# Run the Executable
./Client "$@"
