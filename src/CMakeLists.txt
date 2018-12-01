add_project_template_library(cmake_execution)
target_sources(
  cmake_execution
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include/project_template/cmake_execution.hpp
  PRIVATE
  cmake_execution.cpp)
target_link_libraries(cmake_execution
                      PUBLIC std::filesystem
                      PRIVATE fmt::fmt-header-only reproc++)

add_project_template_library(default_project)
target_sources(
  default_project
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include/project_template/default_project.hpp
  PRIVATE
  default_project.cpp)
target_link_libraries(default_project
                      PUBLIC std::filesystem
                      PRIVATE fmt::fmt-header-only cmake_execution)

find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(llvm_libs support)

add_library(llvm INTERFACE)
target_compile_definitions(llvm INTERFACE ${LLVM_DEFINITIONS})
target_include_directories(llvm INTERFACE ${LLVM_INCLUDE_DIRS})
target_link_libraries(llvm INTERFACE ${llvm_libs})
add_library(llvm::llvm ALIAS llvm)

add_executable(main)
target_sources(main PRIVATE main.cpp)
target_link_libraries(main
                      PRIVATE main::project
                              std::filesystem
                              default_project
                              fmt::fmt-header-only
                              llvm::llvm)
