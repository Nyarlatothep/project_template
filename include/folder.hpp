#ifndef FOLDER_HPP
#define FOLDER_HPP

#include <boost/filesystem/path.hpp>

#include <string>
#include <vector>

#include "file.hpp"

class Folder {
 public:
  Folder(std::string name);

  void add(File);
  void add(Folder);

  void write_to(const boost::filesystem::path& directory) const;

 private:
  const std::string name_;
  std::vector<Folder> directories_;
  std::vector<File> files_;
};

#endif /* FOLDER_HPP */
