# Docker container to build Qt 5.12 for Linux 64-bits projects with latest linuxdeployqt, OpenSSL and SDL
# Image: galaxy-calculator-2-qt:5.12-gcc_64

FROM ubuntu:16.04.6
MAINTAINER MAINTAINER Jeffrey Scott Flesher <JeffreyScottFlesher@gmail.com>

ARG QT_VERSION=5.12.6
ARG LINUXDEPLOYQT_VERSION=continuous

ENV DEBIAN_FRONTEND=noninteractive QMAKESPEC=linux-g++ QT_PATH=/opt/qt QT_PLATFORM=gcc_64

ENV PATH=${QT_PATH}/${QT_VERSION}/${QT_PLATFORM}/bin:${OPENSSL_PREFIX}/bin:$PATH

# Install updates & requirements:
#  * git, openssh-client, ca-certificates - clone & build
#  * locales, sudo - useful to set utf-8 locale & sudo usage
#  * curl - to download Qt bundle
#  * build-essential, pkg-config, libgl1-mesa-dev - basic Qt build requirements
#  * libsm6, libice6, libxext6, libxrender1, libfontconfig1, libdbus-1-3 - dependencies of the Qt bundle run-file
#  * wget - another download utility
#  * libz-dev - OpenSSL dependencies
#  * fuse, file - linuxdeployqt dependencies
#  * libxkbcommon-x11-0 - run-time dependencies
#  * libgstreamer-plugins-base1.0-0 - QtMultimedia run-time dependencies
RUN apt update && apt full-upgrade -y && apt install -y --no-install-recommends \
    git \
    locales \
    sudo \
    curl \
    build-essential \
    pkg-config \
    libgl1-mesa-dev \
    libsm6 \
    libice6 \
    libxext6 \
    libxrender1 \
    libfontconfig1 \
    libdbus-1-3 \
    wget \
    libz-dev \
    fuse \
    file \
    libxkbcommon-x11-0 \
    && apt-get -qq clean

COPY docker/* /tmp/build/

# Download & unpack Qt toolchain
RUN /tmp/build/install-qt.sh

# Download & install linuxdeployqt
RUN /tmp/build/install-linuxdeployqt.sh

# Reconfigure locale
RUN locale-gen en_US.UTF-8 && dpkg-reconfigure locales && groupadd -r user && useradd --create-home --gid user user && echo 'user ALL=NOPASSWD: ALL' > /etc/sudoers.d/user

USER user
WORKDIR /home/user
ENV HOME /home/user
