cmake_minimum_required(VERSION 3.11)

# Use iso c++
set(CMAKE_CXX_EXTENSIONS OFF)

# Link this 'library' to use the following warnings
add_library(project_warnings INTERFACE)

if(MSVC)
  target_compile_options(project_warnings INTERFACE /W4)
else()
  target_compile_options(project_warnings
    INTERFACE
    -Wall
    -Wextra # reasonable and standard
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
    -Wpedantic # warn if non-standard C++ is used
    -Wconversion # warn on type conversions that may lose data
    -Wsign-conversion # warn on sign conversions
    -Wnull-dereference # warn if a null dereference is detected
    -Wdouble-promotion # warn if float is implicit promoted to double
    -Wformat=2 # warn on security issues around functions that format output
    # (ie printf)
    )
  if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(project_warnings
      INTERFACE
      -Wmisleading-indentation # warn if identation implies blocks where blocks
      # do not exist
      -Wduplicated-cond # warn if if / else chain has duplicated conditions
      -Wduplicated-branches # warn if if / else branches have duplicated code
      -Wlogical-op # warn about logical operations being used where bitwise were
      # probably wanted
      -Wuseless-cast # warn if you perform a cast to the same type
      )
  endif(CMAKE_COMPILER_IS_GNUCXX)
endif()

project(project_template CXX)

add_library(libc++ INTERFACE)
target_compile_options(libc++ INTERFACE
  -stdlib=libc++)
target_link_libraries(libc++ INTERFACE
  c++ c++abi)

add_library(std_filesystem INTERFACE)
target_link_libraries(std_filesystem INTERFACE c++fs)

add_library(project_std INTERFACE)
target_compile_features(project_std INTERFACE cxx_std_17)
target_include_directories(project_std INTERFACE
  include/)
target_link_libraries(project_std INTERFACE project_warnings libc++)

add_subdirectory(third_party)
add_subdirectory(src)
