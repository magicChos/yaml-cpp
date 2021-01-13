cmake_minimum_required(VERSION 3.10)
project(yaml_test C CXX)

# 将制定目录下的所有文件添加到LIBSLTPLUS_HPP_FILESYSTEM
file(GLOB LIB_HPP "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB LIB_H "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB LIB_CPP "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# file(GLOB LIB_HPP "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" )
# file(GLOB LIB_CPP "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )


# 将新元素添加到LIBSLTPLUS_SRCS中
# list(APPEND LIBSLTPLUS_SRCS
#   ${LIB_HPP} ${LIB_CPP})

list(APPEND LIB_SRCS ${LIB_HPP} ${LIB_H} ${LIB_CPP})

find_package( Open3D REQUIRED)
if (NOT Open3D_FOUND)
    message(FATAL_ERROR "Open3D Not Found!")
endif (NOT Open3D_FOUND)



include_directories(${Open3D_INCLUDE_DIRS} ${YAML_CPP_INCLUDE_DIR} /usr/local/include /usr/local/include/open3d/3rdparty )
link_directories(${Open3D_LIBRARY_DIRS})

message(${LIB_SRCS})

# 将指定的源文件生成库
add_library(utily ${LIB_SRCS})

find_package(yaml-cpp REQUIRED)
# set(YAML_CPP_LIBRARIES /usr/local/lib/libyaml-cpp.a)

set(YAML_CPP_LIBRARIES  yaml-cpp)

find_package(OpenCV 3  REQUIRED)
include_directories( /usr/local/include ${OpenCV_INCLUDE_DIRS} include)

# add_executable(yaml_test main.cpp)
# add_executable(read_calibration read_calibration.cpp)
# add_executable( generateCarLine generateCarLine.cpp ${LIBSLTPLUS_SRCS})

add_executable(write_yaml write_yaml.cpp )
add_executable(read_yaml read_yaml.cpp ${LIB_SRCS})
add_executable(read_yaml_cv test_read_cv_yaml.cpp ${LIB_SRCS})

# target_link_libraries(yaml_test PUBLIC ${YAML_CPP_LIBRARIES})
# target_link_libraries(read_calibration PUBLIC ${YAML_CPP_LIBRARIES} ${OpenCV_LIBS})
# target_link_libraries(generateCarLine PUBLIC ${YAML_CPP_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries(write_yaml PUBLIC ${YAML_CPP_LIBRARIES} ${OpenCV_LIBS} utily )
target_link_libraries(read_yaml PUBLIC ${YAML_CPP_LIBRARIES} ${OpenCV_LIBS} ${Open3D_LIBRARIES})
target_link_libraries(read_yaml_cv PUBLIC  ${OpenCV_LIBS} ${YAML_CPP_LIBRARIES} ${OpenCV_LIBS} utily )

