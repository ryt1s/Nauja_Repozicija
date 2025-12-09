#include "../include/zmogus.h"
#include "../include/Student.h"
#include <iostream>

int main() {
    std::cout << "Demonstracija, kad klase Zmogus yra abstrakti:\n";

    // Zmogus z;

    Student s("Jonas", "Jonaitis", {8, 9, 10}, 9);
    std::cout << "Studentas sukurtas:\n";
    std::cout << "Vardas: " << s.vardas() << ", Pavarde: " << s.pavarde() 
              << ", Galutinis (Vid.): " << s.galVid() 
              << ", Galutinis (Med.): " << s.galMed() << "\n";

    return 0;
}
