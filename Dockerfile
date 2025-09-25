FROM ubuntu:22.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \ 
    && apt-get -y install --no-install-recommends \
    libqt5opengl5-dev \
    qtbase5-dev \
    build-essential \
    freeglut3-dev \
    protobuf-compiler \
    libprotobuf-dev \
    cmake

COPY . /opt/vssreferee

WORKDIR /opt/vssreferee/build

RUN cmake .. && make -j4

WORKDIR /opt/vssreferee/bin

CMD ["./VSSReferee","--3v3","--record","false"]