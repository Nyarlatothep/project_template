#ifndef PORTABILITY_FILESYSTEM_HPP
#define PORTABILITY_FILESYSTEM_HPP

#include <string_view>

namespace detail {

constexpr std::string_view windows_invalid_chars{
    "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12"
    "\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F<>:\"/\\|"};

constexpr std::string_view valid_posix(
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._-");

}  // namespace detail

constexpr bool portable_posix_name(std::string_view name) {
  return std::size(name) != 0 and
         name.find_first_not_of(detail::valid_posix) == std::string_view::npos;
}

constexpr bool windows_name(std::string_view name) {
  return std::size(name) != 0 and name[0] != ' ' and
         name.find_first_of(detail::windows_invalid_chars) ==
             std::string_view::npos and
         *(name.end() - 1) != ' ' and
         (*(name.end() - 1) != '.' or name.length() == 1 or name == "..");
}

constexpr bool portable_name(std::string_view name) {
  return std::size(name) != 0 and
         (name == "." or name == ".." or
          (windows_name(name) and portable_posix_name(name) and
           name[0] != '.' and name[0] != '-'));
}

constexpr bool portable_directory_name(std::string_view name) {
  return name == "." or name == ".." or
         (portable_name(name) and name.find('.') == std::string_view::npos);
}

#endif /* PORTABILITY_FILESYSTEM_HPP */
