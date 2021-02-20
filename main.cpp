#include <iomanip>
#include <iostream>
#include "Guess.hpp"
#include <Poco/Crypto/DigestEngine.h>

using namespace POW;

void save(const char* filename, const std::string& bytes);

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        std::cerr << "USAGE: ./main <file>" << std::endl;
        return 1;
    }

    auto message = load_message(argv[1]);
    std::cout << "Loaded " << message.size() << " bytes ";
    std::cout << "from " << argv[1] << '.' << std::endl;

    Tools::RNG rng;

    Poco::Crypto::DigestEngine engine("SHA256");
    int target_zeros = 3;

    for(unsigned long long i=0; ; ++i)
    {
        auto bytes = POW::generate_bytes(32, rng);
        engine.reset();
        engine.update(message + bytes);
        auto digest = engine.digest();
        int zeros = count_zeros(digest);
//        std::cout << digest.size() << ' ' << zeros << std::endl;

        bool done = zeros >= target_zeros;
        if(done || ((i+1) % 1000 == 0))
            std::cout << (i+1) << std::endl;
        if(done)
        {
            save("proof.dat", bytes);
            break;
        }
    }

    return 0;
}


void save(const char* filename, const std::string& bytes)
{
    std::fstream fout(filename, std::ios::out | std::ios::binary);
    fout.write(&bytes[0], bytes.size());
    fout.close();
}

