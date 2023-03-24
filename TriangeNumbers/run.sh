#!/usr/bin/env bash

#
# Script: run.sh
# Usage: ./run.sh
#
# Clean, make, and run the program
#

# Set defaults
set -o nounset -o errexit -o errtrace -o pipefail

# The directory of this script
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# Path to the executable
EXE="${SCRIPT_DIR}/triangleNumbers"

# Run
make clean && make && ${EXE}
