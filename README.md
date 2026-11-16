# System Alarmowy na Arduino z Klawiaturą Matrycową

System alarmowy oparty na maszynie stanów skończonych (FSM) dla platformy Arduino. Projekt wykorzystuje klawiaturę matrycową 4x4 do wpisywania kodu PIN, czujnik ruchu lub otwarcia drzwi, diody sygnalizacyjne LED oraz syrenę (buzzer).

---

## Funkcje

* **Ochrona kodem PIN:** Uwierzytelnianie za pomocą 4-cyfrowego hasła (domyślnie `1234`) zatwierdzanego przyciskiem `#`.
* **Opóźnienie na wyjście i wejście:** System daje 5 sekund na opuszczenie pomieszczenia po uzbrojeniu oraz 5 sekund na rozbrojenie alarmu po wykryciu ruchu.
* **Sygnalizacja wizualna i dźwiękowa:** Dedykowane diody LED informujące o stanie uzbrojenia, odliczaniu oraz alarmie, wspierane sygnałem dźwiękowym o częstotliwości 500 Hz.
* **Nieblokujące odmierzanie czasu:** Wykorzystanie funkcji `millis()` zamiast `delay()`, dzięki czemu klawiatura działa płynnie i bez opóźnień podczas odliczania oraz trwania alarmu.

---

## Wymagany sprzęt

* **Mikrokontroler:** Arduino Uno (lub kompatybilny)
* **Wejście:** Klawiatura membranowa/matrycowa 4x4
* **Czujnik:** Czujnik ruchu PIR lub kontaktron (wyzwalany stanem wysokim `HIGH`)
* **Wyjścia:** 
  * 3x dioda LED (wraz z odpowiednimi rezystorami, np. 220Ω)
  * 1x buzzer piezoelektryczny

---

## Schemat podłączenia (Pinout)

| Komponent | Pin Arduino | Tryb | Opis |
| :--- | :---: | :---: | :--- |
| **Wiersze klawiatury (1–4)** | `9, 8, 7, 6` | Wejście/Wyjście | Piny wierszy matrycy |
| **Kolumny klawiatury (1–4)** | `5, 4, 3, 2` | Wejście/Wyjście | Piny kolumn matrycy |
| **Dioda LED Alarmu** | `10` | `OUTPUT` | Miga co sekundę podczas aktywnego alarmu |
| **Dioda LED Opóźnienia** | `11` | `OUTPUT` | Świeci podczas 5-sekundowego odliczania (uzbrajanie/rozbrajanie) |
| **Czujnik (Wyzwalacz)** | `12` | `INPUT` | Uruchamia odliczanie do rozbrojenia po wykryciu stanu `HIGH` |
| **Dioda LED Uzbrojenia** | `13` | `OUTPUT` | Sygnalizuje pełne uzbrojenie systemu |
| **Buzzer** | `A3` | `OUTPUT` | Generuje dźwięk o częstotliwości 500 Hz podczas alarmu |

---

## Zasada działania (Maszyna stanów)

Program działa w oparciu o pięć zdefiniowanych stanów:

1. **`STATE_Roz` (Rozbrojony):** System jest w stanie spoczynku. Wpisz 4-cyfrowy kod PIN i zatwierdź go przyciskiem `#`, aby rozpocząć uzbrajanie.
2. **`STATE_Zbr` (Opóźnienie uzbrojenia):** Pin `11` przechodzi w stan wysoki (`HIGH`) na **5 sekund**, dając czas na opuszczenie strefy przed aktywacją czujnika.
3. **`STATE_Uzb` (Uzbrojony):** Zapala się dioda na pinie `13`. Gdy czujnik na pinie `12` wykryje ruch (stan `HIGH`), system przechodzi w tryb oczekiwania na rozbrojenie.
4. **`STATE_Rozbr` (Opóźnienie rozbrojenia):** Zapala się dioda na pinie `11`. Masz **5 sekund** na wpisanie poprawnego kodu PIN i wciśnięcie `#`. Wpisanie błędnego kodu lub przekroczenie czasu natychmiast uruchamia alarm.
5. **`STATE_Alarm` (Alarm):** Buzzer (`A3`) emituje dźwięk 500 Hz, a dioda alarmowa (`10`) miga przez **20 sekund**. Po tym czasie system automatycznie wraca do stanu uzbrojenia (`STATE_Uzb`).

---

## Instalacja i uruchomienie

1. **Zainstaluj bibliotekę Keypad:**
   * Otwórz środowisko Arduino IDE.
   * Przejdź do **Szkic > Dołącz bibliotekę > Zarządzaj bibliotekami...**
   * Wyszukaj **`Keypad`** (autorstwa Mark Stanley, Alexander Brevig) i kliknij **Instaluj**.
2. **Zmiana kodu PIN (opcjonalnie):**
   * Znajdź poniższą linijkę w kodzie i zmień wartość `"1234"` na własne 4-cyfrowe hasło:
     ```cpp
     const String correctPassword = "1234";
     ```
3. **Wgrywanie kodu:**
   * Podłącz płytkę Arduino do komputera przez USB, wybierz odpowiedni port oraz model płytki i kliknij **Wgraj**.

---

## Licencja

Ten projekt jest udostępniany na licencji [MIT](LICENSE).
