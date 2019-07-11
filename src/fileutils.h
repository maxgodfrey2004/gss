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

#include <string>

namespace gss {
namespace fileutils {

// Checks whether a specified file is accessible given the permissions assigned
// to the program.
//
// Args:
//   - filename: const char *, the name of the file.
//
inline void CheckAccessible(const char *filename);

// Prints all occurrences of a pattern in a file. Note that we assume the file
// exists, and is accessible in the implementation.
//
// Args:
//   - filename: string, the name of the file we are searching.
//   - pattern: string, the pattern we are searching for.
//
void Match(std::string filename, std::string pattern);

}  // namespace fileutils
}  // namespace gss