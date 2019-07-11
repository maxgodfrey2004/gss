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

"""Generates a file containing random dna strings for gss benchmarking.
"""

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import random

ALPHABET = 'ACGT'

try:
    range = xrange  # pylint: disable=redefined-builtin, invalid-name
except NameError:
    pass

def random_string(columns):
    """Returns a random string from the specified alphabet of a certain length.
    """
    return ''.join([random.choice(ALPHABET) for _ in range(columns)])

def generate_file(filename, lines, columns):
    """Creates and propogates a file containing random dna strings.

    This file can in turn be used for gss benchmarking.

    Args:
      - filename: The name of the file to the written.
      - lines: The number of lines to be written to the file.
      - columns: The width of each line to be written to the file.
    """

    with open(filename, 'w+') as outfile:
        for _ in range(lines):
            line = random_string(columns)
            outfile.write(line + '\n')
        outfile.close()

def main():
    """Main logic for the test generator.
    """
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('outfile', type=str,
                        help='The name of the file to be produced.')
    parser.add_argument('lines', type=int,
                        help='The number of lines to write to the outfile.')
    parser.add_argument('columns', type=int,
                        help='The length of each line in the outfile.')
    args = parser.parse_args()
    if args.lines <= 0:
        parser.error('lines must be a positive integer.')
    if args.columns <= 0:
        parser.error('columns must be a positive integer.')

    generate_file(args.outfile, args.lines, args.columns)

if __name__ == '__main__':
    main()
