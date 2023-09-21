#!/usr/bin/env bash

#
# Script: count-file-extensions.sh
# Usage: ./count-file-extensions.sh
#
# Groups files by their extension and counts each group.
# Includes sub-directories.
# Ref: https://stackoverflow.com/a/31870034/5024990
#

# Set defaults
set -o nounset -o errexit -o errtrace -o pipefail

# Directory to write media to
MEDIA_DIR="${HOME}/Desktop/Media"

# Count file extensions
find "${MEDIA_DIR}" -type f -name '*.*' | sed 's|.*\.||' | sort | uniq -c