find_package(Boost REQUIRED COMPONENTS filesystem)

add_library(boost_dependent
  file.cpp
  folder.cpp)
target_link_libraries(boost_dependent PRIVATE Boost::filesystem)

add_library(project_library
  default_project.cpp)
target_link_libraries(project_library boost_dependent)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})

add_executable(main main.cpp)
target_include_directories(main PUBLIC ${LLVM_INCLUDE_DIRS})
llvm_map_components_to_libnames(llvm_libs support)
target_link_libraries(main Boost::filesystem project_library ${llvm_libs})
