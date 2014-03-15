/*
 * This is part of ulog, a small and thread-safe C++ logging library.
 *
 * Copyright 2014 Mostafa Razavi <mostafa@sepent.com>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ulog.hh"

int main(int argc, char *argv[]) {
  ulog::ulog<> logger;

  logger.log(1, "hi");

  return 0;
}
