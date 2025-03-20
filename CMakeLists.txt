cmake_minimum_required(VERSION 3.10)
project(Escape-To-Eclipse)

set(CMAKE_CXX_STANDARD 20)

set(LOCAL_SOURCES_PATH ${CMAKE_SOURCE_DIR}/src)
set(LOCAL_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)
set(LIB_PATH ${CMAKE_SOURCE_DIR}/lib)

# Get all local files recursively
file(GLOB_RECURSE SRC_FILES ${LOCAL_SOURCES_PATH}/*.cpp)
file(GLOB_RECURSE HEADERS ${LOCAL_INCLUDE_PATH}/*.hpp)

# Init executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

#-
add_subdirectory(${LIB_PATH})

target_include_directories(${PROJECT_NAME} PRIVATE ${LOCAL_INCLUDE_PATH})
target_link_libraries(${PROJECT_NAME} PUBLIC SFML_GAME_LIB)