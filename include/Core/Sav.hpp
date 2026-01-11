#pragma once

#include <string>
#include <vector>
#include <string_view>
#include <unordered_map>
#include "Types.hpp"

class Sav
{
public:
    explicit Sav(std::string const& path);

    /* Read value from cached offset */
    template <typename T>
    T read(std::string_view const& name)
    {
        return read<T>(m_offsets.at(name));
    }

    /* Read value from any offset */
    template <typename T>
    T read(u32 const offset)
    {
        return *get_address<T>(offset);
    }

private:
    template <typename T>
    T* get_address(u32 const offset)
    {
        return reinterpret_cast<T*>(&m_data[0] + offset);
    }

    void populate_offsets(std::unordered_map<std::string_view, u32>& out);

    std::vector<u8> m_data;
    std::unordered_map<std::string_view, u32> m_offsets;
};