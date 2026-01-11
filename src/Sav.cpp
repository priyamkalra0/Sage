#include <string>
#include "Core/Sav.hpp"
#include "Core/MurmurHash.hpp"
#include "Filesystem.hpp"

Sav::Sav(std::string const& path)
{
    read_all_bytes(path, m_data);
    populate_offsets(m_offsets);
}

void Sav::populate_offsets(std::unordered_map<std::string_view, u32>& out)
{
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
}
