find_package(FMT REQUIRED)

find_package(Boost REQUIRED COMPONENTS filesystem)

add_library(cmake_execution cmake_execution.cpp ../include/project_template/cmake_execution.hpp)
target_link_libraries(cmake_execution
  PUBLIC stdc++fs
  PRIVATE fmt::fmt project_std Boost::filesystem)

add_library(default_project default_project.cpp ../include/project_template/default_project.hpp)
target_link_libraries(default_project
  PUBLIC stdc++fs
  PRIVATE fmt::fmt cmake_execution project_std)

find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(llvm_libs support)

add_library(llvm_ INTERFACE)
target_compile_definitions(llvm_ INTERFACE ${LLVM_DEFINITIONS})
target_include_directories(llvm_ INTERFACE ${LLVM_INCLUDE_DIRS})
target_link_libraries(llvm_ INTERFACE ${llvm_libs})

add_executable(main main.cpp)
target_link_libraries(main
  stdc++fs default_project project_std fmt::fmt llvm_)
