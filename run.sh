#!/bin/bash

# 安装依赖 (Ubuntu/Debian)
install_deps() {
    sudo apt-get update
    sudo apt-get install -y cmake build-essential libbenchmark-dev
}

# 编译项目
build() {
    mkdir -p build
    cd build
    cmake ..
    make -j$(nproc)
    cd ..
}

# 运行基准测试
run_bench() {
    echo "=== 运行指令延迟测试 ==="
    ./build/benchmark_latency "$@"
}

# 主函数
case "${1:-build}" in
    install)
        install_deps
        ;;
    build)
        build
        ;;
    run)
        shift
        run_bench "$@"
        ;;
    *)
        echo "用法: $0 {install|build|run}"
        exit 1
        ;;
esac
