#pragma once

#include <cstdint>
#include <string_view>

/* See: https://github.com/AntonJohansson/StaticMurmur/blob/master/StaticMurmur.hpp */
class murmurhash3 /* only x86_32 */
{
public:
    static constexpr uint32_t hash(std::string_view const& s, uint32_t const seed = 0)
    {
        return MurmurHash3_x86_32(s.data(), s.size(), seed);
    }

private:
    static constexpr uint32_t MurmurHash3_x86_32(char const* key, uint32_t const len, const uint32_t seed)
    {
        const unsigned nblocks = len / 4;

        uint32_t h1 = seed;

        const uint32_t c1 = 0xcc9e2d51;
        const uint32_t c2 = 0x1b873593;

        for (int i = 0; i < nblocks; ++i)
        {
            uint32_t k1 = get_block(key, i);

            k1 *= c1;
            k1 = rotl32(k1, 15);
            k1 *= c2;

            h1 ^= k1;
            h1 = rotl32(h1, 13);
            h1 = h1 * 5 + 0xe6546b64;
        }

        uint32_t k1 = 0;
        const unsigned tail_start = len - (len % 4);
        switch (len & 3)
        {
        case 3: k1 ^= key[tail_start + 2] << 16;
        case 2: k1 ^= key[tail_start + 1] << 8;
        case 1: k1 ^= key[tail_start + 0];
            k1 *= c1;
            k1 = rotl32(k1, 15);
            k1 *= c2;
            h1 ^= k1;
        };

        h1 ^= len;

        h1 = fmix32(h1);

        return h1;
    }

    static constexpr uint32_t get_block(char const* p, uint32_t const i)
    {
        const uint32_t block =
            static_cast<uint32_t>(p[0 + i * 4]) << 0 |
            static_cast<uint32_t>(p[1 + i * 4]) << 8 |
            static_cast<uint32_t>(p[2 + i * 4]) << 16 |
            static_cast<uint32_t>(p[3 + i * 4]) << 24;
        return block;
    }

    static constexpr uint32_t rotl32(uint32_t const x, int8_t const r)
    {
        return (x << r) | (x >> (32 - r));
    }

    static constexpr uint32_t fmix32(uint32_t h)
    {
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;
        return h;
    }
};
