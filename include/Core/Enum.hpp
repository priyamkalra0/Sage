#pragma once
#include "MurmurHash3.hpp"
#include "Types.hpp"

namespace Enum
{
    /* Various enum values used in progress.sav
     * See: https://github.com/marcrobledo/savegame-editors/blob/b65dc1ecf655ba4f5f8bb74d4a7d402fc375fbf1/zelda-totk/zelda-totk.hashes.csv#L5
     */

    enum class DungeonState : u32
    {
        Hidden = murmurhash3::hash("Hidden"),
        Appear = murmurhash3::hash("Appear"),
        Open = murmurhash3::hash("Open"),
        Enter = murmurhash3::hash("Enter"),
        Clear = murmurhash3::hash("Clear")
    };

    enum class CheckpointState : u32 // ArrivalPointState_Checkpoint
    {
        Close = murmurhash3::hash("Close"),
        Open = murmurhash3::hash("Open")
    };

    enum class KorokCarryProgress : u32
    {
        NotClear = murmurhash3::hash("NotClear"),
        Clear = murmurhash3::hash("Clear")
    };

    enum class PictureBookDataState : u32
    {
        Unopened = murmurhash3::hash("Unopened"),
        TakePhoto = murmurhash3::hash("TakePhoto"),
        Buy = murmurhash3::hash("Buy")

    };
}
