# [Choice] Debian / Ubuntu version (use Debian 11, Ubuntu 18.04/22.04 on local arm64/Apple Silicon): debian-11, debian-10, ubuntu-22.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT=ubuntu-22.04
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

# Install needed packages. Use a separate RUN statement to add your own dependencies.
COPY library-scripts/meta.env /usr/local/etc/vscode-dev-containers
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install build-essential cmake cppcheck valgrind clang lldb llvm gdb autoconf libicu-dev \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Setup ENV vars for vcpkg
ENV VCPKG_ROOT=/usr/local/vcpkg \
    VCPKG_DOWNLOADS=/usr/local/vcpkg-downloads
ENV PATH="${PATH}:${VCPKG_ROOT}"

ARG USERNAME=vscode

# Install vcpkg itself: https://github.com/microsoft/vcpkg/blob/master/README.md#quick-start-unix
COPY base-scripts/install-vcpkg.sh /tmp/
RUN /tmp/install-vcpkg.sh ${USERNAME} \
    && rm -f /tmp/install-vcpkg.sh

# [Optional] Uncomment this section to install additional OS packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends python3-venv python3-pip

# [Optional] Uncomment this section to install additional packages.
RUN python3 -m pip install clang-format
RUN python3 -m pip install cmakelang

# [Optional] Install CMake version different from what base image has already installed.
# CMake reinstall choices: none, 3.21.5, 3.22.2, or versions from https://cmake.org/download/
ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.24.1"

# Optionally install the cmake for vcpkg
COPY base-scripts/reinstall-cmake.sh /tmp/
RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
    chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# Install SQL Tools: SQLPackage and sqlcmd
COPY mssql/install-sqltools.sh install-sqltools.sh
RUN bash ./install-sqltools.sh \
    && apt-get clean -y && rm -rf /var/lib/apt/lists/* /tmp/library-scripts

# Install ChakraCore for Linux
COPY library-scripts/install-chakracore.sh /tmp/
RUN chmod +x /tmp/install-chakracore.sh && /tmp/install-chakracore.sh && rm -f /tmp/install-chakracore.sh

# ODB install choices versions from https://www.codesynthesis.com/products/odb/download.xhtml | https://www.codesynthesis.com/products/odb/doc/install-unix.xhtml
ARG INSTALL_ODB_VERSION_FROM_SOURCE="2.4"
ARG INSTALL_ODB_PACKAGE_VERSION_FROM_SOURCE="2.4.0-1"

# Install ODB for C++ ORM Database Library
COPY library-scripts/install-odb.sh /tmp/
RUN if [ "${INSTALL_ODB_VERSION_FROM_SOURCE}" != "none" ] && [ "${INSTALL_ODB_PACKAGE_VERSION_FROM_SOURCE}" != "none" ]; then \
    chmod +x /tmp/install-odb.sh && /tmp/install-odb.sh ${INSTALL_ODB_VERSION_FROM_SOURCE} ${INSTALL_ODB_PACKAGE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/install-odb.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install boost"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install boost-asio"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install boost-range"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install benchmark"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install celero"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install grpc"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install apsi"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install asio"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install asio-grpc"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install bitserializer"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install tinyxml2"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install cpp-jwt"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install range-v3"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install refl-cpp"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install rxcpp"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install lmdb"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install sqlite3"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install mongo-c-driver"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install mongo-cxx-driver"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install libpq"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install libxlsxwriter"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install libharu"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install libyaml"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install bext-di"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install bext-sml"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install bext-ut"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install ryml"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install czmq"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install azmq"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install zeromq"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install log4cplus"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install microsoft-signalr"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install cpprestsdk"
RUN su vscode -c "${VCPKG_ROOT}/vcpkg install google-cloud-cpp"

# TODO: Packages to install manually
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install nanodbc"    # https://github.com/nanodbc/nanodbc
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install libmariadb" # https://github.com/mariadb-corporation/mariadb-connector-c

# Only supported on 'windows & !arm'
# RUN su vscode -c "/usr/local/vcpkg/vcpkg install rsasynccpp"

# Only supported on '!(arm | arm64 | uwp | osx | linux)'
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install v8"
