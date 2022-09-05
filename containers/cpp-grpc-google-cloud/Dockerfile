# [Choice] Debian / Ubuntu version (use Debian 11, Ubuntu 18.04/22.04 on local arm64/Apple Silicon): debian-11, debian-10, ubuntu-22.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT=ubuntu-22.04
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# [Optional] Install CMake version different from what base image has already installed.
# CMake reinstall choices: none, 3.21.5, 3.22.2, or versions from https://cmake.org/download/
ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.24.1"

# Optionally install the cmake for vcpkg
COPY base-scripts/reinstall-cmake.sh /tmp/
RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
    chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install boost"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install grpc"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install asio"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install asio-grpc"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install boost-asio"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install google-cloud-cpp"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install microsoft-signalr"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install cpprestsdk"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install tinyxml2"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install cpp-jwt"

# [Optional] Uncomment this section to install additional packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends python3-venv python3-pip

# [Optional] Uncomment this section to install additional packages.
RUN python3 -m pip install clang-format
RUN python3 -m pip install cmakelang
