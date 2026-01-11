#include <iostream>
#include "Core/Sav.hpp"
#include "Filesystem.hpp"

int main(int const argc, char const* argv[]) {
    // if (argc != 2) return 1;
    // Sav s { argv[1] };

    /**/
    Sav progress_sav {"progress.sav"};
    std::cout << progress_sav.get<u32>("PlayerStatus.MaxLife") << std::endl;

    auto& rupees = progress_sav.get<u32>("PlayerStatus.CurrentRupee"); // get as reference
    rupees = 99'999; // directly write to sav object's memory
    std::cout << progress_sav.get<u32>("PlayerStatus.CurrentRupee") << std::endl; // 99'999

    std::cout << progress_sav.array<u32>("Pouch.Weapon.ValidNum")[0] << std::endl;
    std::cout << progress_sav.array<u32>("Pouch.Bow.ValidNum")[0] << std::endl;

    auto [x, y, z] = progress_sav.get<vec3f>("PlayerStatus.SavePos");
    std::cout << x << ", " << y << ", " << z << std::endl;

    std::cout << progress_sav.string("Sequence_CurrentBanc") << std::endl; // MainField
    /**/

    /**/
    Sav caption_sav {"caption.sav"};
    std::cout << caption_sav.string("LocationMarker"); // MapArea_TamulPlateau

    u32 const img_size = caption_sav.get<u32>("PreviewImage");
    u8 const* img_buffer = caption_sav.array<u8>("PreviewImage");

    write_all_bytes("preview.jpg", img_buffer, img_size);
    /**/
}
