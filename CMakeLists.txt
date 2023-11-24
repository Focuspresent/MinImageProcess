cmake_minimum_required(VERSION 3.10)

project(MIP VERSION 1.0 LANGUAGES CXX C)

#设置库名字
set(LIB_NAME "MIPLib")

#添加子目录
add_subdirectory(src)
add_subdirectory(apps)