<h1 align="center">
  🧊 Smart Cooling Pad ❄️
</h1>

<p align="center">
  <img src="https://media.giphy.com/media/Ll22OhMLAlVDb8UQWe/giphy.gif" width="120" height="120" alt="Cooling fan gif"/>
</p>

<p align="center">
  ⚡ Real-time CPU/GPU temperature-based fan control system using ESP32 + Python <br>
  💻 Built for smart power-saving and efficient cooling while working, coding, or gaming.
</p>

---

## 🧠 Features

- 🔁 **Real-time communication** between PC & ESP32 via UART
- 🌡️ **Temperature-based fan speed control**
- 🖥️ **OLED display** showing live temperature, fan PWM, and cooling status
- 🎮 Ideal for **gaming laptops** and **heavy development workloads**
- 🔌 **Energy-efficient**: Fans only run when needed

---

## 📷 Project Demo

🧊 **Live Cooling in Action (Simulated View)**  
Real-time temperature shown on OLED and fan speed adapting instantly based on system load.

<p align="center">
  <img src="https://giffer.com/embed/26186" width="280" alt="Fan cooling demo"/>
  <img src="https://giffer.com/embed/26187" width="280" alt="OLED display demo"/>
</p>
---

🎯 **How It Works:**
- CPU/GPU temp is fetched on PC (via Python)
- Sent over USB UART to ESP32
- ESP32 dynamically sets **PWM speed of two fans**
- OLED shows:
  - 🌡 Current temperature
  - 🌀 Fan PWM (0–255)
  - ⚙️ Status: OFF / LOW / MEDIUM / HIGH / MAX

---

💡 **Use Cases:**
- Save laptop power when idle
- Turn ON fans *only* when your apps/games heat up
- Prevent overheating during long coding/gaming sessions
---

## 📊 Cooling Logic

| Temperature Range | Fan PWM | Status |
|-------------------|---------|--------|
| **< 45°C**        | 0       | OFF    |
| **45–55°C**       | 50–140  | LOW    |
| **55–70°C**       | 140–215 | MEDIUM |
| **70–80°C**       | 215–255 | HIGH   |
| **> 80°C**        | 255     | MAX    |

⚙️ Controlled by ESP32 PWM on two fan pins (GPIO 4 & 5).

---

## 🧰 Technologies Used

- **ESP32 (Arduino C++)**
  - PWM Fan control
  - I2C OLED Display (SSD1306)
  - Serial UART data reception
- **Python (PC-Side App)**
  - `pyserial` to send CPU/GPU temp to ESP32
- **Hardware**
  - Dual 5V brushless fans
  - Adafruit 128x64 OLED (I2C)
  - USB-powered custom PCB pad

---

## 🚀 Real-Time Monitoring

> The Python script fetches your CPU/GPU temperature (e.g., using `psutil`, OpenHardwareMonitor) and sends it to the ESP32 every few seconds.

The ESP32:
- Adjusts fan speed accordingly
- Displays real-time temp and fan status on OLED
- Ensures minimal noise and **only uses power when needed**

---

## 📦 How to Run

### ✅ On the PC (Python)
```bash
pip install pyserial
python main.py  # Replace with your temp-sending script
