find_package(FMT REQUIRED)

find_package(Boost REQUIRED COMPONENTS filesystem)
add_library(boost_process INTERFACE)
target_link_libraries(boost_process INTERFACE
  Boost::filesystem)

add_library(cmake_execution cmake_execution.cpp ../include/project_template/cmake_execution.hpp)
target_link_libraries(cmake_execution
  PUBLIC std_filesystem
  PRIVATE fmt::fmt boost_process project_std)

add_library(default_project default_project.cpp ../include/project_template/default_project.hpp)
target_link_libraries(default_project
  PUBLIC std_filesystem
  PRIVATE fmt::fmt cmake_execution project_std)

find_package(LLVM REQUIRED support)
llvm_map_components_to_libnames(llvm_libs support core)

add_library(llvm INTERFACE)
target_include_directories(llvm INTERFACE ${LLVM_INCLUDE_DIRS})
target_compile_definitions(llvm INTERFACE ${LLVM_DEFINITIONS})
target_link_libraries(llvm INTERFACE ${llvm_libs})

add_executable(main main.cpp)
target_link_libraries(main
  project_std std_filesystem default_project fmt::fmt llvm)
