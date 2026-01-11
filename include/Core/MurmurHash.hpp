#pragma once

#include <unordered_map>
#include <string_view>
#include "Types.hpp"

/*
 * Pre-computed Murmur3 hashes for the interesting variables in the .sav files
 * See: https://github.com/marcrobledo/savegame-editors/blob/b65dc1ecf655ba4f5f8bb74d4a7d402fc375fbf1/zelda-totk/zelda-totk.js#L28
 */
std::unordered_map<u32, std::string_view> const Hashes
{
    /* progress.sav */

    // Capacities
    { 0xfbe01da1, "PlayerStatus.MaxLife" }, // i32 // type: value
    { 0xf9212c74, "PlayerStatus.MaxStamina"  }, // float // type: value
    { 0xd7a3f6ba, "Pouch.Weapon.ValidNum*" }, // i32[] // type: reference
    { 0xc61785c2, "Pouch.Bow.ValidNum*" }, // i32[] // type: reference
    { 0x05271e7d, "Pouch.Shield.ValidNum*" }, // i32[] // type: reference

    // Player Coordinates
    { 0xc884818d, "PlayerStatus.SavePos*" }, // vec3f // type: reference

    // Current Statistics
    { 0xa77921d7, "PlayerStatus.CurrentRupee" }, // i32 // type: value
    { 0x31ab5580, "PlayerStatus.Life" },  // i32 // type: value
    { 0xe573f564, "Playtime" }, // i32 // type: value
    { 0xafd01d68, "PlayerStatus.MaxEnergy" }, // float // type: value
    { 0x15ec5858, "HorseInnMemberPoint" }, // i32 // type: value

    // Map data
    { 0x14d7f4c4, "MapData.IconData.StampData.Type*" },
    { 0xf24fc2e7, "MapData.IconData.StampData.Pos*" },
    { 0xd2025694, "MapData.IconData.StampData.Layer*" },

    { 0x1d6189da, "Sequence_CurrentBanc*" },
};