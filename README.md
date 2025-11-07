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
