#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
#include <iostream>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus() = default;

    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

    virtual ~Zmogus() = default;

    std::string vardas() const { return vardas_; }
    std::string pavarde() const { return pavarde_; }

    virtual void print() const = 0;
};

#endif
