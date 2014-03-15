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
  void format_log_msg(int level, std::string *msg) const;
  void format_log_msg(std::string level, std::string *msg) const;
  virtual void output_msg(std::string msg);

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
  this->format_log_msg("LVL", msg);
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
