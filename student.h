/**
 * @file Student.h
 * @brief Student klasė, išvestinė iš Zmogus, su pažymiais ir galutiniais balais.
 */

#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
#include "Zmogus.h"

double skaiciuotiMediana(const std::vector<int>& paz);

/**
 * @class Student
 * @brief Išvestinė klasė aprašanti studentą.
 *
 * Palaiko "Rule of Three": kopijavimo konstruktorių, priskyrimo operatorių ir destruktorių.
 * Apskaičiuoja galutinius balus pagal vidurkį ir medianą.
 */

class Student : public Zmogus {
private:
    std::vector<int> paz_; /**< Namų darbų įvertinimai */
    int egz_ = 0; /**< Egzamino įvertinimas */
    double galVid_ = 0.0;
    double galMed_ = 0.0;

public:
    Student() : Zmogus(), egz_(0), galVid_(0.0), galMed_(0.0) {}

       /**
     * @brief Konstruktorius su vardu, pavarde, ND ir egzamino balais
     * @param vardas Studento vardas
     * @param pavarde Studento pavardė
     * @param nd Namų darbų įvertinimai
     * @param egz Egzamino įvertinimas
     */
    Student(const std::string& vardas, const std::string& pavarde,
            const std::vector<int>& paz, int egz)
        : Zmogus(vardas, pavarde), paz_(paz), egz_(egz) {
        skaiciuotiGalutinius();
    }
    /**
     * @brief Copy konstruktorius
     * @param other Kitas Student objektas, kurį kopijuojame
     */
    Student(const Student& other)
        : Zmogus(other.vardas_, other.pavarde_),
          paz_(other.paz_),
          egz_(other.egz_),
          galVid_(other.galVid_),
          galMed_(other.galMed_) {}
    /**
     * @brief Copy assignment operator
     * @param other Kitas Student objektas
     * @return Referencija į šį objektą
     */
    Student& operator=(const Student& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            paz_ = other.paz_;
            egz_ = other.egz_;
            galVid_ = other.galVid_;
            galMed_ = other.galMed_;
        }
        return *this;
    }
    /** @brief Destruktorius */
    ~Student() {
        paz_.clear();
        egz_ = 0;
        galVid_ = 0.0;
        galMed_ = 0.0;
    }

    const std::vector<int>& paz() const { return paz_; }
    int egz() const { return egz_; }
    /** @brief Skaičiuoja galutinį vidurkį */
    double galVid() const { return galVid_; }
    /** @brief Skaičiuoja galutinę medianą */
    double galMed() const { return galMed_; }

    /** @brief Paveldėtas abstraktus metodas — atspausdina info apie žmogų. */

    void print() const override {
        std::cout << vardas_ << " " << pavarde_ << " | "
                  << "Vidurkis: " << galVid_ << ", Mediana: " << galMed_ << "\n";
    }
    /**
 * @brief Apskaičiuoja galutinius balus (vidurkis ir mediana).
 */
    void skaiciuotiGalutinius();

/**
 * @brief Perskaito studentą iš įvedimo srauto.
 * @param is Įvesties srautas
 * @return Srautas po nuskaitymo
 */

    std::istream& readStudent(std::istream& is);

    friend std::istream& operator>>(std::istream& is, Student& s);
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

#endif
