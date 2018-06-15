find_package(Boost REQUIRED COMPONENTS filesystem)

find_package(FMT REQUIRED)

add_library(project_library default_project.cpp ../include/project_template/default_project.hpp)
target_link_libraries(project_library
  PUBLIC Boost::filesystem
  PRIVATE fmt::fmt project_std)

find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(llvm_libs support)

add_library(llvm_ INTERFACE)
target_compile_definitions(llvm_ INTERFACE ${LLVM_DEFINITIONS})
target_include_directories(llvm_ INTERFACE ${LLVM_INCLUDE_DIRS})
target_link_libraries(llvm_ INTERFACE ${llvm_libs})

add_executable(main main.cpp)
target_link_libraries(main Boost::filesystem project_library project_std fmt::fmt llvm_)
