/**
 * @file main.cpp
 * @brief Programos įėjimo taškas. Vartotojo meniu, rikiavimas ir skirstymas.
 */


#include "../include/student.h"
#include "../include/io.h"
#include <vector>
#include <list>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iomanip>
#include <limits>
#include <iterator>
#include <sstream>
#include <fstream>

using namespace std;
using namespace chrono;

enum class SplitStrategy { Copy = 1, Move = 2, Splice = 3 };

int getIntChoice(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Klaida! Iveskite sveika skaiciu.\n";
            continue;
        }
        if (value < min || value > max) {
            cout << "Pasirinkimas turi buti nuo " << min << " iki " << max << ".\n";
            continue;
        }
        break;
    }
    return value;
}

/**
 * @brief Rūšiuoja studentus pagal vidurkį arba medianą.
 * @tparam Container std::vector<Student> arba std::list<Student>
 * @param studentai Konteineris su Student objektais
 * @param sortParam 1 = vidurkis, 2 = mediana
 * @param order 1 = didėjimo, 2 = mažėjimo
 * @return Užtruktas laikas sekundėmis
 */
template<typename Container>
double rikiuoti(Container& studentai, int sortParam, int order) {
    auto start = high_resolution_clock::now();

    auto comp = [&](const Student& a, const Student& b) {
        double left  = (sortParam == 2 ? a.galMed() : a.galVid());
        double right = (sortParam == 2 ? b.galMed() : b.galVid());
        return order == 1 ? left < right : left > right;
    };

    if constexpr (is_same_v<Container, list<Student>>)
        studentai.sort(comp);
    else
        sort(studentai.begin(), studentai.end(), comp);

    return duration<double>(high_resolution_clock::now() - start).count();
}
/**
 * @brief Skirsto studentus į vargšus ir kietiakus
 * @tparam Container Tinka std::vector<Student> arba std::list<Student>
 * @param studentai Studentų konteineris
 * @param vargsiukai Vector, į kurį įdedami studentai su galutiniu <5
 * @param kietiakai Vector, į kurį įdedami studentai su galutiniu >=5
 * @param strategy Skirstymo strategija (Copy, Move, Splice)
 * @param sortParam Nustato, pagal ką skaičiuoti galutinį balą (1 - vidurkis, 2 - mediana)
 * @return Laikas, per kurį buvo atliktas skirstymas (s)
 */
