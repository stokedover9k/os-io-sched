cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR iosched)
project(${PROJECT_NAME_STR} C CXX)

if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++0x)
endif()

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++0x")

if(MSVC)
#vc 2012 fix for vararg templates
    set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif() 
#-------------------
# set common include folder for module
#-------------------
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

#-------------------
# Module source
#-------------------
set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}_impl)

include_directories(${COMMON_INCLUDES})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_LIB_NAME} ${SRC_FILES})

add_subdirectory(${EXT_PROJECTS_DIR}/gtest)

#-------------------
# Main App
#-------------------
set(PROJECT_APP_NAME ${PROJECT_NAME_STR})
include_directories(${COMMON_INCLUDES})
file(GLOB APP_SRC_FILES ${PROJECT_SOURCE_DIR}/app/*.cpp)

add_executable(${PROJECT_APP_NAME} ${APP_SRC_FILES})
add_dependencies(${PROJECT_APP_NAME} ${PROJECT_LIB_NAME})
target_link_libraries(${PROJECT_APP_NAME} ${PROJECT_LIB_NAME})

#-------------------
# Test
#-------------------
add_definitions(${MSVC_COMPILER_DEFS})
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
add_dependencies(${PROJECT_TEST_NAME} ${PROJECT_LIB_NAME} googletest)
target_link_libraries(${PROJECT_TEST_NAME} ${PROJECT_LIB_NAME})

if(CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(${PROJECT_TEST_NAME} pthread)
	target_link_libraries(${PROJECT_TEST_NAME}
		${GTEST_LIBS_DIR}/libgtest.a
		${GTEST_LIBS_DIR}/libgtest_main.a
	)
else()

	target_link_libraries(${PROJECT_TEST_NAME}
	       debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
	target_link_libraries(${PROJECT_TEST_NAME}
	       debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
endif()

add_test(test1 ${PROJECT_TEST_NAME})
