#ifndef POW_Guess_hpp
#define POW_Guess_hpp

#include <fstream>
#include <Tools/RNG.hpp>
#include <string>
#include <vector>

namespace POW
{

using Tools::RNG;

inline std::string load_message(const char* filename);
inline std::string generate_bytes(int size,
                                  Tools::RNG& rng);

/* IMPLEMENTATIONS FOLLOW */

inline std::string load_message(const char* filename)
{
    std::fstream fin(filename, std::ios::in | std::ios::binary);
    std::string result;
    char c;
    while(true)
    {
        fin.read(&c, 1);
        if(fin.eof())
            break;
        result += std::string{c};
    }
    fin.close();
    return result;
}

inline std::string generate_bytes(int size,
                                  Tools::RNG& rng)
{
    std::string result;
    for(int i=0; i<size; ++i)
        result += rng.rand_int(256);
    return result;
}

inline int count_zeros(const std::vector<unsigned char>& bytes)
{
    int result = 0;
    for(auto byte: bytes)
    {
        if(byte == (unsigned char)(0))
            ++result;
        else
            break;
    }
    return result;
}

} // namespace

#endif

