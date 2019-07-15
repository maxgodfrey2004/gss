# Copyright 2019 Max Godfrey
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# 		http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Benchmarks grep and gss.
"""

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

from timeit import timeit

import generate

# Change this according to your file structure!
PATH_TO_GSS_BINARY = '../gss'

# The amount of tests we run for each individual string. This helps us get an
# even more accurate benchmark.
SINGLE_STRING_TESTS = 10

BENCHMARK_SETUP = '''import os
import subprocess
import sys
stderr = sys.stderr
stdout = open(os.devnull, 'w')
'''

# Arguments passed when benchmarking grep.
GREP_CALL_ARGS = '''['grep', '{}', '{}'],
    stdout=stdout,
    stderr=stderr'''

# Arguments passed when benchmarking gss.
GSS_CALL_ARGS = '''['%s', '{}', '{}'],
    stdout=stdout,
    stderr=stderr''' % (PATH_TO_GSS_BINARY)

def _benchmark_grep(filename, pattern):
    """Benchmarks grep.

    Args:
      - filename: The name of the file to be searched.
      - pattern: The pattern we are searching for in the file.
    """
    time_taken = timeit(setup=BENCHMARK_SETUP, number=SINGLE_STRING_TESTS,
        stmt='subprocess.call(%s)' % GREP_CALL_ARGS.format(pattern, filename))
    return time_taken / SINGLE_STRING_TESTS

def _benchmark_gss(filename, pattern):
    """Benchmarks gss.

    Args:
      - filename: The name of the file to be searched.
      - pattern: The pattern we are searching for in the file.
    """
    time_taken = timeit(setup=BENCHMARK_SETUP, number=SINGLE_STRING_TESTS,
        stmt='subprocess.call(%s)' % GSS_CALL_ARGS.format(filename, pattern))
    return time_taken / SINGLE_STRING_TESTS

def benchmark_all(filename, lines, columns, lengths):
    """Benchmarks grep and gss simultaneously with the same random strings.

    Args:
      - filename: The name of the file to be created.
      - lines: The number of lines for the file to be propogated with.
      - columns: The width of each line in the file.
      - lengths: An array of the random string lengths to be benchmarked.
    """

    generate.generate_file(filename, lines, columns)
    print('File specifications [name: {}, lines: {}, columns: {}]'.
          format(filename, lines, columns))

    for length in lengths:
        pattern = generate.random_string(length)
        grep_runtime = _benchmark_grep(filename, pattern)
        gss_runtime = _benchmark_gss(filename, pattern)
        print('grep benchmark with string of length {}: {}'.
              format(length, grep_runtime))
        print('gss  benchmark with string of length {}: {}'.
              format(length, gss_runtime))

        if grep_runtime < gss_runtime:
            print('grep ran faster')
        elif grep_runtime > gss_runtime:
            print('gss ran faster')
        else:
            print('grep and gss have equal runtimes')
