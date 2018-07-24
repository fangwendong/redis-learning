cmake_minimum_required(VERSION 3.10)
project(redis_learning C)

set(CMAKE_C_STANDARD 99)

add_executable(gc zmalloc.c)