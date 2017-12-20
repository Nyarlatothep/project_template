find_package(Boost REQUIRED COMPONENTS filesystem)

add_library(file file.cpp ../include/file.hpp)
target_link_libraries(file Boost::filesystem)

add_library(sym_link sym_link.cpp ../include/sym_link.hpp)
target_link_libraries(sym_link Boost::filesystem)

add_library(folder folder.cpp ../include/folder.hpp)
target_link_libraries(folder file sym_link Boost::filesystem)

find_package(FMT REQUIRED)

add_library(project_library default_project.cpp ../include/default_project.hpp)
target_link_libraries(project_library folder fmt::fmt)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})

add_executable(main main.cpp)
target_include_directories(main PUBLIC ${LLVM_INCLUDE_DIRS})
llvm_map_components_to_libnames(llvm_libs support)
target_link_libraries(main Boost::filesystem project_library ${llvm_libs})
