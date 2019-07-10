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
CFLAGS := -Wall -Wextra -Wpedantic -std=c++11

SRCDIR := src

CC=g++
CFLAGS=-Wall -Wpedantic

all: gss

gss: main.h main.cc $(SRCDIR)/kmp.o $(SRCDIR)/rabin_karp.o
	$(CC) $(CFLAGS) -o gss main.cc kmp.o rabin_karp.o

$(SRCDIR)/kmp.o: $(SRCDIR)/kmp.h $(SRCDIR)/kmp.cc
	$(CC) $(CFLAGS) -c $(SRCDIR)/kmp.cc

$(SRCDIR)/rabin_karp.o: $(SRCDIR)/rabin_karp.h $(SRCDIR)/rabin_karp.cc
	$(CC) $(CFLAGS) -c $(SRCDIR)/rabin_karp.cc

.PHONY: clean

clean:
	rm *.o
	rm gss
