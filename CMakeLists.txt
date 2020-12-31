cmake_minimum_required(VERSION 3.10)
project(yaml_test C CXX)

# 将制定目录下的所有文件添加到LIBSLTPLUS_HPP_FILESYSTEM
file(GLOB LIB_HPP "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" )
file(GLOB LIB_CPP "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )

# 将新元素添加到LIBSLTPLUS_SRCS中
# list(APPEND LIBSLTPLUS_SRCS
#   ${LIB_HPP} ${LIB_CPP})


# message(${LIBSLTPLUS_SRCS})

# 将指定的源文件生成库
# add_library(stlplus ${LIBSLTPLUS_SRCS})

find_package(yaml-cpp REQUIRED)
# set(YAML_CPP_LIBRARIES /usr/local/lib/libyaml-cpp.a)

set(YAML_CPP_LIBRARIES  yaml-cpp)

find_package(OpenCV REQUIRED)
include_directories( /usr/local/include ${OpenCV_INCLUDE_DIRS} )

add_executable(yaml_test main.cpp)
add_executable(read_calibration read_calibration.cpp)
add_executable( generateCarLine generateCarLine.cpp param_handler.cpp)

add_executable(write_yaml write_yaml.cpp )

target_link_libraries(yaml_test PUBLIC ${YAML_CPP_LIBRARIES})
target_link_libraries(read_calibration PUBLIC ${YAML_CPP_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries(generateCarLine PUBLIC ${YAML_CPP_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries(write_yaml PUBLIC ${YAML_CPP_LIBRARIES})


