#include <iostream>
#include "Core/Sav.hpp"
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

    progress_sav.dump("export.sav");
    /**/

    /* caption.sav */
    Sav caption_sav { "caption.sav" };

    /* Query map area */
    std::cout << caption_sav.string(Hash::LocationMarker); // MapArea_TamulPlateau

    /* Export save thumbnail (menu preview image) */
    std::span<u8 const> image = caption_sav.array<u8>(Hash::PreviewImage);

    write_all_bytes("preview.jpg", image);
    /**/
}
