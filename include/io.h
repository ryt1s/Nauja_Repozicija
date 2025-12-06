/**
 * @file io.h
 * @brief IO pagalbinės funkcijos: failų skaitymas/rašymas ir testinių failų generatorius.
 */


#ifndef IO_H
#define IO_H

#include "../include/student.h"
#include <vector>
#include <string>
#include <list>

void nuskaitytiIsFailo(const std::string& filename, std::vector<Student>& studentai);
void issaugotiIFaila(const std::string& filename, const std::vector<Student>& studentai, int metod);

void nuskaitytiIsFailo(const std::string& filename, std::list<Student>& studentai);
void issaugotiIFaila(const std::string& filename, const std::list<Student>& studentai, int metod);

/**
 * @brief Generuoja testinį failą su nurodytu studentų skaičiumi.
 * @param filename Išvesties failas
 * @param kiekStudentu Kiek sugeneruoti įrašų
 * @param kiekNd Kiek namų darbų (stulpelių)
 */

void generuotiFaila(const std::string& filename, int kiekStudentu, int kiekNd);
int inputSkaicius(const std::string& pranesimas, int min, int max);

#endif