#!/usr/bin/env bash

set -e

# Run apt-get if needed.
apt_get_update_if_needed() {
    if [ ! -d "/var/lib/apt/lists" ] || [ "$(ls /var/lib/apt/lists/ | wc -l)" = "0" ]; then
        echo "Running apt-get update..."
        apt-get update
        apt-get dist-upgrade
    else
        echo "Skipping apt-get update."
    fi
}

# Check if packages are installed and installs them if not.
check_packages() {
    if ! dpkg -s "$@" > /dev/null 2>&1; then
        apt_get_update_if_needed
        apt-get -y install --no-install-recommends "$@"
    fi
}

# Cleanup temporary directory and associated files when exiting the script.
cleanup() {
    EXIT_CODE=$?
    set +e
    if [[ -n "${TMP_DIR}" ]]; then
        echo "Executing cleanup of tmp files"
        rm -Rf "${TMP_DIR}"
    fi
    exit $EXIT_CODE
}

trap cleanup EXIT

TMP_DIR=$(mktemp -d -t chakracore-XXXXXXXXXX)

cd ${TMP_DIR}

export DEBIAN_FRONTEND=noninteractive

# Install additional packages needed by vcpkg: https://github.com/microsoft/vcpkg/blob/master/README.md#installing-linux-developer-tools
check_packages git build-essential ninja-build clang libicu-dev

# https://github.com/chakra-core/ChakraCore/wiki/Building-ChakraCore
# Start Installation
# Clone repository with ports and installer
git clone https://github.com/Microsoft/ChakraCore ${TMP_DIR}/chakracore

# Let's build!
cd ${TMP_DIR}/chakracore && ./build.sh -y -n --static -j=14
