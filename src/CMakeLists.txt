#   CmakeLists for CMakeOSGHelloWorld

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instructs Cmake/VisualS Studio to add a extra folder for the moc files
#set(AUTOGEN_TARGETS_FOLDER ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


include_directories(${CMAKE_BINARY_DIR}/src ${OSG_INCLUDE_DIR} ${Qt5ForMireviMotionHub_INCLUDE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib "${CMAKE_BINARY_DIR}/lib" ${OSG_LIBRARIES_DIR} ${Qt5ForMireviMotionHub_LIBRARIES_DIR})
file(GLOB_RECURSE OSGHELLOWORLD_HEADER "${CMAKE_CURRENT_SRC_DIR}" *.h)
file(GLOB_RECURSE OSGHELLOWORLD_SRC "${CMAKE_CURRENT_SRC_DIR}" *.cpp)
add_executable(CMakeOSGHelloWorld ${OSGHELLOWORLD_HEADER} ${OSGHELLOWORLD_SRC})

set(CMAKE_DEBUG_POSTFIX "d")

target_link_libraries(CMakeOSGHelloWorld
	Qt5::Widgets
	Qt5::OpenGL
    debug osg${CMAKE_DEBUG_POSTFIX} optimized osg
    debug osgDB${CMAKE_DEBUG_POSTFIX} optimized osgDB
    debug osgGA${CMAKE_DEBUG_POSTFIX} optimized osgGA
    debug osgUtil${CMAKE_DEBUG_POSTFIX} optimized osgUtil
    debug osgViewer${CMAKE_DEBUG_POSTFIX} optimized osgViewer
    debug OpenThreads${CMAKE_DEBUG_POSTFIX} optimized OpenThreads
	
	debug osgText${CMAKE_DEBUG_POSTFIX} optimized osgText
	debug osgQOpenGL${CMAKE_DEBUG_POSTFIX} optimized osgQOpenGL
	debug osgQt5${CMAKE_DEBUG_POSTFIX} optimized osgQt5
)