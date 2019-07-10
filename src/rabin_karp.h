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

#ifndef SRC_RABIN_KARP_H_
#define SRC_RABIN_KARP_H_

#include <string>
#include <vector>

namespace gss {
namespace rabin_karp {

const int HASH_KEY = 101;
const int MAX_CHAR = 256;

// Finds all occurrences of a pattern in a chunk of text.
//
// Args:
//   - search: string, the text to be searched.
//   - pattern: string, the pattern which we are trying to find in search.
//
// Returns:
//   vector<int>: the starting indicies of all occurrences of pattern within
//                our search string.
//
std::vector<int> FindMatches(std::string search, std::string pattern);

}  // namespace rabin_karp
}  // namespace gss

#endif  // SRC_RABIN_KARP_H_
