#!/bin/bash

if ! [[ "18.04 20.04 22.04" == *"$(lsb_release -rs)"* ]];
then
    echo "Ubuntu $(lsb_release -rs) is not currently supported.";
    exit;
fi

# Add to bashrc/zshrc files for all users.
updaterc()  {
    echo "Updating /etc/bash.bashrc and /etc/zsh/zshrc..."
    if [[ "$(cat /etc/bash.bashrc)" != *"$1"* ]]; then
        echo -e "$1" >> /etc/bash.bashrc
    fi
    if [ -f "/etc/zsh/zshrc" ] && [[ "$(cat /etc/zsh/zshrc)" != *"$1"* ]]; then
        echo -e "$1" >> /etc/zsh/zshrc
    fi
}

curl https://packages.microsoft.com/keys/microsoft.asc | apt-key add -

curl https://packages.microsoft.com/config/ubuntu/$(lsb_release -rs)/prod.list > /etc/apt/sources.list.d/mssql-release.list

apt-get update && ACCEPT_EULA=Y apt-get install -y msodbcsql18

# optional: for bcp and sqlcmd
ACCEPT_EULA=Y apt-get install -y mssql-tools18

# Add mssql-tools to PATH
updaterc "$(cat << EOF
export PATH="$PATH:/opt/mssql-tools18/bin"
EOF
)"

# optional: for unixODBC development headers
apt-get install -y unixodbc-dev
