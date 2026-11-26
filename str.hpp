#ifndef STR_HPP
#define STR_HPP

#include <cstddef>
#include <cstring>
#include <vector>

class str {
private:
    std::size_t size_;
    char *data_;

    explicit str(std::size_t size)
        : size_(size), data_(new char[size + 1]) {
        data_[size_] = '\0';
    }

public:
    str() : str(std::size_t(0)) {}

    str(const char &c) : str(std::size_t(1)) {
        data_[0] = c;
    }

    str(const char *s) : str(std::strlen(s)) {
        std::memcpy(data_, s, size_);
    }

    str(const str &other) : str(other.size_) {
        std::memcpy(data_, other.data_, size_);
    }

    str &operator=(const str &other) {
        if (this != &other) {
            char *replacement = new char[other.size_ + 1];
            std::memcpy(replacement, other.data_, other.size_ + 1);
            delete[] data_;
            data_ = replacement;
            size_ = other.size_;
        }
        return *this;
    }

    str &operator=(const char *s) {
        // Copy before releasing storage, since s may point into this string.
        const std::size_t size = std::strlen(s);
        char *replacement = new char[size + 1];
        std::memcpy(replacement, s, size + 1);
        delete[] data_;
        data_ = replacement;
        size_ = size;
        return *this;
    }

    char &operator[](std::size_t pos) { return data_[pos]; }
    const char &operator[](std::size_t pos) const { return data_[pos]; }

    std::size_t len() const { return size_; }

    str join(const std::vector<str> &strs) const {
        if (strs.empty()) return str();
        std::size_t total = (strs.size() - 1) * size_;
        for (const str &part : strs) total += part.size_;

        str result(total);
        std::size_t offset = 0;
        for (std::size_t i = 0; i < strs.size(); ++i) {
            if (i != 0) {
                std::memcpy(result.data_ + offset, data_, size_);
                offset += size_;
            }
            std::memcpy(result.data_ + offset, strs[i].data_, strs[i].size_);
            offset += strs[i].size_;
        }
        return result;
    }

    str slice(std::size_t l, std::size_t r) const {
        str result(r - l);
        std::memcpy(result.data_, data_ + l, r - l);
        return result;
    }

    ~str() { delete[] data_; }
};

#endif
