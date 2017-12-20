#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <boost/filesystem/path.hpp>
#include <string>

#include "folder.hpp"

Folder default_project(const std::string& project_name);

Folder default_spacemacs_project(const std::string& project_name,
                                 const boost::filesystem::path& working_directory);

#endif /* PROJECT_HPP */
