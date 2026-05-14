project(vcellstochastic_python LANGUAGES CXX)

# This file assumes you will add a binding source file later, such as:
#   src/bindings.cpp
#
# For now, this directory is only active when OPTION_BUILD_PYTHON_BINDINGS=ON.

pybind11_add_module(vcellstochastic_py
        src/bindings.cpp
)

target_link_libraries(vcellstochastic_py
        PRIVATE
        VCellStochLib
)

target_compile_features(vcellstochastic_py PRIVATE cxx_std_14)

target_include_directories(vcellstochastic_py PRIVATE
        ${PROJECT_SOURCE_DIR}/VCellStoch/include
        ${PROJECT_SOURCE_DIR}/ExpressionParser
        ${PROJECT_SOURCE_DIR}/vcommons/include
        ${PROJECT_SOURCE_DIR}/VCellMessaging/include
)

if(BUILD_TESTING)
    add_test(
        NAME TestPythonBindings
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test_binding.py
    )
    set_tests_properties(TestPythonBindings PROPERTIES
        ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/bin:${CMAKE_SOURCE_DIR}/python/src"
    )
endif()