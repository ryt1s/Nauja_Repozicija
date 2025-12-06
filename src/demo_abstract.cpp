#include "Zmogus.h"
#include "Student.h"
#include <iostream>

int main() {
    std::cout << "Demonstrating that Zmogus is abstract:\n";

    // Zmogus z;

    Student s("Jonas", "Jonaitis", {8, 9, 10}, 9);
    std::cout << "Student created successfully:\n";
    std::cout << "Vardas: " << s.vardas() << ", Pavarde: " << s.pavarde() 
              << ", Galutinis (Vid.): " << s.galVid() 
              << ", Galutinis (Med.): " << s.galMed() << "\n";

    return 0;
}
