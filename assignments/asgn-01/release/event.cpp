// Name: Kiarash Nikpour
// Seneca Email: knikpour@myseneca.ca
// Seneca Student ID: 140371246
// Date: 2026-10-02
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my assignments. This
// submitted piece of work has not been shared with any other student or 3rd
// party content provider.

#include "event.h"
#include "settings.h"
#include <iomanip>

namespace seneca {
Event::Event(const char *name, const std::chrono::nanoseconds &duration)
    : m_name(name), m_duration(duration) {}

std::ostream &operator<<(std::ostream &out, const Event &e) {
  static int counter = 0;
  ++counter;

  long long durationVal = 0;
  int fieldWidth = 11;
  std::string units = seneca::g_settings.m_time_units;

  if (units == "seconds") {
    durationVal =
        std::chrono::duration_cast<std::chrono::seconds>(e.m_duration).count();
    fieldWidth = 2;
  } else if (units == "milliseconds") {
    durationVal =
        std::chrono::duration_cast<std::chrono::milliseconds>(e.m_duration)
            .count();
    fieldWidth = 5;
  } else if (units == "microseconds") {
    durationVal =
        std::chrono::duration_cast<std::chrono::microseconds>(e.m_duration)
            .count();
    fieldWidth = 8;
  } else {
    durationVal = e.m_duration.count();
    fieldWidth = 11;
  }

  out << std::setw(2) << std::right << counter << ": " << std::setw(40)
      << std::right << e.m_name << " -> " << std::setw(fieldWidth) << std::right
      << durationVal << " " << units;

  return out;
}
} // namespace seneca
