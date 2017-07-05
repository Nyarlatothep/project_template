#include "file.hpp"

#include <boost/filesystem/fstream.hpp>

File::File(std::string name, std::string content)
    : name_{name}, content_{content} {}

void File::write_to(const boost::filesystem::path& directory) const {
  boost::filesystem::ofstream temp{directory / name_};
  temp << content_;
}
