# inspired by https://github.com/siana-systems/cross-bbb-debian/blob/master/Dockerfile

FROM debian:jessie

# 1. Install basic development packages
# 2. Add armhf as new architecture
# 3. Install crosstools for armhf
RUN apt-get update -q && \
DEBIAN_FRONTEND=noninteractive apt-get install -y -q \
automake \
binutils \
cmake \
curl \
gawk \
git \
nano \
lib32stdc++6 \
lib32z1 \
libtool \
runit

RUN echo 'deb http://emdebian.org/tools/debian jessie main' > /etc/apt/sources.list.d/crosstools.list && \
curl http://emdebian.org/tools/debian/emdebian-toolchain-archive.key | apt-key add - && \
dpkg --add-architecture armhf && \
apt-get update -q && \
DEBIAN_FRONTEND=noninteractive apt-get install -y -q \
crossbuild-essential-armhf && \
apt-get -q -y clean && \
cd /usr/bin && \
ln -s arm-linux-gnueabihf-cpp-* arm-linux-gnueabihf-cpp
# may have to fix previous link provided cpp-4.9 is other version...

# Hardcode of toolchain
ENV HOST=arm-linux-gnueabihf \
    CROSS_ROOT_BINDIR=/usr/bin

ENV ARCH=arm \
    CROSS_COMPILE=${CROSS_ROOT_BINDIR}/${HOST}- \
    ARM_CROSS_COMPILER=TRUE

ENV AS=${CROSS_COMPILE}as \
    AR=${CROSS_COMPILE}ar \
    CC=${CROSS_COMPILE}gcc \
    CPP=${CROSS_COMPILE}cpp \
    CXX=${CROSS_COMPILE}g++ \
    LD=${CROSS_COMPILE}ld

RUN curl -O https://storage.googleapis.com/golang/go1.8rc1.linux-amd64.tar.gz
RUN tar -C /usr/local -xzf go1.8rc1.linux-amd64.tar.gz

RUN a=c curl -O "http://downloads.ti.com/codegen/esd/cgt_public_sw/PRU/2.1.4/ti_cgt_pru_2.1.4_linux_installer_x86.bin"
RUN chmod a+x ti_cgt_pru_2.1.4_linux_installer_x86.bin
RUN /ti_cgt_pru_2.1.4_linux_installer_x86.bin
ENV PRU_CGT /ti-cgt-pru_2.1.4

ENV PATH "$PATH:/usr/local/go/bin"
ENV GOPATH /go
ENV GOOS linux
ENV GOARCH arm
ENV GOARM 7
ENV CGO_ENABLED 1

COPY vendor/include /usr/include/
COPY vendor/lib /usr/lib/

WORKDIR /go/src/github.com/bolandrm/gofc
RUN mkdir -p /go/src/github.com/bolandrm/gofc
