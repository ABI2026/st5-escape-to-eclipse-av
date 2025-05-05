cmake_minimum_required(VERSION 3.10)
project(SFML_GAME_LIB)

set(INCLUDE_PATH_ ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_FILES_ ${CMAKE_CURRENT_SOURCE_DIR}/src)

# collect all lib files
file(GLOB_RECURSE LIB_HEADERS ${INCLUDE_PATH_}/*.hpp)
file(GLOB_RECURSE LIB_SOURCES ${SRC_FILES_}/*.cpp)

add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES} ${LIB_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH_})
target_link_libraries(${PROJECT_NAME} PUBLIC 
    sfml-system 
    sfml-window 
    sfml-graphics
)
