#ifndef POW_Guess_hpp
#define POW_Guess_hpp

#include <Tools/RNG.hpp>
#include <vector>

namespace POW
{

using Tools::RNG;

inline std::vector<unsigned char> generate_bytes(int size,
                                                 Tools::RNG& rng);

/* IMPLEMENTATIONS FOLLOW */

inline std::vector<unsigned char> generate_bytes(int size,
                                                 Tools::RNG& rng)
{
    std::vector<unsigned char> result(size);
    for(auto& byte: result)
        byte = rng.rand_int(256);
    return result;
}

} // namespace

#endif

