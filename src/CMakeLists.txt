set(CMAKE_PREFIX_PATH "D:/Qt/Qt5.14.2/5.14.2/mingw73_64")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#添加测试
add_subdirectory(test)

#找Qt组件
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)
#生成ui头文件
set(CMAKE_AUTOUIC ON)
#元编程
set(CMAKE_AUTOMOC ON)
#生成qrc头文件
#set(CMAKE_AUTORCC ON)
qt5_add_resources(RESOURCES res.qrc)

#找OpenCv库
set(OpenCV_DIR "d:/OpenCv/opencv/opencv_build/install/x64/mingw/lib")
find_package(OpenCV REQUIRED)

#添加源文件
aux_source_directory(. SRCS)
aux_source_directory(./fun SRCS)
aux_source_directory(./interface SRCS)

#配置选项
option(FUN 
    "Whether to use a third-party library"
    ON
)
option(DEBUG
    "Whether to output related information"
    ON
)

#生成配置文件
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Config.h)

#生成库
add_library(${LIB_NAME}
    ${SRCS}
    ${RESOURCES}
)
#头文件
set(LIB_INCLUDE "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}_autogen/include")
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})
target_include_directories(${LIB_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fun)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/interface)
#连接第三库
target_link_libraries(${LIB_NAME} PUBLIC Qt5::Widgets Qt5::Core Qt5::Gui)
target_link_libraries(${LIB_NAME} PUBLIC ${OpenCV_LIBS})