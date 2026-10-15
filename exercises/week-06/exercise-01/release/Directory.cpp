#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include "Directory.h"

namespace seneca {
    Directory::Directory(const std::string& name) {
        m_name = name;
    }

    Directory::~Directory() {
        for (auto res : m_contents) {
            delete res;
        }
    }

    void Directory::update_parent_path(const std::string& path) {
        m_parent_path = path;
        for (auto res : m_contents) {
            res->update_parent_path(this->path());
        }
    }

    NodeType Directory::type() const {
        return NodeType::DIR;
    }

    std::string Directory::path() const {
        return m_parent_path + m_name;
    }

    std::string Directory::name() const {
        return m_name;
    }

    int Directory::count() const {
        return static_cast<int>(m_contents.size());
    }

    size_t Directory::size() const {
        size_t total = 0u;
        for (const auto res : m_contents) {
            total += res->size();
        }
        return total;
    }

    Directory& Directory::operator+=(Resource* res) {
        if (!res) {
            return *this;
        }
        for (const auto item : m_contents) {
            if (item->name() == res->name()) {
                throw std::runtime_error("Resource already exists with the same name.");
            }
        }
        m_contents.push_back(res);
        res->update_parent_path(this->path());
        return *this;
    }

    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {
        for (auto res : m_contents) {
            if (res->name() == name) {
                return res;
            }
        }
        bool recursive = false;
        for (auto flag : flags) {
            if (flag == OpFlags::RECURSIVE) {
                recursive = true;
                break;
            }
        }
        if (recursive) {
            for (auto res : m_contents) {
                if (res->type() == NodeType::DIR) {
                    Directory* dir = dynamic_cast<Directory*>(res);
                    if (dir) {
                        Resource* found = dir->find(name, flags);
                        if (found) {
                            return found;
                        }
                    }
                }
            }
        }
        return nullptr;
    }

    void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {
        auto it = std::find_if(m_contents.begin(), m_contents.end(), [&](Resource* res) {
            return res->name() == name;
        });
        if (it == m_contents.end()) {
            throw std::string(name + " does not exist in " + m_name);
        }
        if ((*it)->type() == NodeType::DIR) {
            bool recursive = false;
            for (auto flag : flags) {
                if (flag == OpFlags::RECURSIVE) {
                    recursive = true;
                    break;
                }
            }
            if (!recursive) {
                throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
            }
        }
        delete *it;
        m_contents.erase(it);
    }

    void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const {
        os << "Total size: " << size() << " bytes" << std::endl;
        bool isLong = false;
        for (auto flag : flags) {
            if (flag == FormatFlags::LONG) {
                isLong = true;
                break;
            }
        }
        for (const auto res : m_contents) {
            if (res->type() == NodeType::DIR) {
                os << "D | " << std::left << std::setw(15) << res->name() << " |";
                if (isLong) {
                    os << " " << std::right << std::setw(2) << res->count() << " | "
                       << std::right << std::setw(10) << (std::to_string(res->size()) + " bytes") << " | ";
                }
                os << std::endl;
            } else {
                os << "F | " << std::left << std::setw(15) << res->name() << " |";
                if (isLong) {
                    os << "    | "
                       << std::right << std::setw(10) << (std::to_string(res->size()) + " bytes") << " | ";
                }
                os << std::endl;
            }
        }
    }
}