template<typename Container>
double splitStudentus(Container& studentai,
                      std::vector<Student>& vargsiukai,
                      std::vector<Student>& kietiakai,
                      SplitStrategy strategy,
                      int sortParam) 
{
    auto start = high_resolution_clock::now();

    auto isVargsiukas = [&](const Student& s) {
        return (sortParam == 2 ? s.galMed() : s.galVid()) < 5.0;
    };

    vargsiukai.clear();
    kietiakai.clear();

    if (strategy == SplitStrategy::Copy) {
        for (const auto& s : studentai) {
            if (isVargsiukas(s)) vargsiukai.push_back(s);
            else kietiakai.push_back(s);
        }
    } else if (strategy == SplitStrategy::Move) {
        for (auto it = studentai.begin(); it != studentai.end(); ) {
            if (isVargsiukas(*it)) {
                vargsiukai.push_back(std::move(*it));
                it = studentai.erase(it);
            } else ++it;
        }
        kietiakai.assign(studentai.begin(), studentai.end());
    } else {
        if constexpr (is_same_v<Container, list<Student>>) {
            list<Student> good_students;
            auto it = stable_partition(studentai.begin(), studentai.end(), isVargsiukas);
            good_students.splice(good_students.begin(), studentai, it, studentai.end());
            vargsiukai.assign(make_move_iterator(studentai.begin()), make_move_iterator(studentai.end()));
            kietiakai.assign(make_move_iterator(good_students.begin()), make_move_iterator(good_students.end()));
        } else {
            auto it = partition(studentai.begin(), studentai.end(), isVargsiukas);
            vargsiukai.assign(make_move_iterator(studentai.begin()), make_move_iterator(it));
            kietiakai.assign(make_move_iterator(it), make_move_iterator(studentai.end()));
        }
    }

    return duration<double>(high_resolution_clock::now() - start).count();
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    vector<Student> studentai_vec;
    list<Student> studentai_list;
    vector<Student> vargsiukai, kietiakai;
    bool useList = false;

    int containerChoice = getIntChoice(
        "Pasirinkite konteinerio tipa:\n1 - std::vector\n2 - std::list\nJusu pasirinkimas: ", 
        1, 2);
    useList = (containerChoice == 2);
    cout << "Naudojamas konteineris: " << (useList ? "std::list" : "std::vector") << "\n";

    int pasirinkimas = getIntChoice(
        "Pasirinkite veiksma:\n1 - Ivesti / generuoti / nuskaityti studentus\n2 - Sugeneruoti testinius failus\nJusu pasirinkimas: ",
        1, 2);

    if (pasirinkimas == 2) {
        vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
        int kiekNd = 5;
        for (int dydis : dydziai) {
            string filename = "studentai_" + to_string(dydis) + ".txt";
            auto start = high_resolution_clock::now();
            generuotiFaila(filename, dydis, kiekNd);
            auto end = high_resolution_clock::now();
            cout << "Sugeneruotas failas " << filename << " per "
                 << duration<double>(end - start).count() << " s\n";
        }
        return 0;
    }

    int ivestis = getIntChoice(
        "Pasirinkite duomenu ivedimo buda:\n1 - Rankiniu budu\n2 - Atsitiktiniai\n3 - Nuskaityti is failo\nJusu pasirinkimas: ",
        1, 3);

    string failas;
    int sortParam = 1, order = 1, metod = 1;
    double t_read = 0.0, t_sort = 0.0, t_split = 0.0, t_write = 0.0;

    auto printTime = [](double seconds) {
        cout << fixed << setprecision(6);
        if (seconds < 0.5) cout << seconds * 1000 << " ms";
        else cout << seconds << " s";
        cout << setprecision(2) << defaultfloat;
    };

    auto ivestiStudentus = [](auto& studentai, int ivestis) {
        char testi;
        do {
            string vardas, pavarde;
            vector<int> pazymiai;
            int egzaminas = 0;

            cout << "Vardas: "; cin >> vardas;
            cout << "Pavarde: "; cin >> pavarde;

            if (ivestis == 1) {
                int laik;
                while ((laik = inputSkaicius("ND (0 baigti): ", 0, 10)) != 0)
                    pazymiai.push_back(laik);
                egzaminas = inputSkaicius("Egzaminas: ", 1, 10);
            } else {
                int kiek = rand() % 10 + 1;
                cout << "ND ivertinimai: ";
                for (int i = 0; i < kiek; i++) {
                    int nd = rand() % 10 + 1;
                    pazymiai.push_back(nd);
                    cout << nd << " ";
                }
                egzaminas = rand() % 10 + 1;
                cout << "\nEgzamino ivertinimas: " << egzaminas << endl;
            }

            studentai.emplace_back(vardas, pavarde, pazymiai, egzaminas);
            cout << "Objekto adresas konteineryje: " << &studentai.back() << endl;

            cout << "Dar vienas? (t/n) "; cin >> testi;
        } while (testi == 't' || testi == 'T');
    };

    if (ivestis == 3) {
        cout << "Iveskite failo pavadinima: "; cin >> failas;
        ifstream fin(failas);
        if (!fin) {
            cerr << "Failas neegzistuoja arba negalima atidaryti: " << failas << "\n";
            return 1;
        }
        fin.close();

        auto start_read = high_resolution_clock::now();
        if (useList) nuskaitytiIsFailo(failas, studentai_list);
        else nuskaitytiIsFailo(failas, studentai_vec);
        t_read = duration<double>(high_resolution_clock::now() - start_read).count();
    } else {
        if (useList) ivestiStudentus(studentai_list, ivestis);
        else ivestiStudentus(studentai_vec, ivestis);
        failas = "manual_input";
    }

    metod = getIntChoice("Pasirinkite galutinio balo skaiciavimo metoda:\n1 - Vidurkis\n2 - Mediana\n3 - Abu\nJusu pasirinkimas: ", 1, 3);
    if (metod == 3)
        sortParam = getIntChoice("Pagal ka rusiuoti?\n1 - Vidurki\n2 - Mediana\nJusu pasirinkimas: ", 1, 2);
    order = getIntChoice("Rikiuoti:\n1 - Didejanciai\n2 - Mazejanciai\nJusu pasirinkimas: ", 1, 2);
    int splitStrategy = getIntChoice(
        "Pasirinkite studentu skirstymo strategija (T_split):\n1 - Skaidymas i du naujus konteinerius (Kopijavimas)\n2 - Skaidymas i viena nauja konteineri (Trynimas/Perkėlimas)\n3 - Efektyviausias metodas (Splice/Move)\nJusu pasirinkimas: ",
        1, 3);

    t_sort = useList ? rikiuoti(studentai_list, sortParam, order)
                     : rikiuoti(studentai_vec, sortParam, order);
    cout << "Rikiavimas: "; printTime(t_sort); cout << "\n";

    t_split = useList ? splitStudentus(studentai_list, vargsiukai, kietiakai, static_cast<SplitStrategy>(splitStrategy), sortParam)
                      : splitStudentus(studentai_vec, vargsiukai, kietiakai, static_cast<SplitStrategy>(splitStrategy), sortParam);
    cout << "Skirstymas i grupes: "; printTime(t_split); cout << "\n";

    auto start_write = high_resolution_clock::now();
    issaugotiIFaila("vargsiukai.txt", vargsiukai, metod);
    issaugotiIFaila("kietiakai.txt", kietiakai, metod);
    auto end_write = high_resolution_clock::now();
    t_write = duration<double>(end_write - start_write).count();
    cout << "Isvedimas i failus: "; printTime(t_write); cout << "\n";

    string metricStr = (sortParam == 1) ? "Vidurkis" : "Mediana";
    string orderStr = (order == 1) ? "Didejimo tvarka" : "Mazejimo tvarka";

    cout << "\n========== TESTING FILE: " << failas << " ==========\n";
    cout << "Duomenu nuskaitymas: "; printTime(t_read); cout << "\n";
    cout << "Rikiavimas pagal " << metricStr << " (" << orderStr << "): "; printTime(t_sort); cout << "\n";
    cout << "Skirstymas i grupes: "; printTime(t_split); cout << "\n";  
    cout << "Isvedimas i failus: "; printTime(t_write); cout << "\n";
    cout << "Testavimo laikas: "; printTime(t_read + t_sort + t_split + t_write); cout << "\n\n";

    return 0;
}
