#pragma once

#include <unordered_map>

#include "Core/MurmurHash3.hpp"
#include "Types.hpp"

/*
 * Murmur3 hashes for the interesting game data in the .sav files
 * See:
 * https://github.com/marcrobledo/savegame-editors/blob/b65dc1ecf655ba4f5f8bb74d4a7d402fc375fbf1/zelda-totk/zelda-totk.js#L28
 * https://raw.githubusercontent.com/McSpazzy/totk-gamedata/refs/heads/master/GameDataList.Product.110.json
 * https://raw.githubusercontent.com/MrCheeze/totk-tools/refs/heads/master/gamedata_hashes.txt
*/
enum class Hash : u32
{
    /* progress.sav */

    // Capacities
    PlayerStatus_MaxLife = murmurhash3::hash("PlayerStatus.MaxLife"), // i32
    PlayerStatus_MaxStamina = murmurhash3::hash("PlayerStatus.MaxStamina"), // float
    Pouch_Weapon_ValidNum = murmurhash3::hash("Pouch.Weapon.ValidNum"), // i32[]
    Pouch_Bow_ValidNum = murmurhash3::hash("Pouch.Bow.ValidNum"), // i32[]
    Pouch_Shield_ValidNum = murmurhash3::hash("Pouch.Shield.ValidNum"), // i32[]

    // Player Coordinates
    PlayerStatus_SavePos = murmurhash3::hash("PlayerStatus.SavePos"), // vec3f*

    // Current Statistics
    PlayerStatus_CurrentRupee = murmurhash3::hash("PlayerStatus.CurrentRupee"), // i32
    PlayerStatus_Life = murmurhash3::hash("PlayerStatus.Life"), // i32
    Playtime = murmurhash3::hash("Playtime"), // i32
    PlayerStatus_MaxEnergy = murmurhash3::hash("PlayerStatus.MaxEnergy"), // float
    HorseInnMemberPoint = murmurhash3::hash("HorseInnMemberPoint"), // i32

    // Map data
    MapData_IconData_StampData_Type = murmurhash3::hash("MapData.IconData.StampData.Type"),
    MapData_IconData_StampData_Pos = murmurhash3::hash("MapData.IconData.StampData.Pos"),
    MapData_IconData_StampData_Layer = murmurhash3::hash("MapData.IconData.StampData.Layer"),

    Sequence_CurrentBanc = murmurhash3::hash("Sequence.CurrentBanc"), // string*

    /* caption.sav */
    LocationMarker = 0x26f3523b, // string
    PreviewImage = 0x63696a32 // byte[]
};

enum class HashType : bool
{
    Value,
    Reference
};

inline std::unordered_map<Hash, HashType> Hashes
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