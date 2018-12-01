R"delim(add_executable(main)
target_sources(main PRIVATE main.cpp)
target_link_libraries(main
                      PRIVATE main::project
                              project_warnings)
)delim"