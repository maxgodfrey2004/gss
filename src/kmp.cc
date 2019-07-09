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

#include "kmp.h"

#include <iostream>

namespace gss {
namespace kmp {

std::vector<int> ComputePrefix(std::string search) {
  std::vector<int> prefix_vals(search.length());
  prefix_vals[0] = 0;
  int current_prefix = 0;

  for (int i = 1; i < static_cast<int>(search.length()); ++i) {
    // Jump by prefix values to try smaller prefixes. This process stops when
    // we either find a match, or reach zero.
    while (current_prefix > 0 && search[i] != search[current_prefix]) {
      current_prefix = prefix_vals[current_prefix - 1];
    }
    if (search[i] == search[current_prefix]) {
      ++current_prefix;
    }
    prefix_vals[i] = current_prefix;
  }

  return prefix_vals;
}

std::vector<int> FindMatches(std::string search, std::string pattern) {
  if (search == "") {
    std::cerr << "ERROR: text to search must not be blank" << std::endl;
  }

  std::vector<int> prefix_vals = ComputePrefix(search);
  std::vector<int> occurrences;

  int max_length_prefix = 0;
  for (int i = 0; i < static_cast<int>(search.length()); ++i) {
    // Jump by prefix values to try smaller prefixes. Keep jumping until we
    // either find a match, or reach zero.
    while (max_length_prefix > 0 && search[i] != pattern[max_length_prefix]) {
      max_length_prefix = prefix_vals[max_length_prefix - 1];
    }
    if (search[i] == pattern[max_length_prefix]) {
      ++max_length_prefix;
    }
    if (max_length_prefix == static_cast<int>(pattern.length())) {
      // We have found an occurrence of pattern in our search string!
      occurrences.push_back(i - pattern.length() + 1);
      max_length_prefix = prefix_vals[max_length_prefix - 1];
    }
  }

  return occurrences;
}

}  // namespace kmp
}  // namespace gss
