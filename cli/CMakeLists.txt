cmake_minimum_required(VERSION 3.20)


set(CLI_NAME graphc)
set(CLI_VERSION ${PROJECT_VERSION})
set(CLI_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CLI_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CLI_VERSION_PATCH ${PROJECT_VERSION_PATCH})
string(TOUPPER ${CLI_NAME} CLI_NAME_UPPERCASE)

add_compile_definitions(
	${CLI_NAME_UPPERCASE}_NAME=${CLI_NAME}
	${CLI_NAME_UPPERCASE}_VERSION_MAJOR=${CLI_VERSION_MAJOR}
	${CLI_NAME_UPPERCASE}_VERSION_MINOR=${CLI_VERSION_MINOR}
	${CLI_NAME_UPPERCASE}_VERSION_PATCH=${CLI_VERSION_PATCH}
)

if (BUILD_STATIC)
	add_compile_definitions(${PROJECT_ACRONYM_UPPERCASE}_STATIC)
else()
	add_compile_definitions(${PROJECT_ACRONYM_UPPERCASE}_SHARED)
endif()

include_directories(
	./include,
	../lib/include
)

file(GLOB_RECURSE CLI_HEADER *.hpp)
file(GLOB_RECURSE CLI_INLINE *.inl)
file(GLOB_RECURSE CLI_SOURCE *.cpp)

add_executable(${CLI_NAME} ${CLI_HEADER} ${CLI_INLINE} ${CLI_SOURCE})
set_property(TARGET ${CLI_NAME} PROPERTY CXX_STANDARD ${PROJECT_CPP_DIALECT})

#target_link_directories(./lib)

target_link_libraries(
	${CLI_NAME} PRIVATE ${PROJECT_NAME}
)



if (WIN32)
	add_compile_definitions(${CLI_NAME_UPPERCASE}_WINDOWS)
	if (BUILD_STATIC)
	else()
		message("Copying dll")
		message("${PROJECT_BINARY_DIR}/lib/lib${PROJECT_NAME}.dll")
		message("${PROJECT_BINARY_DIR}/cli")
		add_custom_command(
			TARGET ${CLI_NAME}
			PRE_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${PROJECT_BINARY_DIR}/lib/lib${PROJECT_NAME}.dll"
			"${PROJECT_BINARY_DIR}/cli"
		)
	endif()
elseif (UNIX)
	add_compile_definitions(${CLI_NAME_UPPERCASE}_LINUX)
elseif (APPLE)
	add_compile_definitions(${CLI_NAME_UPPERCASE}_APPLE)
else()
	message(FATAL_ERROR "Platforms other than Windows, Linux and MacOS aren't supported for now")
endif()