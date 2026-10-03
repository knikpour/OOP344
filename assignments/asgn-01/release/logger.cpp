// Name: Kiarash Nikpour
// Seneca Email: knikpour@myseneca.ca
// Seneca Student ID: 140371246
// Date: 2026-10-02
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my assignments. This
// submitted piece of work has not been shared with any other student or 3rd
// party content provider.

#include "logger.h"
#include <utility>

namespace seneca {
Logger::~Logger() {
  delete[] m_events;
  m_events = nullptr;
  m_count = 0;
}

Logger::Logger(Logger &&other) noexcept
    : m_events(other.m_events), m_count(other.m_count) {
  other.m_events = nullptr;
  other.m_count = 0;
}

Logger &Logger::operator=(Logger &&other) noexcept {
  if (this != &other) {
    delete[] m_events;
    m_events = other.m_events;
    m_count = other.m_count;
    other.m_events = nullptr;
    other.m_count = 0;
  }
  return *this;
}

void Logger::addEvent(const Event &event) {
  Event *newArr = new Event[m_count + 1];
  for (size_t i = 0; i < m_count; ++i)
    newArr[i] = m_events[i];
  newArr[m_count] = event;

  delete[] m_events;
  m_events = newArr;
  ++m_count;
}

std::ostream &operator<<(std::ostream &out, const Logger &logger) {
  for (size_t i = 0; i < logger.m_count; ++i)
    out << logger.m_events[i] << '\n';
  return out;
}
} // namespace seneca
