---
title: "Zpracování dat z IMU"
author: Macháček Tomáš
date: Jan 3, 2023
---

# Obsah

 - Hardware
 - Software
 - Průběh záznamu
 - Výsledky - přehled grafů
 - Možnosti, návrhy na zlepšení

# Hardware

 - ESP32
 - MPU9250 (MPU6050)
 - I2C, UART

# Schéma zapojení

![](pic/scheme.png){ width=75% }

# Software

 - C++ (termios, termbits)
 - python (matplotlib, imufusion)

# Průběh záznamu dat

 (a) board.conf
 (b) program
 (c) data/

# Grafy - Akcelerometr a gyroskop

![](pic/raw_data.png){ width=100% }

# Grafy - Eulerovy úhly

![](pic/euler_angles.png){ width=100% }

# Grafy - Zrychelní

![](pic/acceleration.png){ width=100% }

# Grafy - Rychlost

![](pic/velocity.png){ width=100% }

# Grafy - Pozice

![](pic/position.png){ width=100% }

# Grafy - Pozice ve 3D

![](pic/position_3D.png){ width=100% }

# Možnosti, návrhy na zlepšení

 - nakalibrováno na krátké záznamy (cca. 5 vteřin)
 - hrubá přesnost
 - zlepšení by poskytlo IMU s magnetometrem a kvalitnějšími senzory

# Děkuji za pozornost, dotazy?
