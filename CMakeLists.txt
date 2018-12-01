cmake_minimum_required(VERSION 3.12)

project(project_template CXX)

# Use iso c++
set(CMAKE_CXX_EXTENSIONS OFF)

# Link this 'library' to use the following warnings
add_library(project_warnings INTERFACE)

if(MSVC)
  target_compile_options(project_warnings INTERFACE /W4)
else()
  target_compile_options(project_warnings
                         INTERFACE -Wall
                                   -Wextra # reasonable and standard
                                   -Wshadow # warn the user if a variable
                                            # declaration shadows one from a
                                            # parent context
                                   -Wnon-virtual-dtor # warn the user if a class
                                                      # with virtual functions
                                                      # has a non-virtual
                                                      # destructor. This helps
                                                      # catch hard to track down
                                                      # memory errors
                                   -Wold-style-cast # warn for c-style casts
                                   -Wcast-align # warn for potential performance
                                                # problem casts
                                   -Wunused # warn on anything being unused
                                   -Woverloaded-virtual # warn if you overload
                                                        # (not override) a
                                                        # virtual function
                                   -Wpedantic # warn if non-standard C++ is used
                                   -Wconversion # warn on type conversions that
                                                # may lose data
                                   -Wsign-conversion # warn on sign conversions
                                   -Wnull-dereference # warn if a null
                                                      # dereference is detected
                                   -Wdouble-promotion # warn if float is
                                                      # implicit promoted to
                                                      # double
                                   -Wformat=2 # warn on security issues around
                                              # functions that format output (ie
                                              # printf)
                         )
  if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(project_warnings
                           INTERFACE -Wmisleading-indentation # warn if
                                                              # identation
                                                              # implies blocks
                                                              # where blocks do
                                                              # not exist
                                     -Wduplicated-cond # warn if if / else chain
                                                       # has duplicated
                                                       # conditions
                                     -Wduplicated-branches # warn if if / else
                                                           # branches have
                                                           # duplicated code
                                     -Wlogical-op # warn about logical
                                                  # operations being used where
                                                  # bitwise were probably wanted
                                     -Wuseless-cast # warn if you perform a cast
                                                    # to the same type
                           )
  endif(CMAKE_COMPILER_IS_GNUCXX)
endif(MSVC)

add_library(std_filesystem INTERFACE)
target_link_libraries(std_filesystem INTERFACE c++fs)
target_compile_features(std_filesystem INTERFACE cxx_std_17)
add_library(std::filesystem ALIAS std_filesystem)

add_library(main_project INTERFACE)
target_compile_features(main_project INTERFACE cxx_std_20)
target_include_directories(main_project
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
add_library(main::project ALIAS main_project)

function(add_project_template_library target)
  add_library(${target} ${ARGN})
  target_link_libraries(${target} PUBLIC main::project PRIVATE project_warnings)
endfunction(add_project_template_library)

add_subdirectory(third_party)
add_subdirectory(src)
