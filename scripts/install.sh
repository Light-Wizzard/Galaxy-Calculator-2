#! /bin/bash
# Galaxy Calculator 2
#
# Last Update: 20 July 2021
#
# shell?check -x scripts/install.sh

if [[ "$APPVEYOR_BUILD_WORKER_IMAGE" = "Ubuntu" ]]; then
    # Python
    sudo add-apt-repository ppa:deadsnakes/ppa -y;
    sudo apt-get update -qq && sudo apt-get install -qq;
    #sudo apt-get upgrade -qqy;
    sudo apt install -qqy build-essential libssl-dev zlib1g-dev libncurses5-dev libncursesw5-dev libreadline-dev libsqlite3-dev;
    sudo apt install -qqy libgdbm-dev libdb5.3-dev libbz2-dev libexpat1-dev liblzma-dev tk-dev libffi-dev mesa-common-dev flex bison;
    sudo apt-get install -qqy cmake software-properties-common python3.9-dev python3-venv checkinstall libglu1-mesa-dev freeglut3-dev;
    sudo apt-get install -qqy libxcb-icccm4 libxcb-image0 libxcb-keysyms1 libxcb-render-util0 libxcb-xinerama0 libxcb-xkb-dev libxkbcommon-x11-0 libgtk2.0-dev;
fi
