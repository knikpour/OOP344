// Name: Kiarash Nikpour
// Seneca Email: knikpour@myseneca.ca
// Seneca Student ID: 140371246
// Date: 2026-10-02
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my assignments. This
// submitted piece of work has not been shared with any other student or 3rd
// party content provider.

#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include "event.h"
#include <iostream>

namespace seneca {
class Logger {
  Event *m_events = nullptr;
  size_t m_count = 0;

public:
  Logger() = default;

  ~Logger();

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  Logger(Logger &&other) noexcept;
  Logger &operator=(Logger &&other) noexcept;

  void addEvent(const Event &event);

  friend std::ostream &operator<<(std::ostream &out, const Logger &logger);
};
} // namespace seneca

#endif // SENECA_LOGGER_H
