#ifndef DEFAULT_PROJECT_HPP
#define DEFAULT_PROJECT_HPP

#include <boost/filesystem/path.hpp>
#include <string>

void create_default_project(const boost::filesystem::path& target_directory,
                            const std::string& project_name);

void create_default_spacemacs_project(
    const boost::filesystem::path& target_directory,
    const std::string& project_name);

#endif /* DEFAULT_PROJECT_HPP */
