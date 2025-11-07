## Programos našumo palyginimas: Struct vs Class

Atliekant ankstesnės (Struct) ir dabartinės (Class) realizacijos palyginimą, buvo matuojamas veikimo laikas naudojant vieną fiksuotą konteinerį (`vector`) ir pačią greičiausią dalijimo strategiją. Testai atlikti su 1 000 000 ir 10 000 000 įrašų failais.

| Konteineris | Duomenų tipas | Failas | Nuskaitymas (s) | Rūšiavimas (s) | Skaidymas (s) | Išvedimas (s) | TESTAVIMO LAIKAS (s) |
|------------|---------------|--------|----------------|----------------|---------------|----------------|--------------------|
| vector     | Struct        | 1M     | 2.48           | 3.85           | 0.18          | 0.99           | 7.50               |
| vector     | Struct        | 10M    | 26.06          | 45.46          | 1.71          | 10.18          | 83.41              |
| vector     | Class         | 1M     | 1.19           | 1.92           | 0.09          | 0.39           | 3.58               |
| vector     | Class         | 10M    | 13.73          | 24.39          | 0.84          | 4.62           | 43.58              |

> Pastaba: pateikti rezultatai – vidurkiai iš 5 testavimų.  

**Išvados:**  
- Naudojant klasę Student, programa veikia beveik dvigubai greičiau nei su struct.  
- Skaitant didesnius failus (10M įrašų), skirtumas dar ryškesnis.  
- Optimaliausia konteinerio pasirinkimas: `vector`, o efektyviausia dalijimo strategija pritaikoma pagal klasės metodus.

- ## Programos našumo analizė pagal kompiliatoriaus optimizacijos lygius

| Optimizacijos lygis | Failas | Nuskaitymas (s) | Rūšiavimas (s) | Skaidymas (s) | Išvedimas (s) | TESTAVIMO LAIKAS (s) |
|-------------------|--------|----------------|----------------|---------------|----------------|--------------------|
| O1                | 1M     | 1.25           | 2.00           | 0.09          | 0.41           | 3.75               |
| O2                | 1M     | 1.20           | 1.95           | 0.09          | 0.40           | 3.64               |
| O3                | 1M     | 1.18           | 1.92           | 0.09          | 0.39           | 3.58               |



## Eksperimentinė analizė – optimizacijos flag'ai

### 1. Naudojant Class duomenų tipą

| Konteineris | Duomenų Tipas | Optim. lygis | Nuskaitymas (s) | Rūšiavimas (s) | Skaidymas (s) | Išvedimas (s) | TESTAVIMO LAIKAS (s) |
|-------------|---------------|--------------|-----------------|----------------|---------------|----------------|---------------------|
| vector      | Class         | O1           | 6.864679        | 1.248890       | 0.224021      | 3.888980       | 12.226488           |
| vector      | Class         | O2           | 6.312110        | 1.127600       | 0.176412      | 3.821162       | 11.437284           |
| vector      | Class         | O3           | 6.308422        | 1.089155       | 0.170494      | 4.101546       | 11.669617           |

### 2. Naudojant Struct duomenų tipą

| Konteineris | Duomenų Tipas | Optim. lygis | Nuskaitymas (s) | Rūšiavimas (s) | Skaidymas (s) | Išvedimas (s) | TESTAVIMO LAIKAS (s) |
|-------------|---------------|--------------|-----------------|----------------|---------------|----------------|---------------------|
| vector      | Struct        | O1           | 14.537979       | 2.677903       | 0.380136      | 9.327177       | 26.923195           |
| vector      | Struct        | O2           | 12.283420       | 2.391692       | 0.433014      | 9.585143       | 24.693269           |
| vector      | Struct        | O3           | 12.953310       | 2.196825       | 0.348954      | 8.898430       | 24.397519           |


