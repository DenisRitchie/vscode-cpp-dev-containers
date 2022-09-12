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

export DEBIAN_FRONTEND=noninteractive

# Install additional packages needed by vcpkg: https://github.com/microsoft/vcpkg/blob/master/README.md#installing-linux-developer-tools
check_packages git build-essential ninja-build clang libicu-dev

# https://github.com/chakra-core/ChakraCore/wiki/Building-ChakraCore
# Start Installation
# Clone repository with ports and installer
git clone https://github.com/Microsoft/ChakraCore chakracore

# Let's build!
cd chakracore && ./build.sh -y -n --static -j=14
