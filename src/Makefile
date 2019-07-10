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

CC=g++
CFLAGS=-Wall -Wpedantic

all: kmp.o rabin_karp.o

kmp.o: kmp.h kmp.cc
	$(CC) $(CFLAGS) -c kmp.cc

rabin_karp.o: rabin_karp.h rabin_karp.cc
	$(CC) $(CFLAGS) -c rabin_karp.cc
