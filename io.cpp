#include "io.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <random>
#include <type_traits>

using namespace std;

void generuotiFaila(const string& filename, int kiekStudentu, int kiekNd) {
    ofstream fout(filename);
    if (!fout) { cerr << "Nepavyko sukurti failo: " << filename << "\n"; return; }

    fout << setw(20) << left << "Pavarde"
         << setw(20) << left << "Vardas";
    for (int i = 1; i <= kiekNd; ++i) fout << setw(5) << ("ND" + to_string(i));
    fout << setw(10) << "Egzaminas" << "\n";

    mt19937 rng(static_cast<unsigned>(time(nullptr)));
    uniform_int_distribution<int> dist(1, 10);

    for (int i = 1; i <= kiekStudentu; ++i) {
        string pav = "Pavarde" + to_string(i);
        string var = "Vardas" + to_string(i);

        fout << setw(20) << left << pav
             << setw(20) << left << var;

        for (int j = 0; j < kiekNd; ++j) fout << setw(5) << dist(rng);
        fout << setw(10) << dist(rng) << "\n";
    }

    cout << "Sugeneruotas failas: " << filename
         << " (" << kiekStudentu << " irasu)\n";
}

template<typename Container>
void nuskaitytiIsFailoTemplate(const string& filename, Container& studentai) {
    ifstream fin(filename);
    if (!fin) { cerr << "Nepavyko atidaryti failo: " << filename << "\n"; return; }

    string header;
    getline(fin, header);

    Student stud;
    while (fin >> stud) {
        studentai.push_back(move(stud));
    }
}

void nuskaitytiIsFailo(const string& filename, vector<Student>& studentai) {
    nuskaitytiIsFailoTemplate(filename, studentai);
}

void nuskaitytiIsFailo(const string& filename, list<Student>& studentai) {
    nuskaitytiIsFailoTemplate(filename, studentai);
}

template <typename Container>
void issaugotiIFailaTemplate(const std::string& filename, const Container& students, int metod) {
    std::ofstream fout(filename, std::ios::out | std::ios::trunc);
    if (!fout.is_open()) return;

    fout << std::left << std::setw(25) << "Pavarde"
         << std::setw(25) << "Vardas";

    if (metod == 3) {
        fout << std::setw(15) << "Galutinis (Vid.)"
             << std::setw(15) << "Galutinis (Med.)";
    } else {
        fout << std::setw(15) << "Galutinis";
    }
    fout << "\n";

    std::string buffer;
    buffer.reserve(1 << 20);
    const size_t FLUSH_THRESHOLD = (1 << 20);

    for (const auto& s : students) {
        std::ostringstream line;
        line << std::left << std::setw(25) << s.pav()
             << std::setw(25) << s.var();

        if (metod == 3) {
            line << std::setw(15) << std::fixed << std::setprecision(2) << s.galVid()
                 << std::setw(15) << std::fixed << std::setprecision(2) << s.galMed();
        } else {
            double galutinis = (metod == 1 ? s.galVid() : s.galMed());
            line << std::setw(15) << std::fixed << std::setprecision(2) << galutinis;
        }
        line << "\n";

        buffer.append(line.str());
        if (buffer.size() > FLUSH_THRESHOLD) {
            fout.write(buffer.data(), buffer.size());
            buffer.clear();
        }
    }

    if (!buffer.empty()) {
        fout.write(buffer.data(), buffer.size());
    }
}

void issaugotiIFaila(const string& filename, const vector<Student>& students, int metod) {
    issaugotiIFailaTemplate(filename, students, metod);
}

void issaugotiIFaila(const string& filename, const list<Student>& students, int metod) {
    issaugotiIFailaTemplate(filename, students, metod);
}

int inputSkaicius(const string& pranesimas, int min, int max) {
    int value;
    while (true) {
        cout << pranesimas;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Klaida! Iveskite sveika skaiciu.\n";
            continue;
        }

        if (value < min || value > max) {
            cout << "Balas turi buti nuo " << min << " iki " << max << ". Bandykite dar karta.\n";
            continue;
        }

        break;
    }
    return value;
}
