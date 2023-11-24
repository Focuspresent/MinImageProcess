add_executable(${PROJECT_NAME} mip.cpp)
#头文件
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
#连接库
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})