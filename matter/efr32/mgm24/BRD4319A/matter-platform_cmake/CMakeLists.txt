# Define minimal required version of CMake.
cmake_minimum_required(VERSION "3.25")

# Project definition
project(
	matter-platform
	VERSION 1.0
	LANGUAGES C CXX ASM
)

# Include the definition of the slc_matter-platform target,
# which contains the content of the SLC project
include(matter-platform.cmake)

add_executable(matter-platform
    # Add additional sources here
)

target_include_directories(matter-platform PUBLIC
    # Add additional include paths here
)

target_compile_definitions(matter-platform PUBLIC
    # Add additional macros here
)

target_compile_options(matter-platform PUBLIC
    # Set additional compiler flags here
)

target_link_options(matter-platform PUBLIC
    # Set additional linker flags here
)

# Link with the content defined in the SLC project
target_link_libraries(matter-platform PRIVATE
    slc_matter-platform
)

# Include managed project content if available
include(matter-platform_project.cmake OPTIONAL RESULT_VARIABLE managed_project)
if(managed_project)
    message(STATUS "Using managed project content from ${managed_project}")
endif()

# Force the gcc linker command
set_target_properties(matter-platform PROPERTIES LINKER_LANGUAGE C)

# Create .bin, .hex and .s37 artifacts after building the project
add_custom_command(TARGET matter-platform
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O srec "$<TARGET_FILE:matter-platform>" "$<TARGET_FILE_DIR:matter-platform>/$<TARGET_FILE_BASE_NAME:matter-platform>.s37"
    COMMAND ${CMAKE_OBJCOPY} -O ihex "$<TARGET_FILE:matter-platform>" "$<TARGET_FILE_DIR:matter-platform>/$<TARGET_FILE_BASE_NAME:matter-platform>.hex"
    COMMAND ${CMAKE_OBJCOPY} -O binary "$<TARGET_FILE:matter-platform>" "$<TARGET_FILE_DIR:matter-platform>/$<TARGET_FILE_BASE_NAME:matter-platform>.bin" 
)

# Run post-build pipeline to perform additional post-processing
if(post_build_command)
add_custom_command(TARGET matter-platform
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
    COMMAND ${post_build_command}
)
endif()