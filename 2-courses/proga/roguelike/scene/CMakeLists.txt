target_sources(${CMAKE_PROJECT_NAME} PUBLIC scene/player.cpp)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC scene/scene.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE things)
add_subdirectory(things)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE inventory)
add_subdirectory(inventory)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE units)
add_subdirectory(units)
