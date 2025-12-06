#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../student.h"

// Testas – ar teisingai skaičiuojamas galutinis vidurkis
TEST_CASE("Galutinio balo skaičiavimas pagal vidurkį", "[student]") {
    Student s("Jonas", "Jonaitis", {10, 8, 9}, 9);

    REQUIRE(s.galVid() == Approx(0.4 * ((10 + 8 + 9) / 3.0) + 0.6 * 9).epsilon(0.001));
}

// Testas – ar teisingai skaičiuojama mediana
TEST_CASE("Medianos skaičiavimas", "[student]") {
    Student s("Petras", "Petraitis", {5, 7, 9}, 8);

    REQUIRE(s.galMed() == Approx(0.4 * 7 + 0.6 * 8).epsilon(0.001));
}

// Testas – ar copy constructor veikia (trejų taisyklė)
TEST_CASE("Copy constructor", "[student]") {
    Student a("Jonas", "Jonaitis", {10, 9}, 8);
    Student b = a;

    REQUIRE(b.vardas() == a.vardas());
    REQUIRE(b.pavarde() == a.pavarde());
    REQUIRE(b.paz() == a.paz());
    REQUIRE(b.egz() == a.egz());
}

// Testas – ar assignment operatorius veikia (trejų taisyklė)
TEST_CASE("Assignment operator", "[student]") {
    Student a("A", "AA", {1, 2, 3}, 4);
    Student b("B", "BB", {9, 9}, 10);

    b = a;

    REQUIRE(b.vardas() == "A");
    REQUIRE(b.pavarde() == "AA");
    REQUIRE(b.paz() == a.paz());
    REQUIRE(b.egz() == 4);
}