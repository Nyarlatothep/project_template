#ifndef SYM_LINK_HPP
#define SYM_LINK_HPP

#include <boost/filesystem/path.hpp>

class SymLink {
 public:
  SymLink(boost::filesystem::path source);

  void write_to(const boost::filesystem::path& directory) const;

 private:
  boost::filesystem::path source_;
};
#endif /* SYM_LINK_HPP */
