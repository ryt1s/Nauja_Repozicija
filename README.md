# First-Project v2.0

## Aprašymas
Ši programa skirta studentų duomenų tvarkymui, įskaitant namų darbų ir egzamino balus.  
Projektas palaiko kelias versijas:  
- **v1.1** - perėjimas iš `struct` į `class`
- **v1.2** – Rule of three implementavimas  
- **v1.5** – pridėta abstrakti bazinė klasė `Zmogus`  
- **v2.0** – dokumentacija su Doxygen ir Unit testai su Catch2 v2

Bazinė klasė `Zmogus` yra **abstrakti**, todėl jos objektų kurti negalima. Iš jos paveldi klasė `Student`.

---

##  Paleidimo instrukcijos

### 1. Kompiliavimas

| Tikslas | Komanda (naudojant `g++`) |
| :--- | :--- |
| **Pagrindinei programai** | `g++ src/main.cpp src/student.cpp src/io.cpp -Iinclude -o program.exe  ` |
| **Unit testams** | `g++ -std=c++17 tests/test_student.cpp src/student.cpp src/io.cpp -Iinclude -o test_runner` |

### 2. Programos paleidimas

* **Pagrindinė programa:**
    ```bash
    ./program.exe
    ```
* **Demo abstrakčiai klasei:**
    ```bash
    ./demo_abstract.exe
    ```

---

##  Unit testai

Unit testai parašyti su **Catch2 v2*. Testai patikrina:
* `Student` konstruktorius
* Balų skaičiavimo metodus (`galVid`, `galMed`)

Paleidimo komanda:
```bash
./test_runner
```
##  Doxygen dokumentacija

Doxygen dokumentacija sugeneruota naudojant `Doxyfile`.

* **Generavimo komanda:**
    ```bash
    doxygen Doxyfile
    ```
* **HTML katalogas:** `docs/html/index.html`

---

##  Versijų istorija

| Versija | Pakeitimai |
| :--- | :--- |
| **v1.2** | Originali versija su failų skaitymu, rašymu, balų skaičiavimu. |
| **v1.5** | Pridėta **abstrakti klasė `Zmogus`** ir `Student` paveldėjimas. |
| **v2.0** | **Doxygen dokumentacija**, **Unit testai**, projekto struktūros pertvarkymas. |

---

##  Išvados

* `Zmogus` klasė yra **abstrakti**, jos objektų kurti negalima.
* `Student` klasė **paveldi** `Zmogus` ir palaiko originalius metodus iš v1.2.
* **Doxygen dokumentacija** pateikia kodo struktūros ir metodų aprašymus.
* **Unit testai** demonstruoja, kad funkcijos veikia teisingai.
* Projekto struktūra yra **švari** be jokių IDE failų.

## Programos funkcionalumas

| Funkcija | Aprašymas |
|----------|-----------|
| Įvedimas | Studentų įvedimas rankiniu būdu arba generuojant atsitiktinius duomenis |
| Failų nuskaitymas | Nuskaitymas iš `.txt` failų |
| Galutinių balų skaičiavimas | Vidurkis, mediana arba abu |
| Rikiavimas | Pagal vidurkį arba medianą, didėjimo / mažėjimo tvarka |
| Skirstymas į grupes | „Vargsiukai“ (< 5 balų) ir „Kietiakai“ (≥ 5 balų) |
| Išsaugojimas | Rezultatų išsaugojimas į failus `vargsiukai.txt` ir `kietiakai.txt` |


