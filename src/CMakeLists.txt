add_library(boost_dependent
  cmake_execution.cpp
  file.cpp
  folder.cpp
  template_files.cpp)
target_link_libraries(boost_dependent PRIVATE ${Boost_LIBRARIES})

add_library(project_library
  default_project.cpp)
target_link_libraries(project_library boost_dependent)

