# Sage

Simple tool for parsing and patching savegame files for TLoZ: Tears of the Kingdom written in C++17.  
Based on this amazing [savegame editor](https://www.marcrobledo.com/savegame-editors/zelda-totk) by [Marc Robeldo](https://www.marcrobledo.com/).

## Usage
At this stage, no user interface has been implemented;  
but the `Sav.hpp` header can be included and used like a library as such:
```c++
    /* progress.sav */
    Sav progress_sav { "progress.sav" };

    /* Query location */
    auto [x, y, z] = progress_sav.get<vec3f>("PlayerStatus.SavePos");
    std::cout << "Location: " << x << ", " << y << ", " << z << std::endl;

    /* Set heart container count */
    auto& hearts = progress_sav.get<u32>("PlayerStatus.MaxLife"); // get as reference
    hearts = 40 * 4; // directly writes to sav object's memory

    std::cout
        << "Hearts set to "
        << progress_sav.get<u32>("PlayerStatus.MaxLife") / 4
        << std::endl;

    /* Set rupee amount */
    auto& rupees = progress_sav.get<u32>("PlayerStatus.CurrentRupee");
    rupees = 99'999;

    std::cout
        << "Rupees set to "
        << progress_sav.get<u32>("PlayerStatus.CurrentRupee")
        << std::endl;

    progress_sav.dump("progress.sav");
    /**/

    /* caption.sav */
    Sav caption_sav { "caption.sav" };

    /* Query map area */
    std::cout << caption_sav.string("LocationMarker"); // MapArea_TamulPlateau

    /* Export save thumbnail (menu preview image) */
    u32 const img_size = caption_sav.get<u32>("PreviewImage");
    u8 const* img_buffer = caption_sav.array<u8>("PreviewImage");
    write_all_bytes("preview.jpg", img_buffer, img_size);
    /**/
```

The modified number of heart containers and amount of rupees will reflect in-game:
![sample-image](https://github.com/priyamkalra0/Sage/releases/download/sample-image/sample.png)

## Dependencies

*   none

## Build

This project uses CMake. To build, navigate to the project root and run:

```bash
mkdir build
cd build && cmake ..
cmake --build .
```