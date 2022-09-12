#!/usr/bin/env bash

set -e

ODB_VERSION=${1:-"none"}
ODB_PACKAGE_VERSION=${2:-"none"}

if [  "$#" != "2" ]; then
    echo "No ODB version and sub-version specified, skipping ODB installation"
    exit 0
fi

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

echo "Installing ODB..."

architecture=$(dpkg --print-architecture)
case "${architecture}" in
    arm64)
        ARCH=i386 ;;
    amd64)
        ARCH=amd64 ;;
    *)
        echo "Unsupported architecture ${architecture}."
        exit 1
        ;;
esac

ODB_PACKAGE_NAME="odb_${ODB_PACKAGE_VERSION}_${ARCH}.deb"
ODB_CHECKSUM_NAME="odb_${ODB_PACKAGE_VERSION}_${ARCH}.deb.sha1"
TMP_DIR=$(mktemp -d -t odb-XXXXXXXXXX)

echo "ODB_PACKAGE_NAME: ${ODB_PACKAGE_NAME}"
echo "ODB_CHECKSUM_NAME: ${ODB_CHECKSUM_NAME}"
echo "TMP_DIR: ${TMP_DIR}"
cd "${TMP_DIR}"

curl -sSL "https://www.codesynthesis.com/download/odb/${ODB_VERSION}/${ODB_PACKAGE_NAME}" -O
curl -sSL "https://www.codesynthesis.com/download/odb/${ODB_VERSION}/${ODB_CHECKSUM_NAME}" -O

sha1sum -c --ignore-missing "${TMP_DIR}/${ODB_CHECKSUM_NAME}"

dpkg -i "${TMP_DIR}/${ODB_PACKAGE_NAME}"
