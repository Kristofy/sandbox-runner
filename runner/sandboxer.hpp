#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <filesystem>

#include "utils.hpp"
#include "global_config.hpp"
#include "jail.hpp"

struct Sandboxer {
  std::string sandbox_template_path;
  std::string jails_path;
  std::vector<Jail> jails;

  Sandboxer(const std::string& sandbox_template_path=sandbox_template_path_default, const std::string& jails_path=jails_path_default)
    : sandbox_template_path(sandbox_template_path), jails_path(jails_path) {
      if (!std::filesystem::exists(sandbox_template_path)) {
        prompt("Sandbox template path does not exist. Create it? (y/n): ", "y", "n", [&] {
          if(execute_script(concat_path(work_dir, "setupjail.sh"), {sandbox_template_path})){
            std::cerr << "Error creating sandbox template.\n";
            std::exit(2);
          }
        });
      } else {
        std::cerr << "Sandbox template directory decetected.\n";
      }

      if (!std::filesystem::exists(jails_path)) {
        prompt("Jails path does not exist. Create it? (y/n): ", "y", "n", [&] {
          if(!std::filesystem::create_directory(jails_path)){
            std::cerr << "Error creating jails directory.\n";
            std::exit(3);
          }
        });
      } else {
        std::cerr << "Jails directory decetected.\n";
      }
    }

    void run(const std::string& command) {
      auto& jail = create_jail("jail" + std::to_string(Jail::number_of_jails++));
      jail.run(command);
    }

  private:
    Jail& create_jail(const std::string& name) {
      jails.emplace_back(concat_path(this->jails_path, "jail" + std::to_string(Jail::number_of_jails++)));
      return jails.back();
    }

};
