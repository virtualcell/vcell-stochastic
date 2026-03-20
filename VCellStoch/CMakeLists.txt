cmake_minimum_required(VERSION 3.10)
project(VCellStoch)

# Source files for the library
set(LIB_SRC_FILES
    src/Gibson.cpp
    src/IndexedTree.cpp
    src/Jump.cpp
    src/StochModel.cpp
    src/StochVar.cpp
    src/MultiTrialStats.cpp
)

# Header files
set(HEADER_FILES
    include/Gibson.h
    include/IndexedTree.h
    include/Jump.h
    include/StochModel.h
    include/StochVar.h
    include/MultiTrialStats.h
)

# Main executable source
set(SRC_MAIN_FILE src/VCellStoch.cpp)

# Build static library
add_library(VCellStochLib STATIC ${LIB_SRC_FILES} ${HEADER_FILES})

# Include directories for the library
target_include_directories(VCellStochLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Link dependencies
target_link_libraries(VCellStochLib
    ExpressionParser
    vcommons
    vcellmessaging
    ${HDF5_LIBRARIES}
)

# Build standalone executable
add_executable(VCellStoch ${SRC_MAIN_FILE})
target_link_libraries(VCellStoch VCellStochLib)

# Installation rules
install(TARGETS VCellStochLib VCellStoch
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES ${HEADER_FILES} DESTINATION include/VCellStoch)
