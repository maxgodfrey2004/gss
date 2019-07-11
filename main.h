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

#ifndef MAIN_H_
#define MAIN_H_

#include <string>

namespace cli {
namespace color {

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";

}  // namespace color

namespace matching {

// Prints all occurrences of a pattern in a file. Note that we assume the file
// exists, and is accessible in the implementation.
//
// Args:
//   - filename: string, the name of the file we are searching.
//   - pattern: string, the pattern we are searching for.
void Match(std::string filename, std::string pattern);

}  // namespace matching

// Checks whether a specified file is accessible given the permissions assigned
// to the program.
//
// Args:
//   - filename: const char *, the name of the file.
//
inline void CheckAccessible(const char *filename);

// Parses command line arguments.
//
// Args:
//   - arg_start: char **, the start of argv.
//   - arg_end: char **, the end of argv.
//
void CheckArgv(char **arg_start, char **arg_end);

// Determines whether an option has been passed as a command line argument.
//
// Args:
//   - arg_start: char **, the start of argv.
//   - arg_end: char **, the end of argv.
//   - option: const string &, the option we are searching for.
//
inline bool HasOption(char **arg_start, char **arg_end,
                      const std::string &option);

// Prints the application's help utility.
//
inline void PrintHelpUtil();

}  // namespace cli

#endif  // MAIN_H_
