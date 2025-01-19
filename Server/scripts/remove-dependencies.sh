#!/usr/bin/env bash

#
# Script: remove-dependencies.sh
# Usage: ./remove-dependencies.sh
#
# Removes the "include" and "lib" directories.
#

# Set defaults
set -o nounset -o errexit -o errtrace -o pipefail

# Directory of this script
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# Directory of the project lib directory
LIB_DIR="${SCRIPT_DIR}/../lib"

# Directory of the project include directory
INCLUDE_DIR="${SCRIPT_DIR}/../include"

# Remove lib directory
rm -rf "${LIB_DIR}"

# Remove include directory
rm -rf "${INCLUDE_DIR}"