#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
#include "Zmogus.h"

double skaiciuotiMediana(const std::vector<int>& paz);

class Student : public Zmogus {
private:
    std::vector<int> paz_;
    int egz_ = 0;
    double galVid_ = 0.0;
    double galMed_ = 0.0;

public:
    Student() = default;

    Student(const std::string& vardas, const std::string& pavarde,
            const std::vector<int>& paz, int egz)
        : Zmogus(vardas, pavarde), paz_(paz), egz_(egz) {}

    Student(const Student& other)
        : Zmogus(other.vardas(), other.pavarde()), paz_(other.paz_),
          egz_(other.egz_), galVid_(other.galVid_), galMed_(other.galMed_) {}

    Student& operator=(const Student& other) {
        if (this != &other) {
            vardas_ = other.vardas();
            pavarde_ = other.pavarde();
            paz_ = other.paz_;
            egz_ = other.egz_;
            galVid_ = other.galVid_;
            galMed_ = other.galMed_;
        }
        return *this;
    }

    ~Student() {
        paz_.clear();
        egz_ = 0;
        galVid_ = 0;
        galMed_ = 0;
    }

    const std::vector<int>& paz() const { return paz_; }
    int egz() const { return egz_; }
    double galVid() const { return galVid_; }
    double galMed() const { return galMed_; }

    void skaiciuotiGalutinius();
    std::istream& readStudent(std::istream& is);

    friend std::istream& operator>>(std::istream& is, Student& s);
    friend std::ostream& operator<<(std::ostream& os, const Student& s);

    void print() const override {
        std::cout << vardas_ << " " << pavarde_ << "\n";
    }
};

#endif
