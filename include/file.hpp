#ifndef FILE_HPP
#define FILE_HPP

#include <boost/filesystem/path.hpp>

#include <string>

class File {
 public:
  File(std::string name, std::string content);

  void write_to(const boost::filesystem::path& directory) const;

 private:
  const std::string name_;
  const std::string content_;
};

#endif /* FILE_HPP */
