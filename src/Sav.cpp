#include <string>
#include "Core/Sav.hpp"
#include "Filesystem.hpp"

Sav::Sav(std::string const& path)
{
    read_all_bytes(path, m_data);
}