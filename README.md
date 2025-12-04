# Studentų Programos Projektas

## Apžvalga
Ši programa valdo studentų duomenis, skaičiuoja galutinius balus pagal vidurkį ir medianą, rikiuoja studentus, ir skirsto į grupes „vargsiukai“ ir „kietiakai“.  

Projekto versija: **v1.5**  
- Palaiko **abstrakčią bazinę klasę `Zmogus`**.  
- Studentas (`Student`) yra išvestinė klasė iš `Zmogus`.  
- Išsaugoma **v1.2 logika**: įvedimas, failų nuskaitymas, rikiavimas, skirstymas.  
- Įgyvendinta **trejų metodų taisyklė** (`Rule of Three`) Student klasėje.

---

## Klasių struktūra


- `Zmogus` yra abstrakti klasė, todėl negalima tiesiogiai kurti `Zmogus` objektų.  
- `Student` paveldi visus žmogaus atributus ir prideda galutinių balų skaičiavimą.  

---

## Programos funkcionalumas

| Funkcija | Aprašymas |
|----------|-----------|
| Įvedimas | Studentų įvedimas rankiniu būdu arba generuojant atsitiktinius duomenis |
| Failų nuskaitymas | Nuskaitymas iš `.txt` failų |
| Galutinių balų skaičiavimas | Vidurkis, mediana arba abu |
| Rikiavimas | Pagal vidurkį arba medianą, didėjimo / mažėjimo tvarka |
| Skirstymas į grupes | „Vargsiukai“ (< 5 balų) ir „Kietiakai“ (≥ 5 balų) |
| Išsaugojimas | Rezultatų išsaugojimas į failus `vargsiukai.txt` ir `kietiakai.txt` |

---


## Tikrinimas: klasės abstraktumas

<img width="458" height="241" alt="image" src="https://github.com/user-attachments/assets/2c426512-a0d7-4424-a58d-a0a5a90e1198" />

Tikrinimui buvo naudojamas toks kodas.



| Veiksmas | Ekrano nuotrauka | Rezultatas |
|----------|-----------------|------------|
| Student objektas sukurtas sėkmingai | <img width="421" height="37" alt="image" src="https://github.com/user-attachments/assets/135d6598-21fc-49d7-a172-91458c0dd3b3" /> | Student objektai veikia kaip tikėtasi |
| Bandymas sukurti Zmogus objektą (`Zmogus z;`) | <img width="514" height="51" alt="image" src="https://github.com/user-attachments/assets/59cd6d0f-e825-4e9f-9e9a-8e7df6048718" />| Kompiliavimo klaida – `Zmogus` abstrakti klasė |

### Išvados
- Negalima kurti `Zmogus` objektų (klaida kompiliavimo metu).  
- `Student` objektai vis dar kuriami sėkmingai, naudojant `Zmogus` bazę.


