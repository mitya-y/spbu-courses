cmake_minimum_required(VERSION 3.10)
project(roguelike)
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

set_property(TARGET roguelike PROPERTY CXX_STANDARD 23)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE model)
add_subdirectory(model)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE application)
add_subdirectory(application)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE scene)
add_subdirectory(scene)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE .)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE GLEW::GLEW OpenGL::GL)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE ASSETS_DIRECTORY="${CMAKE_SOURCE_DIR}/datasets")
