FROM alpine:3.7 as builder
MAINTAINER Group2

RUN echo http://dl-4.alpinelinux.org/alpine/edge/main > /etc/apk/repositories && \
    echo http://dl-4.alpinelinux.org/alpine/edge/community >> /etc/apk/repositories && \
    echo http://dl-4.alpinelinux.org/alpine/edge/testing >> /etc/apk/repositories && \
    apk update && \
    apk --no-cache add \
        cmake \
        g++ \
        opencv \
        opencv-dev \
        make && \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted

ADD . /opt/sources
WORKDIR /opt/sources
RUN cd /opt/sources && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release .. && \
    make && cp LaneDetection /tmp 

# Deploy.
FROM alpine:3.7
MAINTAINER Group2

RUN echo http://dl-4.alpinelinux.org/alpine/edge/main > /etc/apk/repositories && \
    echo http://dl-4.alpinelinux.org/alpine/edge/community >> /etc/apk/repositories && \
    echo http://dl-4.alpinelinux.org/alpine/edge/testing >> /etc/apk/repositories && \
    apk update && \
    apk --no-cache add \
        opencv-libs \
        libcanberra-gtk3 && \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted && \
    mkdir /opt
WORKDIR /opt
COPY --from=builder /tmp/ .
CMD ["/opt/LaneDetection"]
