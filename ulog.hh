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

#include <ctime>
#include <string>
#include <sstream>
#include <mutex>
#include <iostream>

namespace ulog {

template <bool Enabled=true, bool Locking=true>
class ulog {
protected:
  std::string date_format;
  std::ostream &output;
  std::mutex mutex;

  virtual void output_msg(std::string msg);
  void format_log_msg(std::string level, std::string *msg) const;

  // Override this method to customize log line formats.
  virtual void format_log_msg(int level, std::string *msg) const;

public:
  ulog(std::ostream &output=std::cout, std::string date_format="%a %Y/%m/%d %H:%M:%S");
  void log(int level, std::string msg);
};

template <bool Enabled, bool Locking>
ulog<Enabled, Locking>::ulog(std::ostream &output, std::string date_format) :
  output(output),
  date_format(date_format)
{
}

template <bool Enabled, bool Locking>
void ulog<Enabled, Locking>::log(int level, std::string msg) {
  this->format_log_msg(level, &msg);
  std::lock_guard<std::mutex> guard(this->mutex);
  this->output_msg(msg);
}

template <>
void ulog<true, false>::log(int level, std::string msg) {
  printf("log\n");
  this->format_log_msg(level, &msg);
  this->output_msg(msg);
}

template <>
void ulog<false, true>::log(int level, std::string msg) {
  // Logging is disabled. Do nothing.
}

template <>
void ulog<false, false>::log(int level, std::string msg) {
  // Logging is disabled. Do nothing.
}

template <bool Enabled, bool Locking>
void ulog<Enabled, Locking>::format_log_msg(int level, std::string *msg) const {
  std::string level_str;

  switch(level) {
  case 0: level_str = "DEBUG"; break;
  case 1: level_str = "INFO"; break;
  case 2: level_str = "WARNING"; break;
  case 3: level_str = "ERROR"; break;
  }

  this->format_log_msg(level_str, msg);
}

template <bool Enabled, bool Locking>
void ulog<Enabled, Locking>::format_log_msg(std::string level, std::string *msg) const {
  std::ostringstream out;

  char buffer[32];
  std::time_t now = time(0);
  std::tm *time = localtime(&now);
  strftime(buffer, sizeof(buffer), this->date_format.c_str(), time);

  out << "[" << level << "][" << buffer << "] " << *msg;
  *msg = out.str();
}

template <bool Enabled, bool Locking>
void ulog<Enabled, Locking>::output_msg(std::string msg) {
  this->output << msg << std::endl;
}

} // namespace ulog
