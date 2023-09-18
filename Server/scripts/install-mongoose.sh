#!/usr/bin/env bash

#
# Script: install-mongoose.sh
# Usage: ./install-mongoose.sh
#
# Downloads and installs the Mongoose library.
# https://mongoose.ws/documentation
#

# Set defaults
set -o nounset -o errexit -o errtrace -o pipefail

# ============================== Variables ==============================

# Directory of this script
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# Directory of the project lib directory
LIB_DIR="${SCRIPT_DIR}/../lib"

# Directory of the project include directory
INCLUDE_DIR="${SCRIPT_DIR}/../include"

# Name of the library that we are building
TARGET="mongoose"

# Local tmp directory
TMP_DIR="/tmp/${TARGET}"

# Github raw-content URL to download source files from
REMOTE_URL="https://raw.githubusercontent.com/cesanta/mongoose/master"

# Max receive buffer size
MAX_RECV_SIZE="$((12 * 1024 * 1024))" # 12MB

# ============================== Functions ==============================

# Remove temporary directory
function cleanup {
    rm -rf "${TMP_DIR}"
}

# Download the given file locally from the remote
function download {
    curl "${REMOTE_URL}/$1" -o "$1"
}

# ============================== Main ==============================

# Clean up on exit
trap cleanup EXIT

# Clean up initially
cleanup

# Make and move into the tmp directory
mkdir -p "${TMP_DIR}" && cd "${TMP_DIR}"

# Download the header file
download "${TARGET}.h"

# Download the source file
download "${TARGET}.c"

# Compile into object file
clang -c -o "${TARGET}.o" "${TARGET}.c" -D "MG_MAX_RECV_SIZE=${MAX_RECV_SIZE}"

# Make the library file
ar ru "lib${TARGET}.a" "${TARGET}.o"

# Archive the library
ranlib "lib${TARGET}.a"

# Make the destination include directory if it doesn't exist
# and move the header file to it
mkdir -p "${INCLUDE_DIR}" && mv "${TARGET}.h" "${INCLUDE_DIR}"

# Make the destination library directory if it doesn't exist
# and move the library file to it
mkdir -p "${LIB_DIR}" && mv "lib${TARGET}.a" "${LIB_DIR}"