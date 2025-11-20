# Studentų Programa (Versija 1.2)

## Aprašas

Ši programa skirta valdyti studentų duomenis: įvesti, rikiuoti pagal galutinį balą (vidurkį arba medianą), skirstyti į grupes („vargsiukai“ ir „kietiakai“) bei išsaugoti į failus. Programoje galima pasirinkti konteinerio tipą (`std::vector` arba `std::list`) ir skirstymo strategiją.  

### Veiksmai programoje

1. **Konteinerio pasirinkimas** – vartotojas gali pasirinkti `vector` arba `list`.  
2. **Veiksmo pasirinkimas** – įvesti/atsitiktinai sugeneruoti studentus arba sugeneruoti testinius failus.  
3. **Duomenų įvedimas** – galima pasirinkti vieną iš trijų būdų:  
   - Rankiniu būdu  
   - Atsitiktiniai duomenys  
   - Nuskaitymas iš failo  

4. **Galutinio balo skaičiavimo metodas** – galima pasirinkti vidurkį, medianą arba abu.  
5. **Rikiavimo tvarka** – didėjimo arba mažėjimo tvarka pagal pasirinktą balo metodą.  
6. **Studentų skirstymo strategija** – kopijavimas į du naujus konteinerius, perkėlimas į vieną naują konteinerį arba efektyviausias metodas.  
7. **Rezultatų išsaugojimas** – studentų grupės išsaugomos į failus `vargsiukai.txt` ir `kietiakai.txt`.  

---

## Perdengti metodai

Programa naudoja perdengtus įvesties ir išvesties operatorius `Student` klasėje:

### Įvesties operatorius (`operator>>`)

- Leidžia įvesti `Student` objektus naudojant standartinę įvestį (`cin`) arba failus (`ifstream`).  
- Vartotojas gali įvesti studento pavardę, vardą, namų darbų įvertinimus ir egzamino balą.  
- Šis operatorius naudoja klasės metodą `readStudent`, kuris atlieka faktinį įvedimą ir galutinių balų skaičiavimą.  
