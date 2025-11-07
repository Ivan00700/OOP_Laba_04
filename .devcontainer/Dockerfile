# Используем Ubuntu 22.04
FROM ubuntu:22.04

# Обновляем и устанавливаем инструменты для C++ разработки
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    g++ \
    gcc \
    cmake \
    git \
    wget \
    curl \
    ninja-build \
    vim \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# Собираем GoogleTest
RUN cd /usr/src/gtest && \
    cmake CMakeLists.txt && \
    make && \
    cp *.a /usr/lib

# Устанавливаем рабочую директорию
WORKDIR /workspace
