add_executable(QCurve_test QCurve_test.cpp)
#头文件
target_include_directories(QCurve_test PRIVATE ${CMAKE_SOURCE_DIR}/interface)
#连接库
target_link_libraries(QCurve_test PRIVATE ${LIB_NAME})