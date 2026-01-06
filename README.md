# Snake Game cu Display OLED si Joystick

### Autor: Campean Bogdan

### Grupa: 30237

### Facultatea de Automatica si Calculatoare

### 6 ianuarie 2026


## Cuprins

- 1 Introducere
   - 1.1 Descrierea Proiectului
   - 1.2 Obiective
- 2 Hardware Components
   - 2.1 Lista de Componente
   - 2.2 Descrierea Conexiunilor
      - 2.2.1 Display-ul OLED (Protocol I2C)
      - 2.2.2 Joystick-ul Analogic
- 3 Software
   - 3.1 Control si Input (Joystick Logic)
   - 3.2 Miscare si Prevenirea Erorilor
   - 3.3 Generarea Mancarii
   - 3.4 Detectia Coliziunilor (Game Over)
- 4 Testare
   - 4.1 Testare Hardware
   - 4.2 Testare Functionala


## 1 Introducere

### 1.1 Descrierea Proiectului

Acest proiect implementeaza jocul clasic Snake pe un sistem embedded bazat pe Arduino.
Jocul este afisat pe un ecran OLED monocrom si controlat prin intermediul unui joystick ana-
logic. Scopul proiectului este de a demonstra interactiunea in timp real dintre intrari (senzori),
logica de procesare (microcontroller) si iesiri (display), intr-un format interactiv si distractiv.
