cmake_minimum_required(VERSION 2.8.3)
project(custom_conversions)

## Add support for C++11, supported in ROS Kinetic and newer
# add_definitions(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
		roscpp
		rospy
		geometry_msgs
		tf_conversions
		)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need


catkin_package(
        INCLUDE_DIRS include/
        #  LIBRARIES custom_conversions
        LIBRARIES ${PROJECT_NAME}
        #  CATKIN_DEPENDS other_catkin_pkg
        CATKIN_DEPENDS geometry_msgs tf_conversions

)

include_directories(
		include/
		${catkin_INCLUDE_DIRS}
)

add_library(custom_conversions
		src/Conversions.cpp
		)

target_link_libraries(custom_conversions
		${catkin_LIBRARIES}
		${OpenCV_LIBRARIES}
		)


#i n catkin, libraries are installed in a lib/ directory shared by all the packages in that entire ROS distribution.
install(TARGETS custom_conversions
		ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
		LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
		RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

install(DIRECTORY include/${PROJECT_NAME}/
		DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
		FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
		)
