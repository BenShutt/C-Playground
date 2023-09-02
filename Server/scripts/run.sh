#!/usr/bin/env bash

#
# Script: run.sh
# Usage: ./run.sh
#
# Clean, make, and run the executable
#

# Set defaults
set -o nounset -o errexit -o errtrace -o pipefail

# The directory of this script
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# Path to the executable
EXE="${SCRIPT_DIR}/../bin/main"

# Port for socket
PORT="666"

# Number of characters for socket
N_CHAR="1048576" # 1MB

# Directory to write files into
DIR="${HOME}/Desktop"

# Clean, make, and run the executable
make clean && make && ${EXE} ${PORT} ${N_CHAR} ${DIR} && make clean
