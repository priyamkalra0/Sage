#pragma once

#include <span>
#include <string>
#include <vector>
#include <string_view>
#include <unordered_map>
#include "Filesystem.hpp"
#include "Hash.hpp"
#include "HashArray.hpp"
#include "Types.hpp"

class Sav
{
public:
    explicit Sav(std::string const& path)
    {
        read_all_bytes(path, m_data);
        HashArray::load_all();
        populate_offsets(m_offsets);
    };

    void dump(std::string const& path) const
    {
        write_all_bytes(path, m_data);
    }

    /* Get reference to value by hash (uses cached offset) */
    template <typename T>
    T& get(Hash const hash)
    {
        return get<T>(m_offsets.at(hash));
    }

    /* Set value by hash (uses cached offset) */
    template <typename T>
    void set(Hash const hash, T const& v)
    {
        set<T>(m_offsets.at(hash), v);
    }

    /* Set multiple values using hash array (uses cached offsets) */
    template <typename T>
    void set(HashArray_t const& hashes, T const& v)
    {
        for (auto const h : hashes) set<T>(h, v);
    }

    /* Get array by hash (uses cached offset) */
    template <typename T>
    std::span<T> array(Hash const hash)
    {
        return array<T>(m_offsets.at(hash));
    }

    /* Get a view to a string by hash (uses cached offset) */
    std::string_view string(Hash const hash)
    {
        return string(m_offsets.at(hash));
    }

    /* Test a value by hash (uses cached offset) */
    template <typename T>
    bool test(Hash const hash, T const& v)
    {
        return test<T>(m_offsets.at(hash), v);
    }

    /* Test multiple values using hash array (uses cached offsets)
     * returns the number of matches */
    template <typename T>
    u32 test(HashArray_t const& hashes, T const& v)
    {
        u32 r = 0;
        for (auto const h : hashes)
            r += test(h, v);

        return r;
    }

    /* Get reference to value at any offset */
    template <typename T>
    T& get(u32 const offset)
    {
        return *get_address<T>(offset);
    }

    /* Set value at any offset */
    template <typename T>
    void set(u32 const offset, T const& v)
    {
        get<T>(offset) = v;
    }

    /* Get array at any offset */
    template <typename T>
    std::span<T> array(u32 const offset)
    {
        auto const size = get<u32>(offset);
        T* data = get_address<T>(offset + sizeof(u32));
        return {data, size};
    }

    /* Get a view to a string at any offset */
    std::string_view string(u32 const offset)
    {
        return { get_address<char>(offset) };
    }

    /* Test a value at any offset */
    template <typename T>
    bool test(u32 const offset, T const& v)
    {
        return { v == get<T>(offset) };
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
            if (hash == Hash::MetaData_SaveTypeHash) break;
            if (!Hashes.count(hash)) continue;

            auto const type = Hashes.at(hash);
            if (type == HashType::Reference) // value at offset is a reference (pointer)
                value_offset = get<u32>(value_offset);

            out[hash] = value_offset;
        }
    };

    std::vector<u8> m_data;
    std::unordered_map<Hash, u32> m_offsets;
};