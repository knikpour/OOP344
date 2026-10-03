// Name: Kiarash Nikpour
// Seneca Email: knikpour@myseneca.ca
// Seneca Student ID: 140371246
// Date: 2026-10-02
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my assignments. This
// submitted piece of work has not been shared with any other student or 3rd
// party content provider.

#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H
#include <string>

namespace seneca {
enum class PartOfSpeech {
  Unknown,
  Noun,
  Pronoun,
  Adjective,
  Adverb,
  Verb,
  Preposition,
  Conjunction,
  Interjection,
};

struct Word {
  std::string m_word{};
  std::string m_definition{};
  PartOfSpeech m_pos = PartOfSpeech::Unknown;
};

class Dictionary {
  Word *m_words = nullptr;
  size_t m_count = 0;

public:
  Dictionary() = default;

  Dictionary(const char *filename);

  ~Dictionary();

  Dictionary(const Dictionary &other);

  Dictionary &operator=(const Dictionary &other);

  Dictionary(Dictionary &&other) noexcept;

  Dictionary &operator=(Dictionary &&other) noexcept;

  void searchWord(const char *word);
};
} // namespace seneca

#endif // SENECA_DICTIONARY_H
