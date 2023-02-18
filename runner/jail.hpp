#pragma once

#include <filesystem>
#include <iostream>
#include "utils.hpp"
#include "global_config.hpp"

struct Jail{
  static int number_of_jails;

  std::filesystem::path jail_path;

  Jail(const std::filesystem::path& jail_path)
    : jail_path(jail_path) {
    if(execute_script(concat_path(work_dir, "makejail.sh"), {jail_path.string()})){
      std::cerr << "Error creating jail.\n";
      std::exit(4);
    }
  }

};