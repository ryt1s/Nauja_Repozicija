#include "student.h"
#include "io.h"
#include <vector>
#include <list>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;
using namespace chrono;

enum class SplitStrategy { Copy = 1, Move = 2, Splice = 3 };

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

template<typename Container>
double splitStudentus(Container& studentai,
                      vector<Student>& vargsiukai,
                      vector<Student>& kietiakai,
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
        for (const auto& s : studentai)
            (isVargsiukas(s) ? vargsiukai : kietiakai).push_back(s);
    } 
    else if (strategy == SplitStrategy::Move) {
        for (auto it = studentai.begin(); it != studentai.end(); ) {
            if (isVargsiukas(*it)) {
                vargsiukai.push_back(std::move(*it));
                it = studentai.erase(it);
            } else ++it;
        }
        kietiakai.assign(studentai.begin(), studentai.end());
    } 
    else {
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

void printTime(double seconds) {
    cout << fixed << setprecision(6);
    if (seconds < 0.5) cout << seconds * 1000 << " ms";
    else cout << seconds << " s";
    cout << setprecision(2) << defaultfloat;
}

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

        studentai.emplace_back(pavarde, vardas, pazymiai, egzaminas);
        cout << "Objekto adresas konteineryje: " << &studentai.back() << endl;

        cout << "Dar vienas? (t/n) "; cin >> testi;
    } while (testi == 't' || testi == 'T');
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    vector<Student> studentai_vec;
    list<Student> studentai_list;
    vector<Student> vargsiukai, kietiakai;
    bool useList = false;

    cout << "Pasirinkite konteinerio tipa:\n1 - std::vector\n2 - std::list\nJusu pasirinkimas: ";
    int containerChoice; cin >> containerChoice;
    useList = (containerChoice == 2);
    cout << "Naudojamas konteineris: " << (useList ? "std::list" : "std::vector") << "\n";

    cout << "Pasirinkite veiksma:\n1 - Ivesti / generuoti / nuskaityti studentus\n2 - Sugeneruoti testinius failus\nJusu pasirinkimas: ";
    int pasirinkimas; cin >> pasirinkimas;

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

    cout << "Pasirinkite duomenu ivedimo buda:\n1 - Rankiniu budu\n2 - Atsitiktiniai\n3 - Nuskaityti is failo\nJusu pasirinkimas: ";
    int ivestis; cin >> ivestis;

    string failas;
    int sortParam = 1, order = 1, metod = 1;
    double t_read = 0.0, t_sort = 0.0, t_split = 0.0, t_write = 0.0;

    if (ivestis == 3) {
        cout << "Iveskite failo pavadinima: "; cin >> failas;
        auto start_read = high_resolution_clock::now();
        if (useList) nuskaitytiIsFailo(failas, studentai_list);
        else nuskaitytiIsFailo(failas, studentai_vec);
        t_read = duration<double>(high_resolution_clock::now() - start_read).count();
    } else {
        if (useList) ivestiStudentus(studentai_list, ivestis);
        else ivestiStudentus(studentai_vec, ivestis);
        failas = "manual_input";
    }

    cout << "Pasirinkite galutinio balo skaiciavimo metoda:\n1 - Vidurkis\n2 - Mediana\n3 - Abu\nJusu pasirinkimas: ";
    cin >> metod;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (metod == 3) {
        cout << "Pagal ka rusiuoti?\n1 - Vidurki\n2 - Mediana\n"; cin >> sortParam;
    }
    cout << "Rikiuoti:\n1 - Didejanciai\n2 - Mazejanciai\n"; cin >> order;

    cout << "Pasirinkite studentu skirstymo strategija (T_split):\n";
    cout << "1 - Kopijavimas\n2 - Trynimas/Perkelimas\n3 - Efektyviausias\nJusu pasirinkimas: ";
    int splitStrategy; cin >> splitStrategy;

    if (useList) {
        t_sort = rikiuoti(studentai_list, sortParam, order);
        t_split = splitStudentus(studentai_list, vargsiukai, kietiakai, static_cast<SplitStrategy>(splitStrategy), sortParam);
    } else {
        t_sort = rikiuoti(studentai_vec, sortParam, order);
        t_split = splitStudentus(studentai_vec, vargsiukai, kietiakai, static_cast<SplitStrategy>(splitStrategy), sortParam);
    }

    auto start_write = high_resolution_clock::now();
    issaugotiIFaila("vargsiukai.txt", vargsiukai, metod);
    issaugotiIFaila("kietiakai.txt", kietiakai, metod);
    t_write = duration<double>(high_resolution_clock::now() - start_write).count();

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
