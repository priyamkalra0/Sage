#include <iostream>
#include "Core/Sav.hpp"

int main(int const argc, char const* argv[]) {
    // if (argc != 2) return 1;
    // Sav s { argv[1] };

    Sav s {"progress.sav"};
    std::cout << s.get<u32>("PlayerStatus.MaxLife") << std::endl;

    auto& rupees = s.get<u32>("PlayerStatus.CurrentRupee"); // get as reference
    rupees = 99'999; // directly write to sav object's memory

    std::cout << s.get<u32>("PlayerStatus.CurrentRupee") << std::endl; // 99'999

    std::cout << s.get_array<u32>("Pouch.Weapon.ValidNum")[0] << std::endl;
    std::cout << s.get_array<u32>("Pouch.Bow.ValidNum")[0] << std::endl;
}
