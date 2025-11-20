#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>

double skaiciuotiMediana(const std::vector<int>& paz);

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
            const std::vector<int>& paz, int egz);

    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();

    const std::string& pav() const { return pav_; }
    const std::string& var() const { return var_; }
    const std::vector<int>& paz() const { return paz_; }
    int egz() const { return egz_; }
    double galVid() const { return galVid_; }
    double galMed() const { return galMed_; }

    void skaiciuotiGalutinius();
    std::istream& readStudent(std::istream& is);

    friend std::istream& operator>>(std::istream& is, Student& s);
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

#endif
