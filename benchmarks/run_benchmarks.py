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

"""Runs multiple benchmarks of grep and gss on files of various sizes.
"""

import benchmark

# The name of the file that generate.py will create.
GENFILE_NAME = 'generate_out.txt'

def test_small():
    """Benchmarks grep and gss on smaller files.
    """
    benchmark.benchmark_all(GENFILE_NAME, 5, 5, [1, 2, 3, 4, 5])
    benchmark.benchmark_all(GENFILE_NAME, 10, 10, [2, 4, 6, 8, 10])

def test_medium():
    """Benchmarks grep and gss on average sized files.
    """
    benchmark.benchmark_all(GENFILE_NAME, 100, 100,
                            [10, 30, 50, 70, 99])
    benchmark.benchmark_all(GENFILE_NAME, 1000, 1000,
                            [111, 333, 555, 777, 999])

def test_large():
    """Benchmarks grep and gss on relatively large files.
    """
    benchmark.benchmark_all(GENFILE_NAME, 100000, 1000,
                            [1, 3, 5, 7, 12, 20, 35, 50, 111, 555, 777, 10000])

def test_all():
    """Runs all testing utilities.
    """
    test_small()
    test_medium()
    test_large()

if __name__ == '__main__':
    test_all()
