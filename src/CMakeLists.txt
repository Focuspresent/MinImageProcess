set(CMAKE_PREFIX_PATH "D:/Qt/Qt5.14.2/5.14.2/mingw73_64")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#生成ui头文件
set(CMAKE_AUTOUIC ON)
#元编程
set(CMAKE_AUTOMOC ON)
#生成qrc头文件
set(CMAKE_AUTORCC ON)

#找Qt组件
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)
#添加源文件
aux_source_directory(. SRCS)

#生成库
add_library(${LIB_NAME}
    ${SRCS}
)
#头文件
set(LIB_INCLUDE "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}_autogen/include")
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})
#连接第三库
target_link_libraries(${LIB_NAME} PUBLIC Qt5::Widgets Qt5::Core Qt5::Gui)