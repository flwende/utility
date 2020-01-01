cmake_minimum_required (VERSION 3.0)

file (GLOB Sources "*.cpp")
add_library (System STATIC ${Sources})
