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

#include "rabin_karp.h"

namespace gss {
namespace rabin_karp {

std::vector<int> FindMatches(std::string search, std::string pattern) {
  int search_length = static_cast<int>(search.length());
  int pattern_length = static_cast<int>(pattern.length());
  std::vector<int> occurrences;

  // Precompute (MAX_CHAR ^ (M - 1) mod HASH_KEY) where ^ is an exponent.
  int mc_precomp = 1;
  for (int i = 0; i + 1 < pattern_length; ++i) {
    mc_precomp = (MAX_CHAR * mc_precomp) % HASH_KEY;
  }

  // Hash the search string and the pattern according to a modular hash
  // function. The hash value is computed for the first "window", or text
  // segment whose length is that of pattern.
  int search_hash = 0;
  int pattern_hash = 0;
  for (int i = 0; i < pattern_length; ++i) {
    search_hash = (MAX_CHAR * search_hash + search[i]) % HASH_KEY;
    pattern_hash = (MAX_CHAR * pattern_hash + pattern[i]) % HASH_KEY;
  }

  // Start searching...
  for (int i = 0; i <= search_length - pattern_length; ++i) {
    if (search_hash == pattern_hash) {
      int current_idx = 0;
      for (; current_idx < pattern_length; ++current_idx) {
        if (search[i + current_idx] != pattern[current_idx]) {
          break;
        }
      }

      if (current_idx == pattern_length) {
        // We have found an occurrence of pattern in our search string!
        occurrences.push_back(i);
      }
    }

    // Hash the next "window".
    if (i < search_length - pattern_length) {
      search_hash = (MAX_CHAR * (search_hash - search[i] * mc_precomp) +
                      search[i + pattern_length]) % HASH_KEY;
      if (search_hash < 0) {
        search_hash += HASH_KEY;
      }
    }
  }

  return occurrences;
}

}  // namespace rabin_karp
}  // namespace gss
