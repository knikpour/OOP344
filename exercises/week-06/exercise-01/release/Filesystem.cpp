#include <fstream>
#include <stdexcept>
#include <utility>
#include "Filesystem.h"
#include "File.h"

namespace seneca {
    static std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) {
            return "";
        }
        size_t end = str.find_last_not_of(" \t\r\n");
        return str.substr(start, end - start + 1);
    }

    Filesystem::Filesystem(const std::string& filename, const std::string& rootName) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        m_root = new Directory(rootName);
        m_current = m_root;

        try {
            std::string line;
            while (std::getline(file, line)) {
                line = trim(line);
                if (line.empty()) {
                    continue;
                }

                bool is_file = false;
                std::string path_part;
                std::string contents_part;

                size_t pipe_pos = line.find('|');
                if (pipe_pos != std::string::npos) {
                    is_file = true;
                    path_part = trim(line.substr(0, pipe_pos));
                    contents_part = trim(line.substr(pipe_pos + 1));
                } else {
                    path_part = trim(line);
                }

                Directory* curr = m_root;
                size_t start = 0;
                size_t slash_pos = path_part.find('/', start);
                while (slash_pos != std::string::npos) {
                    std::string dir_name = path_part.substr(start, slash_pos - start + 1);
                    Resource* found = curr->find(dir_name);
                    if (found) {
                        curr = dynamic_cast<Directory*>(found);
                    } else {
                        Directory* new_dir = new Directory(dir_name);
                        *curr += new_dir;
                        curr = new_dir;
                    }
                    start = slash_pos + 1;
                    slash_pos = path_part.find('/', start);
                }

                if (is_file && start < path_part.length()) {
                    std::string file_name = path_part.substr(start);
                    File* new_file = new File(file_name, contents_part);
                    *curr += new_file;
                }
            }
        } catch (...) {
            delete m_root;
            m_root = nullptr;
            m_current = nullptr;
            throw;
        }
    }

    Filesystem::Filesystem(Filesystem&& other) noexcept
        : m_root(other.m_root), m_current(other.m_current) {
        other.m_root = nullptr;
        other.m_current = nullptr;
    }

    Filesystem& Filesystem::operator=(Filesystem&& other) noexcept {
        if (this != &other) {
            delete m_root;
            m_root = other.m_root;
            m_current = other.m_current;
            other.m_root = nullptr;
            other.m_current = nullptr;
        }
        return *this;
    }

    Filesystem::~Filesystem() {
        delete m_root;
    }

    Filesystem& Filesystem::operator+=(Resource* res) {
        if (m_current) {
            *m_current += res;
        }
        return *this;
    }

    Directory* Filesystem::change_directory(const std::string& name) {
        if (name.empty()) {
            m_current = m_root;
            return m_current;
        }
        Resource* found = m_current->find(name);
        if (!found || found->type() != NodeType::DIR) {
            throw std::invalid_argument("Cannot change directory! " + name + " not found!");
        }
        m_current = dynamic_cast<Directory*>(found);
        return m_current;
    }

    Directory* Filesystem::get_current_directory() const {
        return m_current;
    }
}
