#pragma once

#include <unordered_map>
#include "Types.hpp"

/*
 * Pre-computed Murmur3 hashes for the interesting variables in the .sav files
 * See: https://github.com/marcrobledo/savegame-editors/blob/b65dc1ecf655ba4f5f8bb74d4a7d402fc375fbf1/zelda-totk/zelda-totk.js#L28
 */

enum class Hash : u32
{
    /* progress.sav */

    // Capacities
    PlayerStatus_MaxLife = 0xfbe01da1, // i32
    PlayerStatus_MaxStamina = 0xf9212c74, // float
    Pouch_Weapon_ValidNum = 0xd7a3f6ba, // i32[]
    Pouch_Bow_ValidNum = 0xc61785c2, // i32[]
    Pouch_Shield_ValidNum = 0x05271e7d, // i32[]

    // Player Coordinates
    PlayerStatus_SavePos = 0xc884818d, // vec3f*

    // Current Statistics
    PlayerStatus_CurrentRupee = 0xa77921d7, // i32
    PlayerStatus_Life = 0x31ab5580, // i32
    Playtime = 0xe573f564, // i32
    PlayerStatus_MaxEnergy = 0xafd01d68, // float
    HorseInnMemberPoint = 0x15ec5858, // i32

    // Map data
    MapData_IconData_StampData_Type = 0x14d7f4c4,
    MapData_IconData_StampData_Pos = 0xf24fc2e7,
    MapData_IconData_StampData_Layer = 0xd2025694,

    Sequence_CurrentBanc = 0x1d6189da, // string*

    /* caption.sav */

    LocationMarker = 0x26f3523b, // string
    PreviewImage = 0x63696a32 // byte[]
};

enum class HashType : bool
{
    Value,
    Reference
};

inline std::unordered_map<Hash, HashType> const Hashes
{
    { Hash::PlayerStatus_MaxLife, HashType::Value },
    { Hash::PlayerStatus_MaxStamina, HashType::Value },
    { Hash::Pouch_Weapon_ValidNum, HashType::Reference },
    { Hash::Pouch_Bow_ValidNum, HashType::Reference },
    { Hash::Pouch_Shield_ValidNum, HashType::Reference },

    { Hash::PlayerStatus_SavePos, HashType::Reference },

    { Hash::PlayerStatus_CurrentRupee, HashType::Value },
    { Hash::PlayerStatus_Life, HashType::Value },
    { Hash::Playtime, HashType::Value },
    { Hash::PlayerStatus_MaxEnergy, HashType::Value },
    { Hash::HorseInnMemberPoint, HashType::Value },

    { Hash::MapData_IconData_StampData_Type, HashType::Reference },
    { Hash::MapData_IconData_StampData_Pos, HashType::Reference },
    { Hash::MapData_IconData_StampData_Layer, HashType::Reference },

    { Hash::Sequence_CurrentBanc, HashType::Reference },

    { Hash::LocationMarker, HashType::Value },
    { Hash::PreviewImage, HashType::Reference }
};
