#!/usr/bin/env bash

#
# WIP
# Script: check-corrupt-media.sh
# Usage: ./check-corrupt-media.sh
#
# Check that all images and videos in the media directory
# have been transferred successfully.
#

# Set defaults
set -o nounset -o errexit -o errtrace -o pipefail

# ==================== Constants ====================

# Directory to read media from
MEDIA_DIR="${HOME}/Desktop/Media"

# Temporary file to write ffmpeg logs
TMP_LOG_FILE="/tmp/test.log"

# ==================== Functions ====================

# Remove temporary log file
function clean {
    rm -rf "${TMP_LOG_FILE}"
}

# Function that finds videos in the media directory
function findVideoPaths {
    find "${MEDIA_DIR}" -type f -iname '*.mov' -or -iname '*mp4'
}

# Use ffmpeg to check a video's integrity
function recodeVideo {
    ffmpeg -v error -i "$1" -f null - 2>"${TMP_LOG_FILE}"
}

# Check a video is 
function testVideo {
    echo "Testing $1..."
    clean
    recodeVideo "$1"
    if [[ -s "${TMP_LOG_FILE}" ]]; then
        echo "$1" is a corrupt file
    else
        echo "$1" is valid
    fi
}

# ==================== Main ====================

# Clean on exit
trap clean EXIT

# Check ffmpeg exists
if ! [ -x "$(command -v ffmpeg)" ]; then
  echo "Please make sure ffmpeg is installed." 1>&2
  exit 1
fi

# Iterate through videos
videoPaths=( $(findVideoPaths) )
for videoPath in "${videoPaths[@]}"; do
    testVideo "${videoPath}"
done