// Name: Kiarash Nikpour
// Seneca Email: knikpour@myseneca.ca
// Seneca Student ID: 140371246
// Date: 2026-10-02
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my assignments. This
// submitted piece of work has not been shared with any other student or 3rd
// party content provider.

#include "dictionary.h"
#include "settings.h"
#include <fstream>
#include <iostream>
#include <string>

namespace seneca {
static PartOfSpeech parsePOS(const std::string &pos) {
  if (pos == "n." || pos == "n. pl.")
    return PartOfSpeech::Noun;
  if (pos == "adv.")
    return PartOfSpeech::Adverb;
  if (pos == "a.")
    return PartOfSpeech::Adjective;
  if (pos == "v." || pos == "v. i." || pos == "v. t." || pos == "v. t. & i.")
    return PartOfSpeech::Verb;
  if (pos == "prep.")
    return PartOfSpeech::Preposition;
  if (pos == "pron.")
    return PartOfSpeech::Pronoun;
  if (pos == "conj.")
    return PartOfSpeech::Conjunction;
  if (pos == "interj.")
    return PartOfSpeech::Interjection;
  return PartOfSpeech::Unknown;
}

static const char *posToString(PartOfSpeech pos) {
  switch (pos) {
  case PartOfSpeech::Noun:
    return "noun";
  case PartOfSpeech::Pronoun:
    return "pronoun";
  case PartOfSpeech::Adjective:
    return "adjective";
  case PartOfSpeech::Adverb:
    return "adverb";
  case PartOfSpeech::Verb:
    return "verb";
  case PartOfSpeech::Preposition:
    return "preposition";
  case PartOfSpeech::Conjunction:
    return "conjunction";
  case PartOfSpeech::Interjection:
    return "interjection";
  default:
    return "";
  }
}

Dictionary::Dictionary(const char *filename) {
  std::ifstream file(filename);
  if (!file) {
    m_words = nullptr;
    m_count = 0;
    return;
  }

  size_t lineCount = 0;
  std::string line;
  while (std::getline(file, line))
    ++lineCount;

  if (lineCount == 0)
    return;

  m_words = new Word[lineCount];

  file.clear();
  file.seekg(0);

  size_t idx = 0;
  while (std::getline(file, line) && idx < lineCount) {
    if (line.empty())
      continue;
    std::string word, pos, definition;

    size_t first = line.find(',');
    if (first == std::string::npos)
      continue;

    size_t second = line.find(',', first + 1);
    if (second == std::string::npos)
      continue;

    word = line.substr(0, first);
    pos = line.substr(first + 1, second - first - 1);
    definition = line.substr(second + 1);

    m_words[idx].m_word = word;
    m_words[idx].m_definition = definition;
    m_words[idx].m_pos = parsePOS(pos);
    ++idx;
  }
  m_count = idx;
}

Dictionary::~Dictionary() {
  delete[] m_words;
  m_words = nullptr;
  m_count = 0;
}

Dictionary::Dictionary(const Dictionary &other) : m_count(other.m_count) {
  if (other.m_words && other.m_count > 0) {
    m_words = new Word[m_count];
    for (size_t i = 0; i < m_count; ++i)
      m_words[i] = other.m_words[i];
  } else {
    m_words = nullptr;
    m_count = 0;
  }
}

Dictionary &Dictionary::operator=(const Dictionary &other) {
  if (this != &other) {
    delete[] m_words;
    m_count = other.m_count;
    if (other.m_words && other.m_count > 0) {
      m_words = new Word[m_count];
      for (size_t i = 0; i < m_count; ++i)
        m_words[i] = other.m_words[i];
    } else {
      m_words = nullptr;
      m_count = 0;
    }
  }
  return *this;
}

Dictionary::Dictionary(Dictionary &&other) noexcept
    : m_words(other.m_words), m_count(other.m_count) {
  other.m_words = nullptr;
  other.m_count = 0;
}

Dictionary &Dictionary::operator=(Dictionary &&other) noexcept {
  if (this != &other) {
    delete[] m_words;
    m_words = other.m_words;
    m_count = other.m_count;
    other.m_words = nullptr;
    other.m_count = 0;
  }
  return *this;
}

void Dictionary::searchWord(const char *word) {
  bool found = false;
  bool firstMatch = true;
  std::string wordStr(word);

  for (size_t i = 0; i < m_count; ++i) {
    if (m_words[i].m_word == wordStr) {
      found = true;

      std::string prefix;
      if (firstMatch)
        prefix = wordStr;
      else
        prefix = std::string(wordStr.size(), ' ');

      std::cout << prefix << " - ";

      if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown)
        std::cout << "(" << posToString(m_words[i].m_pos) << ") ";

      std::cout << m_words[i].m_definition << '\n';

      firstMatch = false;

      if (!g_settings.m_show_all)
        return;
    }
  }

  if (!found)
    std::cout << "Word '" << word << "' was not found in the dictionary.\n";
}
} // namespace seneca
