FROM nvcr.io/nvidia/l4t-jetpack:r36.2.0

ARG USER_ID=1000
ARG GROUP_ID=1000

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    curl \
    git \
    pkg-config \
    libv4l-dev \
    v4l-utils \
    libssl-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

RUN curl https://sh.rustup.rs -sSf | sh -s -- -y --default-toolchain stable
ENV PATH="/root/.cargo/bin:${PATH}"

RUN git clone https://github.com/eclipse-iceoryx/iceoryx2.git /opt/iceoryx2 --depth=1 && \
    cd /opt/iceoryx2 && \
    cmake -S . -B build \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr/local \
        -Diox2_BUILD_EXAMPLES=OFF \
        -Diox2_BUILD_TESTS=OFF && \
    cmake --build build --parallel $(nproc) && \
    cmake --install build && \
    rm -rf /opt/iceoryx2

RUN groupadd -g ${GROUP_ID} appuser && \
    useradd -u ${USER_ID} -g ${GROUP_ID} -m -s /bin/bash appuser && \
    usermod -aG video appuser

WORKDIR /app
USER appuser
