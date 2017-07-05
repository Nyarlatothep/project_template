#include "folder.hpp"

#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

Folder::Folder(std::string name) : name_{name} {}

void Folder::add(File file) { files_.push_back(file); }

void Folder::add(Folder folder) { directories_.push_back(folder); }

void Folder::write_to(const fs::path& directory) const {
  const fs::path new_directory{directory / name_};
  fs::create_directory(new_directory);
  for (const auto& folder : directories_) {
    folder.write_to(new_directory);
  }
  for (const auto& file : files_) {
    file.write_to(new_directory);
  }
}
