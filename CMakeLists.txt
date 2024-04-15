cmake_minimum_required(VERSION 3.5)

project(
  RaylibRPG
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_C_STANDARD 11)

# Linking raylib
add_subdirectory(libs/raylib)

# Make it work with clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Raylib options
set(SUPPORT_FILEFORMAT_JPG ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} raylib)

if(APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# Copy the assets folder to the build directory or link if it's not release
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
else()
  if(WIN32)
    file(CREATE_LINK ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
         SYMBOLIC)
  else()
    add_custom_target(
      copy_assets COMMAND ${CMAKE_COMMAND} -E create_symlink
                          ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)
    add_dependencies(${PROJECT_NAME} copy_assets)
  endif()
endif()
