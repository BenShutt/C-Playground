#!/usr/bin/env bash

#
# Script: install-c-json.sh
# Usage: ./install-c-json.sh
#
# Downloads and installs the cJSON library into the project lib directory.
#

# Set defaults
set -o nounset -o errexit -o errtrace -o pipefail

# ============================== Variables ==============================

# The directory of this script
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# Name of the repository to download and install
REPOSITORY_NAME="cJSON"

# URL of the repository to clone
CLONE_URL="https://github.com/DaveGamble/${REPOSITORY_NAME}.git"

# Local directory where files are written to temporarily
TMP_REPOSITORY_DIR="/tmp/${REPOSITORY_NAME}"

# Local directory of the project
PROJECT_DIR="${SCRIPT_DIR}/.."

# ============================== Functions ==============================

# Clean up temporary files
function cleanup {
    rm -rf "${TMP_REPOSITORY_DIR}"
}

# ============================== Main ==============================

# Clean up on exit
trap cleanup EXIT

# Clean up initially
cleanup

# Clone the repository from the remote to the local directory
git clone -b master "${CLONE_URL}" "${TMP_REPOSITORY_DIR}" && cd "${TMP_REPOSITORY_DIR}"

# Make a build directory for cmake to write to and make the library
mkdir -p build && cd build
cmake .. \
    -DBUILD_SHARED_AND_STATIC_LIBS=On \
    -DENABLE_CJSON_UTILS=On \
    -DENABLE_CJSON_TEST=Off \
    -DCMAKE_INSTALL_PREFIX="${PROJECT_DIR}"
make install

# Remove .dylib files in preference of .a
find "${PROJECT_DIR}/lib" -name "*.dylib" -delete