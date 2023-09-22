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

# Makefile target
TARGET="bin/main"

# Path to the executable
EXE="${SCRIPT_DIR}/../${TARGET}"

# Directory to write media to
MEDIA_DIR="${HOME}/Desktop/Media"

# ============================== Functions ==============================

function clean {
    make "clean"
}

function build {
    make "${TARGET}"
}

function run {
    "${EXE}" "${MEDIA_DIR}"
}

# ============================== Main ==============================

# Make the directory if it doesn't exist
mkdir -p "${MEDIA_DIR}"

# Clean, make, and run the executable
clean && build && run && clean
