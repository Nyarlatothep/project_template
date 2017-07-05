#include "default_project.hpp"

#include "template_files.hpp"

Folder default_project(const std::string& name) {
  Folder project{name};
  project.add(Folder{"bin"});
  project.add(Folder{"build"});
  project.add(Folder{"include"});
  project.add(File{".projectile", ProjectileFile()});
  project.add(File{"CMakeLists.txt", CMakeListsRootFile(name)});

  Folder src{"src"};
  src.add(File{"CMakeLists.txt", CMakeListsSrcFile()});
  src.add(File{"main.cpp", MainFile()});

  project.add(src);

  return project;
}
