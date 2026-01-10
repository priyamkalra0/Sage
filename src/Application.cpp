#include <iostream>
#include "Core/Sav.hpp"

int main(int const argc, char const* argv[]) {
    // if (argc != 2) return 1;
    // Sav s { argv[1] };

    Sav s {"progress.sav"};
    std::cout << s.read<u32>(170564) << std::endl;
}
