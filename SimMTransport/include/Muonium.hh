#ifndef Muonium_hh
#define Muonium_hh 1

#include "Global.hh"
#include "Vector3.hh"

struct MACE::SimMTransport::Muonium {
    double_t    preTime;
    double_t    postTime;
    Vector3 prePosition;
    Vector3 postPosition;
    Vector3 velocity;

    Muonium();
    ~Muonium();
    Muonium(const Muonium&) = delete;
    Muonium& operator=(const Muonium&) = delete;
    bool operator==(const Muonium& rhs) { return this == &rhs; }
};

#endif
