#!/usr/bin/env bash

#
# Script: install-c-json.sh
# Usage: ./install-c-json.sh
#
# Downloads and installs the cJSON library into the project lib 
# directory using cmake.
#

# ============================== Variables ==============================

# The directory of this script
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# Name of the repository to download and install
REPOSITORY_NAME="cJSON"

# URL of the repository to clone
CLONE_URL="https://github.com/DaveGamble/${REPOSITORY_NAME}.git"

# Local directory where files are written to temporarily
REPOSITORY_DIR="/tmp/${REPOSITORY_NAME}"

# Name of the library (that is created) to install
LIBRARY_NAME="libcjson.dylib"

# Destination to write to
DST="${SCRIPT_DIR}/../lib/${LIBRARY_NAME}"

# ============================== Functions ==============================

# Clean up temporary files
function cleanup {
    rm -rf "${REPOSITORY_DIR}"
}

# ============================== Main ==============================

# Clean up on exit
trap cleanup EXIT

# Clean up initially
cleanup

# Make the local repository directory
mkdir -p "${REPOSITORY_DIR}"

# Clone the repository from the remote to the local directory
git clone -b master "${CLONE_URL}" "${REPOSITORY_DIR}" && cd "${REPOSITORY_DIR}"

# Make a build directory for cmake to write to and make the library
mkdir -p build && cd build
cmake ..
make all

# Move the library
cp "${LIBRARY_NAME}" "${DST}"

# Success
echo "Success, ${REPOSITORY_NAME} written to '${DST}'"