// Copyright 2019 Max Godfrey
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "main.h"

#include <sys/stat.h>
#include <cstdlib>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "src/kmp.h"
#include "src/rabin_karp.h"

namespace cli {
namespace matching {

void Match(std::string filename, std::string pattern) {
  std::ifstream infile(filename);
  std::string line;
  std::vector<int> occurrences;
  int pattern_length = static_cast<int>(pattern.length());
  int line_idx;
  int line_length;

  while (std::getline(infile, line)) {
    occurrences = gss::kmp::FindMatches(line, pattern);
    if (!occurrences.empty()) {
      line_idx = 0;
      line_length = static_cast<int>(line.length());
      for (int occ_idx : occurrences) {
        for (; line_idx < occ_idx; ++line_idx) {
          std::cout << line[line_idx];
        }
        std::cout << color::RED;
        for (; line_idx < occ_idx + pattern_length; ++line_idx) {
          std::cout << line[line_idx];
        }
        std::cout << color::RESET;
      }
      for (; line_idx < line_length; ++line_idx) {
        std::cout << line[line_idx];
      }
      std::cout << std::endl;
    }
  }
}

}  // namespace matching

inline void CheckAccessible(const char *filename) {
  struct stat buffer;
  if (stat(filename, &buffer) != 0) {
    std::cerr << "ERROR: `" << filename << "` is not accessible." << std::endl;
    exit(EXIT_FAILURE);
  }
}

void CheckArgv(char **arg_start, char **arg_end) {
  if (HasOption(arg_start, arg_end, "-h") ||
      HasOption(arg_start, arg_end, "--help") ||
      arg_end - arg_start == 1) {
    PrintHelpUtil();
    exit(EXIT_SUCCESS);
  }
  if (arg_end - arg_start != 3) {
    std::cerr << "ERROR: incorrect number of arguments.\n"
              << "Execute `gss --help` for more info."
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

inline bool HasOption(char **arg_start, char **arg_end,
                      const std::string &option) {
  return (std::find(arg_start, arg_end, option) != arg_end);
}

inline void PrintHelpUtil() {
  std::cout << "gss: Grep for Small Strings\n"
            << "Usage: gss [--help] [FILE] [PATTERN]\n\n"
            << "Flags:\n"
            << "  -h, --help    display this help text and exit"
            << std::endl;
}

}  // namespace cli

int main(int argc, char *argv[]) {
  // Optimize std::cout - this will (hopefully) help us run faster than grep.
  std::ios::sync_with_stdio(false);
  std::cout.tie(nullptr);

  cli::CheckArgv(argv, argv + argc);
  cli::CheckAccessible(argv[1]);

  std::string filename(argv[1]);
  std::string search_pattern(argv[2]);
  cli::matching::Match(filename, search_pattern);

  return EXIT_SUCCESS;
}
