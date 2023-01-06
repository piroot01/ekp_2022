---
title: "Zpracování dat z IMU"
author: Macháček Tomáš
date: Jan 3, 2023
---

# Obsah

 - Vyčítání dat
 - Přenos dat do počítače
 - Zpracování do grafů
 - Průběh záznamu
 - Výsledky - přehled grafů

# 1. Vyčítání dat

 - ESP32
 - MPU9250
 - I2C

# 2. Přenos dat do počítače

 - UART
 - C++ (termios, termbits)

# 3. Zpracování dat

 - python
 - Madgwickův algoritmus (imufusion)
 - grafy (matplotlib)

# 4. Průběh záznamu dat

 (a) board.conf
 (b) program
 (c) data/

# 5. Grafy - Akcelerometr a gyroskop

![](pic/raw_data.png){ width=100% }

# 5. Grafy - Eulerovy úhly

![](pic/euler_angles.png){ width=100% }

# 5. Grafy - Zrychelní

![](pic/acceleration.png){ width=100% }

# 5. Grafy - Rychlost

![](pic/velocity.png){ width=100% }

# 5. Grafy - Pozice

![](pic/position.png){ width=100% }

# 5. Grafy - Pozice ve 3D

![](pic/position_3D.png){ width=100% }

# Děkuji za pozornost, dotazy?
