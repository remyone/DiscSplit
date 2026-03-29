cmake_minimum_required(VERSION 4.2.0)

project(DiscSplit VERSION 1.1 LANGUAGES C)

message(STATUS "Project Version: ${PROJECT_VERSION}")
message(STATUS "Source directory: ${CMAKE_SOURCE_DIR}")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(LibrarySources
    src/mergeFiles.c
    src/splitFileContent.c
    src/fileAnalysis.c
)

set(LibraryHeaders
    include/mergeFiles.h
    include/splitFileContent.h
    include/fileAnalysis.h 
)

add_library(LIB_DiscSplit STATIC ${LibrarySources} ${LibraryHeaders})
target_include_directories(LIB_DiscSplit PRIVATE include)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE LIB_DiscSplit)
target_include_directories(${PROJECT_NAME} PRIVATE include)
