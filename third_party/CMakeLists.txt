set(REPROCXX ON CACHE BOOL "" FORCE)
add_subdirectory(reproc)

add_library(fmt-header-only INTERFACE)
target_compile_definitions(fmt-header-only INTERFACE
  FMT_HEADER_ONLY=1
  FMT_STRING_ALIAS=1)
target_include_directories(fmt-header-only INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/fmt/include)
add_library(fmt::fmt-header-only ALIAS fmt-header-only)
