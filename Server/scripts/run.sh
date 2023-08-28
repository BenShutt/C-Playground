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

# Clean, make, and run the executable
make clean && make && ${EXE} && make clean
