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

#include "fileutils.h"

#include <sys/stat.h>
#include <cstdlib>

#include <fstream>
#include <iostream>
#include <vector>

#include "kmp.h"

namespace gss {
namespace color {

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";

}  // namespace color

namespace fileutils {

inline void CheckAccessible(const char *filename) {
  struct stat buffer;
  if (stat(filename, &buffer) != 0) {
    std::cerr << "ERROR: `" << filename << "` is not accessible." << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Match(std::string filename, std::string pattern) {
  CheckAccessible(filename.c_str());
  std::ifstream infile(filename);
  std::string line;
  std::vector<int> occurrences;
  int pattern_length = static_cast<int>(pattern.length());
  int line_idx;
  int line_length;

  while (std::getline(infile, line)) {
    if (line == "") {
      continue;
    }
    occurrences = kmp::FindMatches(line, pattern);
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

}  // namespace fileutils
}  // namespace gss