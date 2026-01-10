#pragma once

#include <string>
#include <vector>
#include "Types.hpp"

class Sav
{
public:
    explicit Sav(std::string const& path);

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

    std::vector<u8> m_data;
};