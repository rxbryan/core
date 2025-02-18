# Check if port is enabled
if(NOT OPTION_BUILD_PORTS OR NOT OPTION_BUILD_PORTS_JAVA)
	return()
endif()

#
# External dependencies
#

find_package(Java)

if(NOT JAVA_FOUND)
	message(STATUS "Java libraries not found")
	return()
endif()

find_package(JNI)

if(NOT JNI_FOUND)
	message(STATUS "JNI libraries not found")
	return()
endif()

include(UseJava)

find_package(Maven)

if(NOT MAVEN_FOUND)
	message(STATUS "Maven not found")
	return()
endif()

#
# Port name and options
#

# Target name
set(target java_port)

# Exit here if required dependencies are not met
message(STATUS "Port ${target}")

# TODO:
# https://cmake.org/cmake/help/latest/module/UseJava.html
# https://searchcode.com/codesearch/view/7927641/
# https://github.com/Kurento/kms-core/blob/master/CMake/FindMaven.cmake

# # Set API export file and macro
# string(TOUPPER ${target} target_upper)
# set(export_file  "include/${target}/${target}_api.h")
# set(export_macro "${target_upper}_API")

# #
# # Sources
# #

# set(interface_path "${CMAKE_CURRENT_SOURCE_DIR}/interface/${target}")
# set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
# set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

# set(interfaces
# 	${interface_path}/java_port.i
# )

# set(headers
# 	${include_path}/java_port.h
# )

# set(sources
# 	${source_path}/java_port.c
# )

# # Group source files
# set(interface_group "Interface Files (SWIG)")
# set(header_group "Header Files (API)")
# set(source_group "Source Files")
# source_group_by_path(${interface_path} "\\\\.i$"
# 	${interface_group} ${interfaces})
# source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$"
# 	${header_group} ${headers})
# source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$"
# 	${source_group} ${sources})

# #
# # SWIG Configuration
# #

# # Set SWIG flags
# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# 	list(APPEND CMAKE_SWIG_FLAGS "-DDEBUG")
# else()
# 	list(APPEND CMAKE_SWIG_FLAGS "-DNDEBUG")
# endif()

# # Set SWIG include path
# include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
# include_directories("${CMAKE_CURRENT_SOURCE_DIR}/interface")

# #
# # Create library
# #

# foreach(file ${interfaces} ${headers} ${sources})
# 	set_source_files_properties(
# 		${file}
# 		PROPERTY SWIG_FLAGS "-java" "-includeall"
# 	)

# 	set_source_files_properties(
# 		${file}
# 		PROPERTIES CPLUSPLUS OFF
# 	)
# endforeach()

# if(${CMAKE_VERSION} VERSION_LESS "3.8.0")
# 	swig_add_module(${target}
# 		java
# 		${interfaces}
# 		${headers}
# 		${sources}
# 	)
# else()
# 	swig_add_library(${target}
# 		LANGUAGE java
# 		SOURCES ${interfaces} ${headers} ${sources}
# 	)
# endif()

# #
# # Dependecies
# #

# add_dependencies(${SWIG_MODULE_${target}_REAL_NAME}
# 	${META_PROJECT_NAME}::metacall
# )

# # Create namespaced alias
# add_library(${META_PROJECT_NAME}::${target} ALIAS ${SWIG_MODULE_${target}_REAL_NAME})

# # Export library for downstream projects
# export(TARGETS ${SWIG_MODULE_${target}_REAL_NAME} NAMESPACE ${META_PROJECT_NAME}:: FILE ${PROJECT_BINARY_DIR}/cmake/${target}/${target}-export.cmake)

# # Create API export header
# generate_export_header(${SWIG_MODULE_${target}_REAL_NAME}
# 	EXPORT_FILE_NAME  ${export_file}
# 	EXPORT_MACRO_NAME ${export_macro}
# )

# #
# # Project options
# #

# set_target_properties(${SWIG_MODULE_${target}_REAL_NAME}
# 	PROPERTIES
# 	${DEFAULT_PROJECT_OPTIONS}
# 	FOLDER "${IDE_FOLDER}"
# )

