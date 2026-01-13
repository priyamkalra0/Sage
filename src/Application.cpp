#include <iostream>
#include "Core/Sav.hpp"
#include "Core/Enum.hpp"
#include "Core/Hash.hpp"
#include "Core/HashArray.hpp"
#include "Filesystem.hpp"

int main(int const argc, char const* argv[]) {
    // if (argc != 2) return 1;
    // Sav s { argv[1] };

    /* Sample usage for `Sav.hpp` */
    /* progress.sav */
    Sav progress_sav { "progress.sav" };

    /* Query location */
    auto [x, y, z] = progress_sav.get<vec3f>(Hash::PlayerStatus_SavePos);
    std::cout << "Location: " << x << ", " << y << ", " << z << std::endl;

    /* Set heart container count */
    auto& hearts = progress_sav.get<u32>(Hash::PlayerStatus_MaxLife);
    hearts = 40 * 4; // directly writes to sav object's memory

    std::cout
        << "Hearts set to "
        << hearts / 4
        << std::endl;

    /* Set rupee amount */
    auto& rupees = progress_sav.get<u32>(Hash::PlayerStatus_CurrentRupee); // get as reference
    rupees = 99'999;

    std::cout
        << "Rupees set to "
        << rupees
        << std::endl;

    /* Set weapon capacity */
    auto& weapon_capacity = progress_sav.array<u32>(Hash::Pouch_Weapon_ValidNum)[0];
    weapon_capacity = 20;

    std::cout
        << "Weapon capacity set to "
        << weapon_capacity
        << std::endl;

    /* Query cleared shrine count */
    auto query_shrines = [&sav = progress_sav]() {
        return sav.test(HashArray::DungeonState, Enum::DungeonState::Clear);
    };
    std::cout << "Shrines cleared: " << query_shrines(); // 50

    /* Set all shrines as cleared */
    progress_sav.set(HashArray::DungeonState, Enum::DungeonState::Clear);
    std::cout << " -> " << query_shrines() << std::endl; // 152

    progress_sav.dump("export.sav");
    /**/

    /* caption.sav */
    Sav caption_sav { "caption.sav" };

    /* Query map area, it is found 48 bytes
     * after Metadata.SaveTypeHash
     */
    std::string_view const map_area = &caption_sav.get<char>(Hash::CaptionData_SaveTypeHash) + 48;
    std::cout << map_area; // MapArea_TamulPlateau

    /* Export save thumbnail (menu preview image) */
    std::span<u8 const> image = caption_sav.array<u8>(Hash::CaptionData_ScreenShot);

    write_all_bytes("preview.jpg", image);
    /**/
}
