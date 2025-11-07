#include "io.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits> // Būtina ifstream valymui

using namespace std;

void generuotiFaila(const string& filename, int kiekStudentu, int kiekNd) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Nepavyko sukurti failo: " << filename << endl;
        return;
    }

    fout << setw(20) << left << "Pavarde"
         << setw(20) << left << "Vardas";
    for (int i = 1; i <= kiekNd; ++i)
        fout << setw(5) << ("ND" + to_string(i));
    fout << setw(10) << "Egzaminas" << "\n";

    for (int i = 1; i <= kiekStudentu; ++i) {
        string pav = "Pavarde" + to_string(i);
        string var = "Vardas" + to_string(i);

        fout << setw(20) << left << pav
             << setw(20) << left << var;

        for (int j = 0; j < kiekNd; ++j)
            fout << setw(5) << (rand() % 10 + 1);
        fout << setw(10) << (rand() % 10 + 1) << "\n";
    }

    fout.close();
    cout << "Sugeneruotas failas: " << filename << " (" << kiekStudentu << " irasu)\n";
}

// OPTIMIZUOTA NUSKAITYMO FUNKCIJA (vector)
void nuskaitytiIsFailo(const string& filename, vector<Student>& studentai) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Nepavyko atidaryti failo: " << filename << endl;
        return;
    }

    string header;
    getline(fin, header); 
    
    // Nuskaitoma tiesiai iš failo srauto (fin), išvengiant tarpinio std::string
    while (fin.peek() != EOF) {
        Student stud; 
        stud.readStudent(fin); 
        
        // Būtina, kad praleistų likusią eilutės dalį (įskaitant \n)
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (!stud.pav().empty()) { 
            studentai.push_back(std::move(stud));
        }
    }
}

// OPTIMIZUOTA NUSKAITYMO FUNKCIJA (list)
void nuskaitytiIsFailo(const string& filename, list<Student>& studentai) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Nepavyko atidaryti failo: " << filename << endl;
        return;
    }

    string header;
    getline(fin, header); 

    while (fin.peek() != EOF) {
        Student stud; 
        stud.readStudent(fin); 
        
        fin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!stud.pav().empty()) {
            studentai.push_back(std::move(stud)); 
        }
    }
}

void issaugotiIFaila(const string& filename, const vector<Student>& students, int metod) {
    std::ofstream fout(filename, std::ios::out | std::ios::trunc);
    if (!fout.is_open()) return;

    fout << setw(25) << left << "Pavarde"
          << setw(25) << left << "Vardas";
    if (metod == 3) {
        fout << setw(15) << left << "Galutinis (Vid.)"
              << setw(15) << left << "Galutinis (Med.)";
    } else {
        fout << setw(15) << left << "Galutinis";
    }
    fout << "\n";

    std::string buffer;
    buffer.reserve(1 << 20);
    const size_t FLUSH_THRESHOLD = (1 << 20);

    for (const auto& s : students) {
        char line[512];
        int n = 0;
        if (metod == 3) {
            n = std::snprintf(line, sizeof(line),
                               "%-25s %-25s %15.2f %15.2f\n",
                               s.pav().c_str(), s.var().c_str(), s.galVid(), s.galMed());
        } else {
            double galutinis = (metod == 1 ? s.galVid() : s.galMed());
            n = std::snprintf(line, sizeof(line),
                               "%-25s %-25s %15.2f\n",
                               s.pav().c_str(), s.var().c_str(), galutinis);
        }
        buffer.append(line, static_cast<size_t>(n));
        if (buffer.size() > FLUSH_THRESHOLD) {
            fout.write(buffer.data(), buffer.size());
            buffer.clear();
        }
    }
    if (!buffer.empty()) fout.write(buffer.data(), buffer.size());
    fout.close();
}

void issaugotiIFaila(const string& filename, const list<Student>& students, int metod) {
    std::ofstream fout(filename, std::ios::out | std::ios::trunc);
    if (!fout.is_open()) return;

    fout << setw(25) << left << "Pavarde"
          << setw(25) << left << "Vardas";
    if (metod == 3) {
        fout << setw(15) << left << "Galutinis (Vid.)"
              << setw(15) << left << "Galutinis (Med.)";
    } else {
        fout << setw(15) << left << "Galutinis";
    }
    fout << "\n";

    std::string buffer;
    buffer.reserve(1 << 20);
    const size_t FLUSH_THRESHOLD = (1 << 20);

    for (const auto& s : students) {
        char line[512];
        int n = 0;
        if (metod == 3) {
            n = std::snprintf(line, sizeof(line),
                               "%-25s %-25s %15.2f %15.2f\n",
                               s.pav().c_str(), s.var().c_str(), s.galVid(), s.galMed());
        } else {
            double galutinis = (metod == 1 ? s.galVid() : s.galMed());
            n = std::snprintf(line, sizeof(line),
                               "%-25s %-25s %15.2f\n",
                               s.pav().c_str(), s.var().c_str(), galutinis);
        }
        buffer.append(line, static_cast<size_t>(n));
        if (buffer.size() > FLUSH_THRESHOLD) {
            fout.write(buffer.data(), buffer.size());
            buffer.clear();
        }
    }
    if (!buffer.empty()) fout.write(buffer.data(), buffer.size());
    fout.close();
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