# #
# # Include directories
# #
# target_include_directories(${SWIG_MODULE_${target}_REAL_NAME}
# 	PRIVATE
# 	${PROJECT_BINARY_DIR}/source/include
# 	${CMAKE_CURRENT_SOURCE_DIR}/include
# 	${CMAKE_CURRENT_BINARY_DIR}/include

# 	$<TARGET_PROPERTY:${META_PROJECT_NAME}::metacall,INCLUDE_DIRECTORIES> # MetaCall includes
# 	${JAVA_INCLUDE_DIRS} # Java includes
# 	${JNI_INCLUDE_DIRS} # JNI includes

# 	PUBLIC
# 	${DEFAULT_INCLUDE_DIRECTORIES}

# 	INTERFACE
# 	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
# 	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
# 	$<INSTALL_INTERFACE:include>
# )

# #
# # Libraries
# #

# swig_link_libraries(${target}
# 	PRIVATE
# 	${JAVA_LIBRARY} # Java libraries
# 	${JNI_LIBRARIES} # JNI libraries

# 	${META_PROJECT_NAME}::metacall

# 	PUBLIC
# 	${DEFAULT_LIBRARIES}

# 	INTERFACE
# )

# #
# # Compile definitions
# #

# target_compile_definitions(${SWIG_MODULE_${target}_REAL_NAME}
# 	PRIVATE

# 	PUBLIC
# 	$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${target_upper}_STATIC_DEFINE>
# 	${DEFAULT_COMPILE_DEFINITIONS}

# 	INTERFACE
# )

# #
# # Compile options
# #

# target_compile_options(${SWIG_MODULE_${target}_REAL_NAME}
# 	PRIVATE

# 	PUBLIC
# 	${DEFAULT_COMPILE_OPTIONS}

# 	INTERFACE
# )

# #
# # Linker options
# #

# target_link_libraries(${SWIG_MODULE_${target}_REAL_NAME}
# 	PRIVATE
# 	${META_PROJECT_NAME}::metacall

# 	PUBLIC
# 	${DEFAULT_LINKER_OPTIONS}

# 	INTERFACE
# )

# #
# # Deployment
# #

# # Library
# install(TARGETS ${SWIG_MODULE_${target}_REAL_NAME}
# 	EXPORT  "${target}-export"			COMPONENT dev
# 	RUNTIME DESTINATION ${INSTALL_BIN}	COMPONENT runtime
# 	LIBRARY DESTINATION ${INSTALL_SHARED} COMPONENT runtime
# 	ARCHIVE DESTINATION ${INSTALL_LIB}	COMPONENT dev
# )

# # Header files
# install(DIRECTORY
# 	${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
# 	COMPONENT dev
# )

# # Generated header files
# install(DIRECTORY
# 	${CMAKE_CURRENT_BINARY_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
# 	COMPONENT dev
# )

# # CMake config
# install(EXPORT ${target}-export
# 	NAMESPACE   ${META_PROJECT_NAME}::
# 	DESTINATION ${INSTALL_CMAKE}/${target}
# 	COMPONENT   dev
# )

# #
# # Configure test
# #

# set(java_port_test "${target}_test")
# set(java_port_test_path "${PROJECT_OUTPUT_DIR}/${java_port_test}.java")

# # Require module name
# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# 	get_target_property(DEBUG_POSTFIX ${SWIG_MODULE_${target}_REAL_NAME} "DEBUG_POSTFIX")
# 	set(JAVA_PORT_NAME "${SWIG_MODULE_${target}_REAL_NAME}${DEBUG_POSTFIX}")
# else()
# 	set(JAVA_PORT_NAME "${SWIG_MODULE_${target}_REAL_NAME}")
# endif()

# configure_file(test/run.java.in ${java_port_test_path})

# #
# # Define test
# #

# add_test(NAME ${target}
# 	COMMAND ${JAVA_EXECUTABLE} ${java_port_test_path}
# )

# #
# # Define test labels
# #

# set_property(TEST ${target}
# 	PROPERTY LABELS ${java_port_test}
# )

# include(TestEnvironmentVariables)

# test_environment_variables(${target}
# 	""
# 	${TESTS_ENVIRONMENT_VARIABLES}
# )
