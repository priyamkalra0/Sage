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
    MetaData_SaveTypeHash = 0xa3db7114, // unknown

    // Capacity
    PlayerStatus_MaxLife = murmurhash3::hash("PlayerStatus.MaxLife"), // u32
    PlayerStatus_MaxStamina = murmurhash3::hash("PlayerStatus.MaxStamina"), // float
    Pouch_Weapon_ValidNum = murmurhash3::hash("Pouch.Weapon.ValidNum"), // u32[]
    Pouch_Bow_ValidNum = murmurhash3::hash("Pouch.Bow.ValidNum"), // u32[]
    Pouch_Shield_ValidNum = murmurhash3::hash("Pouch.Shield.ValidNum"), // u32[]

    // Player Position
    PlayerStatus_SavePos = murmurhash3::hash("PlayerStatus.SavePos"), // vec3f*

    // Status
    PlayerStatus_CurrentRupee = murmurhash3::hash("PlayerStatus.CurrentRupee"), // u32
    PlayerStatus_Life = murmurhash3::hash("PlayerStatus.Life"), // u32
    Playtime = murmurhash3::hash("Playtime"), // u32
    PlayerStatus_MaxEnergy = murmurhash3::hash("PlayerStatus.MaxEnergy"), // float
    HorseInnMemberPoint = murmurhash3::hash("HorseInnMemberPoint"), // u32

    // Map Data
    MapData_IconData_StampData_Type = murmurhash3::hash("MapData.IconData.StampData.Type"), // enum
    MapData_IconData_StampData_Pos = murmurhash3::hash("MapData.IconData.StampData.Pos"), // enum
    MapData_IconData_StampData_Layer = murmurhash3::hash("MapData.IconData.StampData.Layer"), // enum

    // Other
    Sequence_CurrentBanc = murmurhash3::hash("Sequence.CurrentBanc"), // string*

    /* caption.sav */
    CaptionData_SaveTypeHash = 0x26f3523b, // unknown

    CaptionData_ScreenShot = murmurhash3::hash("CaptionData.ScreenShot"), // byte[]
    CaptionData_IsAutoSave = murmurhash3::hash("CaptionData.IsAutoSave"), // bool
    CaptionData_IsClear = murmurhash3::hash("CaptionData.IsClear"), // bool
    CaptionData_IsEnableUseAmiibo = murmurhash3::hash("CaptionData.IsEnableUseAmiibo"), // bool
    CaptionData_IsTitleMuralEnable = murmurhash3::hash("CaptionData.IsTitleMuralEnable"), // bool

    CaptionData_Date_Second = murmurhash3::hash("CaptionData.Date.Second"), // u32
    CaptionData_Date_Minute = murmurhash3::hash("CaptionData.Date.Minute"), // u32
    CaptionData_Date_Hour = murmurhash3::hash("CaptionData.Date.Hour"), // u32
    CaptionData_Date_Day = murmurhash3::hash("CaptionData.Date.Day"), // u32
    CaptionData_Date_Month = murmurhash3::hash("CaptionData.Date.Month"), // u32
    CaptionData_Date_Year = murmurhash3::hash("CaptionData.Date.Year"), // u32
};

enum class HashType : bool
{
    Value,
    Reference
};

inline std::unordered_map<Hash, HashType> Hashes
{
    { Hash::MetaData_SaveTypeHash, HashType::Value },

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

    { Hash::CaptionData_SaveTypeHash, HashType::Value },

    { Hash::CaptionData_ScreenShot, HashType::Reference },
    { Hash::CaptionData_IsAutoSave, HashType::Value },
    { Hash::CaptionData_IsClear, HashType::Value },
    { Hash::CaptionData_IsEnableUseAmiibo, HashType::Value },
    { Hash::CaptionData_IsTitleMuralEnable, HashType::Value },

    { Hash::CaptionData_Date_Second, HashType::Value },
    { Hash::CaptionData_Date_Minute, HashType::Value },
    { Hash::CaptionData_Date_Hour, HashType::Value },
    { Hash::CaptionData_Date_Day, HashType::Value },
    { Hash::CaptionData_Date_Month, HashType::Value },
    { Hash::CaptionData_Date_Year, HashType::Value },
};