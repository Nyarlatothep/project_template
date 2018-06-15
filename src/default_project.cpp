#include "project_template/default_project.hpp"

#include <fmt/format.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

namespace {

void create_file(const fs::path& file_path, const std::string_view content) {
  fs::ofstream file{file_path};
  if (file) {
    file << content;
  } else {
    throw std::runtime_error{
        fmt::format(fmt("Could not create file {}"), file_path.string())};
  }
}

void create_default_bin_folder(const fs::path& target_directory) {
  const fs::path bin_root_directory = target_directory / "bin";
  fs::create_directory(bin_root_directory);
}

void create_default_build_folder(const fs::path& target_directory) {
  const fs::path build_root_directory = target_directory / "build";
  fs::create_directory(build_root_directory);

  fs::create_directory(build_root_directory / "Debug");
  fs::create_directory(build_root_directory / "Release");
}

void create_default_include_folder(const fs::path& target_directory) {
  const fs::path include_root_directory = target_directory / "include";
  fs::create_directory(include_root_directory);
}

void create_CMakeLists_src_file(const fs::path& target_directory) {
  constexpr std::string_view content{
#include "templates/CMakeLists_src.txt.inc"
  };
  create_file(target_directory / "CMakeLists.txt", content);
}

void create_main_cpp_file(const fs::path& target_directory) {
  constexpr std::string_view content{
#include "templates/main.cpp.inc"
  };
  create_file(target_directory / "main.cpp", content);
}

void create_default_src_folder(const fs::path& target_directory) {
  const fs::path src_root_directory = target_directory / "src";
  fs::create_directory(src_root_directory);

  create_CMakeLists_src_file(src_root_directory);
  create_main_cpp_file(src_root_directory);
}

void create_CMakeLists_root_file(const fs::path& target_directory,
                                 const std::string_view project_name) {
  constexpr auto text{
#include "templates/CMakeLists_root.txt.inc"
  };
  return create_file(target_directory / "CMakeLists.txt",
                     fmt::format(fmt(text), project_name));
}

void create_clang_format_file(const fs::path& target_directory) {
  constexpr std::string_view content{
#include "templates/.clang-format.inc"
  };
  create_file(target_directory / ".clang-format", content);
}

void create_projectile_file(const fs::path& target_directory) {
  constexpr std::string_view content{
#include "templates/.projectile.inc"
  };
  create_file(target_directory / ".projectile", content);
}

void create_dir_locals_file(const fs::path& target_directory) {
  constexpr std::string_view cmake_build_type{"Debug"};
  constexpr auto content{
#include "templates/.dir-locals.el.inc"
  };

  create_file(target_directory / ".dir-locals.el",
              fmt::format(fmt(content), cmake_build_type));
}

}  // namespace

void create_default_project(const fs::path& target_directory,
                            const std::string& project_name) {
  const fs::path project_root_directory = target_directory / project_name;
  fs::create_directory(project_root_directory);

  create_default_bin_folder(project_root_directory);
  create_default_build_folder(project_root_directory);
  create_default_include_folder(project_root_directory);
  create_default_src_folder(project_root_directory);

  create_CMakeLists_root_file(project_root_directory, project_name);
  create_clang_format_file(project_root_directory);
}

void create_default_spacemacs_project(const fs::path& target_directory,
                                      const std::string& project_name) {
  create_default_project(target_directory, project_name);

  const fs::path project_root_directory = target_directory / project_name;
  create_projectile_file(project_root_directory);
  create_dir_locals_file(project_root_directory);
}
