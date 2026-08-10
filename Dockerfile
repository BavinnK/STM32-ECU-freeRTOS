FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        gcc-arm-none-eabi \
        binutils-arm-none-eabi \
        libnewlib-arm-none-eabi \
        make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["sh", "-lc", "make -C Debug clean && make -C Debug all -j"]
