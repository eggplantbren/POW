#include <iomanip>
#include <iostream>
#include "Guess.hpp"
#include <Poco/Crypto/DigestEngine.h>
#include <Tools/Timer.hpp>

using namespace POW;

void save(const char* filename, const std::string& bytes);
bool less(const std::vector<unsigned char>& x, const std::vector<unsigned char>& y);

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

    std::string best_nonce;
    std::vector<unsigned char> best_hash;
    Tools::Timer timer;
    unsigned long long steps = 1000000000;
    for(unsigned long long i=0; i<steps; ++i)
    {
        int bytes = 4 + rng.rand_int(61);

        auto nonce = POW::generate_bytes(bytes, rng);
        engine.reset();
        engine.update(message + nonce);
        auto digest = engine.digest();
        if(i == 0 || less(digest, best_hash))
        {
            best_nonce = nonce;
            best_hash = digest;
        }

        if((i+1) % 10000 == 0)
        {
            save("nonce.dat", best_nonce);
            std::cout << (i+1) << ". ";
            std::cout << "Hash rate = " << double(i + 1)/timer.stop();
            std::cout << " H/s." << std::endl;
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

bool less(const std::vector<unsigned char>& x, const std::vector<unsigned char>& y)
{
    for(int i=0; i<int(x.size()); ++i)
    {
        if(x[i] < y[i])
            return true;
        else if(x[i] > y[i])
            return false;
    }
    return false;
}

