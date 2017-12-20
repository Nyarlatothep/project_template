#include "sym_link.hpp"

#include <boost/filesystem/operations.hpp>

SymLink::SymLink(boost::filesystem::path source) : source_{source} {}

void SymLink::write_to(const boost::filesystem::path& directory) const {
  boost::filesystem::create_symlink(source_, directory / source_.filename());
}
