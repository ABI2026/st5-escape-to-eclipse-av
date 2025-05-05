cmake_minimum_required(VERSION 3.10)
project(Escape-To-Eclipse)

set(CMAKE_CXX_STANDARD 20)

set(LOCAL_SOURCES_PATH ${CMAKE_SOURCE_DIR}/src)
set(LOCAL_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)
set(LIB_PATH ${CMAKE_SOURCE_DIR}/lib)
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(-w)

# Remotely include SFML LIB
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x    
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_subdirectory(${LIB_PATH})

# Get all local files recursively
file(GLOB_RECURSE SRC_FILES ${LOCAL_SOURCES_PATH}/*.cpp)
file(GLOB_RECURSE HEADERS ${LOCAL_INCLUDE_PATH}/*.hpp)

# Init executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Includes and Links / Dependencies
target_include_directories(${PROJECT_NAME} PRIVATE ${LOCAL_INCLUDE_PATH})

link_directories(${SFML_LIBRARY_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SFML_GAME_LIB
    sfml-system 
    sfml-window 
    sfml-graphics
)