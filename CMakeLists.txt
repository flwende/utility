cmake_minimum_required (VERSION 3.0)
project (utility)
 
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

include_directories (include)

add_subdirectory (src)

file(WRITE ${CMAKE_BINARY_DIR}/Empty.cpp "int main() { return 0; }")
add_executable (Empty ${CMAKE_BINARY_DIR}/Empty.cpp)
target_link_libraries (Empty LINK_PUBLIC "Utility")
