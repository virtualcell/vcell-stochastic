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
        Python3::Python
)

target_compile_features(vcellstochastic_py PRIVATE cxx_std_14)

target_include_directories(vcellstochastic_py PRIVATE
        ${Python3_INCLUDE_DIRS}
)