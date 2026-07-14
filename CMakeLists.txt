cmake_minimum_required(VERSION 3.15)
project(vulkan_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(${PROJECT_NAME} src/main.cpp src/windows_layer/windows_manager.h src/windows_layer/windows_manager.cpp  )

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    glfw
    Vulkan::Vulkan
)

