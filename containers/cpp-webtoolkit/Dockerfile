ARG VARIANT=latest
FROM archlinux:${VARIANT}
USER root

# Install needed packages. Use a separate RUN statement to add your own dependencies.
RUN pacman --noconfirm -Sy --needed gcc clang lldb llvm gdb cmake cppcheck valgrind git base-devel
RUN pacman --noconfirm -Sy --needed zip unzip pkg-config bash-completion ninja autoconf automake autoconf-archive
RUN pacman --noconfirm -Sy --needed libxmu libxi libgl

# Setup ENV vars for vcpkg
ENV VCPKG_ROOT=/usr/local/vcpkg \
    VCPKG_DOWNLOADS=/usr/local/vcpkg-downloads
ENV PATH="${PATH}:${VCPKG_ROOT}"

# Setup group and add user
RUN umask 0002
RUN groupadd -r "vcpkg"
RUN usermod -a -G "vcpkg" "root"

# Start Installation
# Clone repository with ports and installer
RUN mkdir -p "${VCPKG_ROOT}"
RUN mkdir -p "${VCPKG_DOWNLOADS}"

RUN git clone https://github.com/microsoft/vcpkg.git "${VCPKG_ROOT}"
RUN "${VCPKG_ROOT}"/bootstrap-vcpkg.sh

# Add to bashrc/zshrc files for all users.
RUN echo -e "EOF \
    export VCPKG_ROOT="${VCPKG_ROOT}" \
    if [[ "\${PATH}" != *"\${VCPKG_ROOT}"* ]]; then \
        	export PATH="\${PATH}:\${VCPKG_ROOT}"; \
    fi EOF" >> /etc/bash.bashrc

# Give read/write permissions to the user group.
RUN chown -R ":vcpkg" "${VCPKG_ROOT}" "${VCPKG_DOWNLOADS}"
RUN chmod g+r+w+s "${VCPKG_ROOT}" "${VCPKG_DOWNLOADS}"
RUN chmod -R g+r+w "${VCPKG_ROOT}" "${VCPKG_DOWNLOADS}"

# Enable tab completion for bash and zsh
# RUN VCPKG_FORCE_SYSTEM_BINARIES=1 ${VCPKG_ROOT}/vcpkg integrate bash

# [Optional] Uncomment this section to install additional vcpkg ports.

RUN ${VCPKG_ROOT}/vcpkg install boost --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install abseil --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install openssl --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install asio --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install benchmark --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install cpp-jwt --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install jwt-cpp --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install tinyxml2 --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install refl-cpp --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install bext-di --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install bext-sml --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install bext-ut --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install libharu --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install libxlsxwriter --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install log4cplus --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install cpprestsdk --only-downloads
# RUN ${VCPKG_ROOT}/vcpkg install microsoft-signalr --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install nlohmann-json --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install cpp-httplib --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install libxml2 --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install tinyxml2 --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install sqlite3 --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install libpq --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install libpqxx --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install doctest --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install range-v3 --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install bitserializer --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install protobuf --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install protobuf-c --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install websocketpp --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install telnetpp --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install wt --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install grpc --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install asio-grpc --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install crow --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install hiredis --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install redis-plus-plus --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install cpp-redis --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install mongoose --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install mongo-c-driver --only-downloads
RUN ${VCPKG_ROOT}/vcpkg install mongo-cxx-driver --only-downloads

RUN ${VCPKG_ROOT}/vcpkg install wt
RUN ${VCPKG_ROOT}/vcpkg install abseil
RUN ${VCPKG_ROOT}/vcpkg install openssl
RUN ${VCPKG_ROOT}/vcpkg install asio
RUN ${VCPKG_ROOT}/vcpkg install benchmark
RUN ${VCPKG_ROOT}/vcpkg install cpp-jwt
RUN ${VCPKG_ROOT}/vcpkg install jwt-cpp
RUN ${VCPKG_ROOT}/vcpkg install tinyxml2
RUN ${VCPKG_ROOT}/vcpkg install refl-cpp
RUN ${VCPKG_ROOT}/vcpkg install bext-di
RUN ${VCPKG_ROOT}/vcpkg install bext-sml
RUN ${VCPKG_ROOT}/vcpkg install bext-ut
RUN ${VCPKG_ROOT}/vcpkg install libharu
RUN ${VCPKG_ROOT}/vcpkg install libxlsxwriter
RUN ${VCPKG_ROOT}/vcpkg install log4cplus
RUN ${VCPKG_ROOT}/vcpkg install cpprestsdk
# RUN ${VCPKG_ROOT}/vcpkg install microsoft-signalr --recurse
RUN ${VCPKG_ROOT}/vcpkg install nlohmann-json
RUN ${VCPKG_ROOT}/vcpkg install cpp-httplib
RUN ${VCPKG_ROOT}/vcpkg install libxml2
RUN ${VCPKG_ROOT}/vcpkg install tinyxml2
RUN ${VCPKG_ROOT}/vcpkg install sqlite3
RUN ${VCPKG_ROOT}/vcpkg install libpq
RUN ${VCPKG_ROOT}/vcpkg install libpqxx
RUN ${VCPKG_ROOT}/vcpkg install doctest
RUN ${VCPKG_ROOT}/vcpkg install range-v3
RUN ${VCPKG_ROOT}/vcpkg install bitserializer
RUN ${VCPKG_ROOT}/vcpkg install protobuf
RUN ${VCPKG_ROOT}/vcpkg install protobuf-c
RUN ${VCPKG_ROOT}/vcpkg install websocketpp
RUN ${VCPKG_ROOT}/vcpkg install telnetpp
RUN ${VCPKG_ROOT}/vcpkg install grpc
RUN ${VCPKG_ROOT}/vcpkg install asio-grpc
RUN ${VCPKG_ROOT}/vcpkg install crow
RUN ${VCPKG_ROOT}/vcpkg install hiredis
RUN ${VCPKG_ROOT}/vcpkg install redis-plus-plus
RUN ${VCPKG_ROOT}/vcpkg install cpp-redis
RUN ${VCPKG_ROOT}/vcpkg install mongoose
RUN ${VCPKG_ROOT}/vcpkg install mongo-c-driver
RUN ${VCPKG_ROOT}/vcpkg install mongo-cxx-driver
RUN ${VCPKG_ROOT}/vcpkg install boost
