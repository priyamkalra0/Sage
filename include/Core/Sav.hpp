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

    /* Get array by name (uses cached offset) */
    template <typename T>
    T* get_array(std::string_view const& name)
    {
        return get_array<T>(m_offsets.at(name));
    }

    /* Get a view to a string by name (uses cached offset) */
    std::string_view string(std::string_view const& name)
    {
        return string(m_offsets.at(name));
    }

    /* Get array at any offset */
    template <typename T>
    T* get_array(u32 const offset)
    {
        return get_address<T>(
            offset
            + sizeof(u32) // The first integer is the size of the array
        );
    }

    /* Get reference to value at any offset */
    template <typename T>
    T& get(u32 const offset)
    {
        return *get_address<T>(offset);
    }

    /* Get a view to a string at any offset (uses cached offset) */
    std::string_view string(u32 const offset)
    {
        return { get_address<char>(offset) };
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