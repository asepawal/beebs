# Makefile.am for BEEBS CRC32 test
#
# Copyright (C) 2013 Embecosm Limited and University of Bristol
#
# Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

# SPDX-License-Identifier: GPL-3.0-or-later

if ENABLED_BENCHMARK_CRC32

include $(top_srcdir)/src/common.mk.am

bin_PROGRAMS        = crc32
noinst_LTLIBRARIES  = libcrc32.la

crc32_SOURCES       =

libcrc32_la_SOURCES = crc_32.c

crc32_LDADD         = $(DUMMY_CRT0) \
                      $(top_builddir)/support/libsupport.la \
                      libcrc32.la \
                      $(DUMMY_LIBC) $(DUMMY_LIBGCC) $(DUMMY_COMPILERRT)

endif
