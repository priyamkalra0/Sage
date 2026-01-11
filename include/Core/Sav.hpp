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
    explicit Sav(std::string const& path)
    {
        read_all_bytes(path, m_data);
        populate_offsets(m_offsets);
    };

    void dump(std::string const& path) const
    {
        write_all_bytes(path, m_data);
    }

    /* Get reference to value by hash (uses cached offset) */
    template <typename T>
    T& get(Hash const& hash)
    {
        return get<T>(m_offsets.at(hash));
    }

    /* Get array by hash (uses cached offset) */
    template <typename T>
    T* array(Hash const& hash)
    {
        return array<T>(m_offsets.at(hash));
    }

    /* Get a view to a string by hash (uses cached offset) */
    std::string_view string(Hash const& hash)
    {
        return string(m_offsets.at(hash));
    }

    /* Get reference to value at any offset */
    template <typename T>
    T& get(u32 const offset)
    {
        return *get_address<T>(offset);
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

    /* Get a view to a string at any offset */
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

    void populate_offsets(std::unordered_map<Hash, u32>& out)
    {
        for (u32 offset = 0x00; offset < m_data.size(); offset += 0x08)
        {
            auto hash = get<Hash>(offset);
            u32 value_offset = offset + sizeof(u32);

            /* Hashtable ends at MetaData.SaveTypeHash
             * See: https://github.com/marcrobledo/savegame-editors/blob/b65dc1ecf655ba4f5f8bb74d4a7d402fc375fbf1/zelda-totk/zelda-totk.variables.js#L757
             */
            if (hash == Hash{0xa3db7114}) break;
            if (!Hashes.count(hash)) continue;

            auto const type = Hashes.at(hash);
            if (type == HashType::Reference) // value at offset is a reference (pointer)
                value_offset = get<u32>(value_offset);

            out[hash] = value_offset;


            /* Some offsets need to be manually shifted */
            /* i.e I do not know a better way to do this */
            if (hash == Hash::LocationMarker) out[hash] += 0x30;
        }
    };

    std::vector<u8> m_data;
    std::unordered_map<Hash, u32> m_offsets;
};