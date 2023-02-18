#pragma once

#include <string>
#include <vector>
#include <filesystem>

template<typename Fn>
void prompt(const std::string& text, const std::string& yes, const std::string& no, Fn fn) {
  std::string input;
  std::cout << text;
  std::cin >> input;
  if (input == yes) {
    fn();
  } else if (input == no) {
    return;
  } else {
    prompt(text, yes, no, fn);
  }
}

auto concat_path(std::filesystem::path a, std::string_view b) -> std::filesystem::path {
  return a / b;
};


int execute_script(const std::filesystem::path& script_path, const std::vector<std::string>& args) {
  // Build command string
  std::string cmd = script_path.string();
  for (const auto& arg : args) {
    cmd += " \"" + arg + "\"";
  }

  // Execute command
  int ret = std::system(cmd.c_str());
  if (ret != 0) {
    std::cerr << "Error executing script: " << script_path << std::endl;
  }
  return ret;
}
