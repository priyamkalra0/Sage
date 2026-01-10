#pragma once

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