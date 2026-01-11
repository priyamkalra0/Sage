#pragma once

#include <string>
#include <vector>
#include <fstream>

/* See: https://gist.github.com/matthewjberger/0b6760de2ed41436a19235cfbe1b2d31 */
inline void read_all_bytes(std::string const& path, std::vector<unsigned char>& out)
{
    std::ifstream file { path, std::ios::binary | std::ios::ate };
    file >> std::noskipws;

    auto const file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    out.reserve(file_size);

    std::copy(
        std::istream_iterator<unsigned char>(file),
        std::istream_iterator<unsigned char>(),
        std::back_inserter(out)
    );
}

inline void write_all_bytes(const std::string& path, unsigned char const* data, unsigned int const size) {
    std::ofstream stream { path, std::ios::out | std::ios::binary | std::ios::trunc };
    stream.write(reinterpret_cast<char const*>(data), size);
    stream.close();
}

inline void write_all_bytes(std::string const& path, std::span<unsigned char const> const& data)
{
    write_all_bytes(path, data.data(), data.size());
}