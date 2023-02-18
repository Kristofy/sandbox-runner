#pragma once

#include <string>
#include <string_view>
#include <filesystem>
#include <cstdlib>
#include "utils.hpp"


std::string_view base = "dev";

std::string home_path = std::getenv("HOME") + std::string("/alpha/sandbox");

auto work_dir = concat_path(home_path, base);
auto sandbox_template_path_default = concat_path(work_dir, "sandbox");
auto jails_path_default = concat_path(work_dir, "jails");


