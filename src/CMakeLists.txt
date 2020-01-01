cmake_minimum_required (VERSION 3.0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory (string)
add_subdirectory (system)

set (LIB_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (LIB_LOCATION ${CMAKE_BINARY_DIR}/lib/libUtility.a)

file (MAKE_DIRECTORY ${LIB_DIRECTORY})
add_custom_target(libs
        COMMAND ar -x $<TARGET_FILE:String>
        COMMAND ar -x $<TARGET_FILE:System>
        COMMAND ar -qcs ${LIB_LOCATION} *.o
        WORKING_DIRECTORY ${LIB_DIRECTORY}
        DEPENDS String System)
add_library (Utility STATIC IMPORTED GLOBAL)
add_dependencies (Utility libs)
set_target_properties(Utility PROPERTIES IMPORTED_LOCATION ${LIB_LOCATION})

if (Test)
    find_package(GTest REQUIRED)
    add_subdirectory (unit_test)
endif (Test)