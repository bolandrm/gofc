FROM debian:stretch

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
wget \
xz-utils \
runit

# The cross-compiling emulator
RUN apt-get update \
&& apt-get install -y \
  qemu-user \
  qemu-user-static \
&& apt-get clean --yes

RUN dpkg --add-architecture i386
RUN apt-get -y install lib32z1


RUN wget http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.23.0.tar.xz
RUN tar -xJf crosstool-ng-1.23.0.tar.xz

run apt-get install -y \
  gperf \
  bison \
  flex \
  texinfo \
  bzip2

run apt-get install -y help2man libncurses-dev

RUN cd crosstool-ng-1.23.0 && \
  ./configure --prefix=/ct-ng && \
  make && \
  make install

ENV PATH "$PATH:/ct-ng/bin"

COPY crosstool-ng.config .config

RUN mkdir -p /root/src

RUN apt-get install -y bsdtar g++-multilib
RUN ln -sf $(which bsdtar) $(which tar)

RUN ct-ng build


# The CROSS_TRIPLE is a configured alias of the "aarch64-unknown-linux-gnueabi" target.
#ENV CROSS_TRIPLE armv7-unknown-linux-gnueabi
#ENV CROSS_ROOT ${XCC_PREFIX}/${CROSS_TRIPLE}

ENV CROSS_TRIPLE armv7-unknown-linux-gnueabi
ENV CROSS_ROOT /root/x-tools/${CROSS_TRIPLE}

ENV AS=${CROSS_ROOT}/bin/${CROSS_TRIPLE}-as \
    AR=${CROSS_ROOT}/bin/${CROSS_TRIPLE}-ar \
    CC=${CROSS_ROOT}/bin/${CROSS_TRIPLE}-gcc \
    CPP=${CROSS_ROOT}/bin/${CROSS_TRIPLE}-cpp \
    CXX=${CROSS_ROOT}/bin/${CROSS_TRIPLE}-g++ \
    LD=${CROSS_ROOT}/bin/${CROSS_TRIPLE}-ld \
    FC=${CROSS_ROOT}/bin/${CROSS_TRIPLE}-gfortran


#ENV QEMU_LD_PREFIX "${CROSS_ROOT}/${CROSS_TRIPLE}/sysroot"
#ENV QEMU_SET_ENV "LD_LIBRARY_PATH=${CROSS_ROOT}/lib:${QEMU_LD_PREFIX}"
#
#ENV DEFAULT_DOCKCROSS_IMAGE gofc-builder
#
#COPY Toolchain.cmake ${CROSS_ROOT}/
#ENV CMAKE_TOOLCHAIN_FILE ${CROSS_ROOT}/Toolchain.cmake
#
#ENV PKG_CONFIG_PATH /usr/lib/arm-linux-gnueabihf/


RUN curl -O https://storage.googleapis.com/golang/go1.11.5.linux-amd64.tar.gz
RUN tar -C /usr/local -xzf go1.11.5.linux-amd64.tar.gz

RUN wget "http://software-dl.ti.com/codegen/esd/cgt_public_sw/PRU/2.3.1/ti_cgt_pru_2.3.1_linux_installer_x86.bin"

RUN chmod +x ti_cgt_pru_2.3.1_linux_installer_x86.bin
RUN ./ti_cgt_pru_2.3.1_linux_installer_x86.bin

ENV PRU_CGT /ti-cgt-pru_2.3.1

ENV PATH "$PATH:/usr/local/go/bin"
ENV GOPATH /go
ENV GOOS linux
ENV GOARCH arm
ENV GOARM 7
ENV CGO_ENABLED 1

#COPY vendor/include /usr/include/
#COPY vendor/lib /usr/lib/

WORKDIR /go/src/github.com/bolandrm/gofc
RUN mkdir -p /go/src/github.com/bolandrm/gofc
