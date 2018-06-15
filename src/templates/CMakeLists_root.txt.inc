R"delim(cmake_minimum_required(VERSION 3.11)

# Use iso c++
set(CMAKE_CXX_EXTENSIONS OFF)

# Output compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Link this 'library' to use the following warnings
add_library(project_warnings INTERFACE)

if(MSVC)
  target_compile_options(project_warnings INTERFACE /W4)
else()
  target_compile_options(project_warnings
                         INTERFACE
                         -Wall
                         -Wextra # reasonable and standard
                         -Wpedantic # warn if non-standard C++ is used
                         -Wshadow # warn the user if a variable declaration shadows one from a
                                  # parent context
                         -Wnon-virtual-dtor # warn the user if a class with virtual functions has a
                                            # non-virtual destructor. This helps catch hard to
                                            # track down memory errors
                         -Wold-style-cast # warn for c-style casts
                         -Wcast-align # warn for potential performance problem casts
                         -Wunused # warn on anything being unused
                         -Woverloaded-virtual # warn if you overload (not override) a virtual
                                              # function
                         -Wconversion # warn on type conversions that may lose data
                                      # probably wanted
                         -Wnull-dereference # warn if a null dereference is detected
                         -Wdouble-promotion # warn if float is implicit promoted to double
                         -Wformat=2 # warn on security issues around functions that format output
                                    # (ie printf)
                         )
endif()

project({} CXX)

add_library(main_project INTERFACE)
target_compile_features(main_project INTERFACE cxx_std_17)
target_include_directories(main_project INTERFACE
  include/)
target_link_libraries(main_project INTERFACE project_warnings)

add_subdirectory(src)
)delim"