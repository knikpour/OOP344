#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include <string>
#include "Directory.h"

namespace seneca {
    class Filesystem {
        Directory* m_root{nullptr};
        Directory* m_current{nullptr};

    public:
        Filesystem(const std::string& filename, const std::string& rootName = "");
        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;
        Filesystem(Filesystem&& other) noexcept;
        Filesystem& operator=(Filesystem&& other) noexcept;
        ~Filesystem();

        Filesystem& operator+=(Resource* res);
        Directory* change_directory(const std::string& name = "");
        Directory* get_current_directory() const;
    };
}

#endif
