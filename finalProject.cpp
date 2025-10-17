#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <cstring>

static inline uint32_t rotr(uint32_t x, uint32_t n) {
    return (x >> n) | (x << (32 - n));
}

static const uint32_t K[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

// Initial hash values (square roots of first 8 primes)
static const uint32_t H0[8] = {
    0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,
    0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19
};

std::string sha256(const std::vector<uint8_t>& data) {
    uint64_t bit_len = data.size() * 8;
    std::vector<uint8_t> msg = data;

    msg.push_back(0x80);
    while ((msg.size() * 8) % 512 != 448) {
        msg.push_back(0x00);
    }

    for (int i = 7; i >= 0; --i)
        msg.push_back(static_cast<uint8_t>((bit_len >> (i * 8)) & 0xFF));

    uint32_t h[8];
    std::memcpy(h, H0, sizeof(H0));

    for (size_t chunk_start = 0; chunk_start < msg.size(); chunk_start += 64) {
        uint32_t w[64];

        for (int i = 0; i < 16; ++i) {
            size_t idx = chunk_start + i * 4;
            w[i] = (msg[idx] << 24) | (msg[idx + 1] << 16) | (msg[idx + 2] << 8) | msg[idx + 3];
        }

        for (int i = 16; i < 64; ++i) {
            uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
            uint32_t s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = (w[i - 16] + s0 + w[i - 7] + s1) & 0xFFFFFFFF;
        }

        uint32_t a = h[0], b = h[1], c = h[2], d = h[3];
        uint32_t e = h[4], f = h[5], g = h[6], hh = h[7];

        for (int i = 0; i < 64; ++i) {
            uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = hh + S1 + ch + K[i] + w[i];
            uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            hh = g;
            g = f;
            f = e;
            e = (d + temp1) & 0xFFFFFFFF;
            d = c;
            c = b;
            b = a;
            a = (temp1 + temp2) & 0xFFFFFFFF;
        }

        h[0] = (h[0] + a) & 0xFFFFFFFF;
        h[1] = (h[1] + b) & 0xFFFFFFFF;
        h[2] = (h[2] + c) & 0xFFFFFFFF;
        h[3] = (h[3] + d) & 0xFFFFFFFF;
        h[4] = (h[4] + e) & 0xFFFFFFFF;
        h[5] = (h[5] + f) & 0xFFFFFFFF;
        h[6] = (h[6] + g) & 0xFFFFFFFF;
        h[7] = (h[7] + hh) & 0xFFFFFFFF;
    }

    std::ostringstream result;
    result << std::hex << std::setfill('0');
    for (int i = 0; i < 8; ++i)
        result << std::setw(8) << h[i];

    return result.str();
}

std::vector<uint8_t> read_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("Could not open file: " + filename);
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)),
                                 std::istreambuf_iterator<char>());
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./sha256_mark <file>\n";
        return 1;
    }

    try {
        auto data = read_file(argv[1]);
        std::string hash = sha256(data);
        std::cout << "SHA-256 (" << argv[1] << ") = " << hash << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
