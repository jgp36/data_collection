
#
# Components, types and plugins.
#
# The CMake 'target' names are identical to the first argument of the
# macros below, except for orocos_typegen_headers, where the target is fully
# controlled by generated code of 'typegen'.
#

# Creates a component library libdata_collection-<target>.so
# and installs in the directory lib/orocos/data_collection/
#
orocos_component(data_collection data_collection-component.hpp data_collection-component.cpp) # ...you may add multiple source files
#
# You may add multiple orocos_component statements.

#
# Additional headers:
#
# Installs in the include/orocos/data_collection/ directory
#
orocos_install_headers(data_collection-component.hpp) # ...you may add multiple header files
#
# You may add multiple orocos_install_headers statements.

