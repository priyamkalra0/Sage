#pragma once

#include <string>
#include <vector>
#include <string_view>
#include <unordered_map>
#include "Filesystem.hpp"
#include "MurmurHash.hpp"
#include "Types.hpp"

class Sav
{
public:
    explicit Sav(std::string const& path) {
        read_all_bytes(path, m_data);
        populate_offsets(m_offsets);
    };

    /* Get reference to value by name (uses cached offset) */
    template <typename T>
    T& get(std::string_view const& name)
    {
        return get<T>(m_offsets.at(name));
    }

    /* Get array by name (uses cached offset) */
    template <typename T>
    T* array(std::string_view const& name)
    {
        return array<T>(m_offsets.at(name));
    }

    /* Get a view to a string by name (uses cached offset) */
    std::string_view string(std::string_view const& name)
    {
        return string(m_offsets.at(name));
    }

    /* Get array at any offset */
    template <typename T>
    T* array(u32 const offset)
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

    void populate_offsets(std::unordered_map<std::string_view, u32>& out) {
        for (u32 offset = 0x00; offset < m_data.size(); offset += 0x08)
        {
            u32 hash = get<u32>(offset);
            u32 const value_offset = offset + sizeof(u32);

            /* Hashtable ends at MetaData.SaveTypeHash
             * See: https://github.com/marcrobledo/savegame-editors/blob/b65dc1ecf655ba4f5f8bb74d4a7d402fc375fbf1/zelda-totk/zelda-totk.variables.js#L757
             */
            if (hash == 0xa3db7114) break;
            if (!Hashes.count(hash)) continue;

            auto const& name = Hashes.at(hash);
            if (name.back() == '*') { // is reference
                auto const& actual_name = name.substr(0, name.size() - 1);
                out[actual_name] = get<u32>(value_offset);
            } else { // is value
                out[name] = value_offset;
            }

            /* Some offsets need to be manually shifted */
            /* i.e I do not know a better way to do this */
            if (name == "LocationMarker") out[name] += 0x30;
        }
    };

    std::vector<u8> m_data;
    std::unordered_map<std::string_view, u32> m_offsets;
};