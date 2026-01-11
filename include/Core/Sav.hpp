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

    /* Get reference to value by name (uses cached offset) */
    template <typename T>
    T& get(std::string_view const& name)
    {
        return get<T>(m_offsets.at(name));
    }

    /* Get reference to value at any offset */
    template <typename T>
    T& get(u32 const offset)
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