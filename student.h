#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
#include <iostream>

class Student {
private:
    std::string pav_;
    std::string var_;
    std::vector<int> paz_;
    int egz_ = 0;
    double galVid_ = 0.0;
    double galMed_ = 0.0;

public:
    Student() = default;

    Student(const std::string& pav, const std::string& var,
            const std::vector<int>& paz, int egz)
        : pav_(pav), var_(var), paz_(paz), egz_(egz) {
        skaiciuotiGalutinius();
    }

    Student(std::istream& is) {
        readStudent(is);
    }

    inline const std::string& pav() const { return pav_; }
    inline const std::string& var() const { return var_; }
    inline const std::vector<int>& paz() const { return paz_; }
    inline int egz() const { return egz_; }
    inline double galVid() const { return galVid_; }
    inline double galMed() const { return galMed_; }

    inline void setPav(const std::string& p) { pav_ = p; }
    inline void setVar(const std::string& v) { var_ = v; }
    inline void setPaz(const std::vector<int>& p) { paz_ = p; }
    inline void setEgz(int e) { egz_ = e; }

    void skaiciuotiGalutinius();

    std::istream& readStudent(std::istream& is);
};

double skaiciuotiMediana(const std::vector<int>& paz);

#endif
