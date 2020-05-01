FROM python:3.6-stretch
MAINTAINER summergift

RUN mkdir /rt-thread
ADD ./build.py /etc/apt/
ADD ./eclipse /rt-thread/eclipse

RUN apt-get update \
    && apt-get -qq install gcc-multilib libsdl-dev scons \
    && apt-get --no-install-recommends --allow-unauthenticated --fix-broken -y install wget bzip2 make vim git ca-certificates scons sudo \
    && apt-get clean \
    && pip install pytest pytest-html

RUN cd /rt-thread \
    && wget -c https://developer.arm.com/-/media/Files/downloads/gnu-rm/5_4-2016q3/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2 \
    && tar jxf gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2 \
    && rm -rf gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2

RUN cd /rt-thread \
    && wget -c https://download.java.net/java/GA/jdk11/13/GPL/openjdk-11.0.1_linux-x64_bin.tar.gz \
    && tar xzvf openjdk-11.0.1_linux-x64_bin.tar.gz \
    && rm -rf openjdk-11.0.1_linux-x64_bin.tar.gz \
    && python /etc/apt/build.py





