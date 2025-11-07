#include "student.h"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <limits>
#include <iostream>

double skaiciuotiMediana(const std::vector<int>& paz) {
    if (paz.empty()) return 0.0;
    std::vector<int> tmp = paz;
    std::sort(tmp.begin(), tmp.end());
    size_t n = tmp.size();
    if (n % 2 == 1) return static_cast<double>(tmp[n/2]);
    return (static_cast<double>(tmp[n/2 - 1]) + static_cast<double>(tmp[n/2])) / 2.0;
}

void Student::skaiciuotiGalutinius() {
    if (paz_.empty()) {
        galVid_ = 0.6 * egz_;
        galMed_ = 0.6 * egz_;
    } else {
        double sum = std::accumulate(paz_.begin(), paz_.end(), 0.0);
        double ndVid = sum / static_cast<double>(paz_.size());
        galVid_ = 0.4 * ndVid + 0.6 * egz_;
        galMed_ = 0.4 * skaiciuotiMediana(paz_) + 0.6 * egz_;
    }
}

std::istream& Student::readStudent(std::istream& is) {
    pav_.clear(); var_.clear(); paz_.clear(); egz_ = 0;
    
    if (!(is >> pav_ >> var_)) {
        return is;
    }

    int val;
    std::vector<int> tmp;
    while (is >> val) {
        tmp.push_back(val);
    }
    
    is.clear(); 

    if (!tmp.empty()) {
        egz_ = tmp.back();
        tmp.pop_back();
        paz_ = std::move(tmp);
    } else {
        egz_ = 0;
        paz_.clear();
    }

    skaiciuotiGalutinius();
    return is;
}