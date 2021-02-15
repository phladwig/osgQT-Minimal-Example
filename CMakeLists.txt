# top level cmake file

cmake_minimum_required (VERSION 3.0 FATAL_ERROR)
project (CMakeOSGQtHelloWorld)

include_directories("${CMAKE_SOURCE_DIR}/src")

# First for the generic no-config case (e.g. with mingw)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set(CMAKE_DEBUG_POSTFIX "d")
# CMake Modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

function(getsTheDepsNameFromURL "${URL}")
	string(FIND "${URL}" / FILENAME_STRING_POS REVERSE) # searches for the last / and returns the position in the string
	math(EXPR FILENAME_STRING_POS "${FILENAME_STRING_POS} + 1") # increments the string position since it would otherwise contain the /
	string(LENGTH "${URL}" FILENAME_STRING_LENGTH) # get the length of the whole string
	math(EXPR LENGTH_OF_DEPS_NAME "${FILENAME_STRING_LENGTH} - ${FILENAME_STRING_POS} - 4") # calculates the length of the deps name 
	string(SUBSTRING "${URL}" "${FILENAME_STRING_POS}" "${LENGTH_OF_DEPS_NAME}" DEPS_NAME) # gets the file name as string
	#message(STATUS "LENGTH_OF_DEPS_NAME ist ${LENGTH_OF_DEPS_NAME}")
	#message(STATUS "CURRENT_DEPS_PATH ist ${URL}")
	#message(STATUS "FILENAME_STRING_POS ist ${FILENAME_STRING_POS}")
	#message(STATUS "FILENAME_STRING_LENGTH ist ${FILENAME_STRING_LENGTH}")
	#message(STATUS "AUSGABE ist ${DEPS_NAME}")
	set(DEPS_NAME "${DEPS_NAME}" PARENT_SCOPE) #set the DEPS_NAME for the upper scope from where the function was called with PARENT_SCOPE
endfunction(getsTheDepsNameFromURL)


# OSG (How-to-pack OSG below)
set( EXPECTED_SHA256 87efd7368c42f424d2a0993fa370b059685452a9bb326ad0720dd78281797ea9 )
set(CURRENT_DEPS_PATH ${CMAKE_BINARY_DIR}/../deps/osg-3650/)
set( URL https://claymore.mirevi.com/osg-3.6.5.zip)
getsTheDepsNameFromURL("${URL}")
set(CHECK_IF_DEPS_EXIST "${CURRENT_DEPS_PATH}/include/osg/Vec3")
FIND_PACKAGE( OSGForClayMore REQUIRED ) #There are OSG cmake modules shipped
file(COPY DIRECTORY ${CURRENT_DEPS_PATH}/bin
        DESTINATION ${CMAKE_BINARY_DIR}
        FILES_MATCHING PATTERN *.dll )
		
#QT5ForMireviMotionHub -> downloads dependency from web
cmake_policy(SET CMP0020 NEW) #supresses CMake Warnings to CMP2020
set(EXPECTED_SHA256 3e6ca0d8a030cbffd2e2896c478730b0b45468f6294e1c46c8023d6e5cd066cc )
set(CURRENT_DEPS_PATH ${CMAKE_BINARY_DIR}/../deps/qt-5.15.2/)
set(URL http://claymore.mirevi.com/qt-5.15.2.zip)
getsTheDepsNameFromURL("${URL}")
set(CHECK_IF_DEPS_EXIST "${CURRENT_DEPS_PATH}/include/QtCore/5.15.2/QtCore/private/qcoreapplication_p.h")
FIND_PACKAGE( Qt5ForMireviMotionHub REQUIRED )
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Widgetsd.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Widgets.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Guid.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Gui.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Cored.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Core.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5OpenGL.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5OpenGLd.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/platforms)
file(COPY ${CURRENT_DEPS_PATH}/plugins/platforms/qwindows.dll DESTINATION ${CMAKE_BINARY_DIR}/bin/platforms)
file(COPY ${CURRENT_DEPS_PATH}/plugins/platforms/qwindowsd.dll DESTINATION ${CMAKE_BINARY_DIR}/bin/platforms)


file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Widgetsd.pdb DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Widgets.pdb DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Guid.pdb DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Gui.pdb DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Cored.pdb DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5Core.pdb DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5OpenGL.pdb DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/bin/Qt5OpenGLd.pdb DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CURRENT_DEPS_PATH}/plugins/platforms/qwindows.pdb DESTINATION ${CMAKE_BINARY_DIR}/bin/platforms)
file(COPY ${CURRENT_DEPS_PATH}/plugins/platforms/qwindowsd.pdb DESTINATION ${CMAKE_BINARY_DIR}/bin/platforms)




# Add subdir with additional CMakeLists.txt and files
add_subdirectory("${CMAKE_SOURCE_DIR}/src") # CMake look for further CMakeLists.txt in that directory
