#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
#include <iostream>

class Student {
private:
    std::string pav_;              // Pavardė (matches your file format)
    std::string var_;              // Vardas
    std::vector<int> paz_;         // ND pažymiai
    int egz_ = 0;                  // Egzamino balas
    double galVid_ = 0.0;          // Galutinis (vidurkis variantas)
    double galMed_ = 0.0;          // Galutinis (mediana variantas)

public:
    Student() = default;

    // Construct from fields
    Student(const std::string& pav, const std::string& var,
            const std::vector<int>& paz, int egz)
        : pav_(pav), var_(var), paz_(paz), egz_(egz) {
        skaiciuotiGalutinius();
    }

    // Construct from stream (calls readStudent)
    Student(std::istream& is) {
        readStudent(is);
    }

    // Getters (const refs for strings/vectors where appropriate)
    inline const std::string& pav() const { return pav_; }
    inline const std::string& var() const { return var_; }
    inline const std::vector<int>& paz() const { return paz_; }
    inline int egz() const { return egz_; }
    inline double galVid() const { return galVid_; }
    inline double galMed() const { return galMed_; }

    // Setters / modifiers
    inline void setPav(const std::string& p) { pav_ = p; }
    inline void setVar(const std::string& v) { var_ = v; }
    inline void setPaz(const std::vector<int>& p) { paz_ = p; }
    inline void setEgz(int e) { egz_ = e; }

    // Calculate final scores
    void skaiciuotiGalutinius();

    // Read a single student from a stream (expected: Pavarde Vardas nd1 nd2 ... egz)
    std::istream& readStudent(std::istream& is);
};

// helper functions (kept for sorting usage)
double skaiciuotiMediana(const std::vector<int>& paz);

#endif // STUDENT_H
