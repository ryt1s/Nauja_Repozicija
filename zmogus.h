
#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
#include <iostream>

/**
 * @class Zmogus
 * @brief Bazinė abstrakti klasė žmogui.
 *
 * Ši klasė yra abstrakti, todėl negalima sukurti jos objektų tiesiogiai.
 * Naudojama kaip bazė Student klasės išvedimui.
 */
class Zmogus {
protected:
    std::string vardas_; /**< Vardas */
    std::string pavarde_; /**< Pavardė */

public:
    /** @brief Numatytasis konstruktorius */
    Zmogus() = default;

     /**
     * @brief Konstruktorius su vardu ir pavarde.
     * @param vardas Žmogaus vardas.
     * @param pavarde Žmogaus pavardė.
     */
    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

    /** @brief Virtualus destruktorius */
    virtual ~Zmogus() = default;
     /** @brief Grąžina vardą */
    std::string vardas() const { return vardas_; }
    /** @brief Grąžina pavardę */
    std::string pavarde() const { return pavarde_; }
    /** @brief Abstrakti funkcija, kurią turi įgyvendinti išvestinė klasė */
    virtual void print() const = 0;
};

#endif
