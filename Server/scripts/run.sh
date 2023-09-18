#!/usr/bin/env bash

#
# Script: run.sh
# Usage: ./run.sh
#
# Clean, make, and run the executable
#

# Set defaults
set -o nounset -o errexit -o errtrace -o pipefail

# ============================== Variables ==============================

# The directory of this script
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# Path to the executable
EXE="${SCRIPT_DIR}/../bin/main"

# Directory to write images to
DIR="${HOME}/Desktop/Images"

# ============================== Main ==============================

# Make the directory if it doesn't exist
mkdir -p "${DIR}"

# Clean, make, and run the executable
make clean && make && "${EXE}" "${DIR}" && make clean
