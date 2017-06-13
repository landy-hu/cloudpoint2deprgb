cmake_minimum_required(VERSION 2.8)
find_package(PCL REQUIRED COMPONENTS common io)
find_package(OpenCV REQUIRED)
#find_package(OpenNI REQUIRED)

ADD_DEFINITIONS( ${PCL_DEFINITIONS} )
INCLUDE_DIRECTORIES( ${PCL_INCLUDE_DIRS}  )
LINK_LIBRARIES( ${PCL_LIBRARY_DIRS} )

#include_directories(${OPENNI_INCLUDE_DIRS})
#target_link_libraries((${OPENNI_LIBRARY_DIRS})


add_executable(point2rgb src/point2rgb.cpp)
target_link_libraries(point2rgb ${OpenCV_LIBS} ${PCL_LIBRARIES})
