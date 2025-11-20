#include "student.h"
#include <algorithm>
#include <numeric>
#include <iomanip>

double skaiciuotiMediana(const std::vector<int>& paz) {
    if (paz.empty()) return 0.0;
    std::vector<int> tmp = paz;
    std::sort(tmp.begin(), tmp.end());
    size_t n = tmp.size();
    if (n % 2 == 1) return static_cast<double>(tmp[n / 2]);
    return (static_cast<double>(tmp[n / 2 - 1]) + static_cast<double>(tmp[n / 2])) / 2.0;
}

Student::Student(const std::string& pav, const std::string& var,
                 const std::vector<int>& paz, int egz)
    : pav_(pav), var_(var), paz_(paz), egz_(egz) {
    skaiciuotiGalutinius();
}

Student::Student(const Student& other)
    : pav_(other.pav_), var_(other.var_),
      paz_(other.paz_), egz_(other.egz_),
      galVid_(other.galVid_), galMed_(other.galMed_) {}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        pav_ = other.pav_;
        var_ = other.var_;
        paz_ = other.paz_;
        egz_ = other.egz_;
        galVid_ = other.galVid_;
        galMed_ = other.galMed_;
    }
    return *this;
}

Student::~Student() {
    pav_.clear();
    var_.clear();
    paz_.clear();
    egz_ = 0;
    galVid_ = 0.0;
    galMed_ = 0.0;
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
    pav_.clear(); var_.clear(); paz_.clear(); egz_ = 0;
    if (!(is >> pav_ >> var_)) return is;

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
    os << std::setw(25) << std::left << s.pav()
       << std::setw(25) << std::left << s.var()
       << std::setw(15) << std::right << std::fixed << std::setprecision(2) << s.galVid()
       << std::setw(15) << std::right << std::fixed << std::setprecision(2) << s.galMed();
    return os;
}
