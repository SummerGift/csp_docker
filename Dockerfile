FROM python:3.6-slim-buster
MAINTAINER SummerGift

ADD config_env.py /etc/apt/
RUN ls /etc/apt/config_*

# 1. install some basic library
RUN apt-get update \
    && apt-get -qq install gcc-multilib libsdl-dev scons libc6 libc6-dev \
    && apt-get --no-install-recommends --allow-unauthenticated --fix-broken -y install lib32z1 wget bzip2 make vim git ca-certificates scons sudo \
    && apt-get clean \
    && pip install pytest pytest-html click\
    && rm -rf /var/lib/apt/lists/* \
    && ldd --version

# 2. install arm gcc tool chain
RUN mkdir /rt-thread

RUN cd /rt-thread \
    && wget -c https://developer.arm.com/-/media/Files/downloads/gnu-rm/5_4-2016q3/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2 \
    && tar jxf gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2 \
    && rm -rf gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2

# 3. add eclipse IDE
ADD ./eclipse /rt-thread/eclipse
RUN chmod a+x /rt-thread/eclipse/eclipse

# 4. config java environment
RUN cd /rt-thread \
    && wget -c https://download.java.net/java/GA/jdk11/13/GPL/openjdk-11.0.1_linux-x64_bin.tar.gz \
    && tar xzvf openjdk-11.0.1_linux-x64_bin.tar.gz \
    && rm -rf openjdk-11.0.1_linux-x64_bin.tar.gz \
    && python /etc/apt/config_env.py

