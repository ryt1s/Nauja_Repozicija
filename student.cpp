/**
 * @file student.cpp
 * @brief Student klasės implementacija: konstruktoriai, kopijavimas, skaiciavimai, IO operatoriai.
 */


#include "student.h"
#include <algorithm>
#include <numeric>
#include <iomanip>

/**
 * @brief Apskaičiuoja mediana iš pažymių vektoriaus.
 * @param paz Vektorius pažymių
 * @return Mediana kaip double
 */


double skaiciuotiMediana(const std::vector<int>& paz) {
    if (paz.empty()) return 0.0;
    std::vector<int> tmp = paz;
    std::sort(tmp.begin(), tmp.end());
    size_t n = tmp.size();
    if (n % 2 == 1) return static_cast<double>(tmp[n / 2]);
    return (static_cast<double>(tmp[n / 2 - 1]) + static_cast<double>(tmp[n / 2])) / 2.0;
}

void Student::skaiciuotiGalutinius() {
    if (paz_.empty()) {
        galVid_ = 0.6 * egz_;
        galMed_ = 0.6 * egz_;
    } else {
        double ndVid = std::accumulate(paz_.begin(), paz_.end(), 0.0) / paz_.size();
        galVid_ = 0.4 * ndVid + 0.6 * egz_;
        galMed_ = 0.4 * skaiciuotiMediana(paz_) + 0.6 * egz_;
    }
}

std::istream& Student::readStudent(std::istream& is) {
    vardas_.clear(); pavarde_.clear(); paz_.clear(); egz_ = 0;
    if (!(is >> vardas_ >> pavarde_)) return is;

    int val;
    std::vector<int> tmp;
    while (is >> val) tmp.push_back(val);

    is.clear();

    if (!tmp.empty()) {
        egz_ = tmp.back();
        tmp.pop_back();
        paz_ = std::move(tmp);
    }
    skaiciuotiGalutinius();
    return is;
}

std::istream& operator>>(std::istream& is, Student& s) {
    return s.readStudent(is);
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << std::setw(25) << std::left << s.pavarde_
       << std::setw(25) << std::left << s.vardas_
       << std::setw(15) << std::right << std::fixed << std::setprecision(2) << s.galVid()
       << std::setw(15) << std::right << std::fixed << std::setprecision(2) << s.galMed();
    return os;
}
