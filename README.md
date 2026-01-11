# CPC357-Project---IoT-Based-Automated-Farm-for-Sustainable-Cities

# IoT-Based Automated Farm for Sustainable Cities

---

##  Project Description
This project addresses the challenges of urban farming by developing an **IoT-Based Automated Vertical Farm**. [cite_start]The system automates essential maintenance tasks—such as climate control and rain protection—using real-time sensor data, making agriculture accessible and sustainable for city dwellers with limited space[cite: 21, 22].

The system utilizes an **ESP32 microcontroller** to monitor environmental conditions (Temperature, Humidity, Soil Moisture, and Rain). [cite_start]It communicates via **MQTT** over Wi-Fi to a Google Cloud VM, allowing users to monitor and control the farm through a custom **Web Dashboard**[cite: 56, 72].

### Key Features
* [cite_start]**Real-Time Monitoring:** Live tracking of temperature, humidity, soil moisture, and weather status[cite: 33].
* [cite_start]**Automated Rain Protection:** A servo motor automatically closes the roof when rain is detected[cite: 60, 61].
* [cite_start]**Active Climate Control:** A cooling fan activates automatically when temperature exceeds a user-defined threshold[cite: 63].
* **Smart Alerts:** Visual dashboard warnings when soil moisture drops below critical levels (<30%).
* **Remote Configuration:** Users can adjust the temperature threshold for the fan directly from the dashboard (Bidirectional MQTT).
* **Data Visualization:** Live graphing of temperature history using Chart.js.

---

## 🛠️ Hardware Requirements
[cite_start]The following components were used to build the prototype[cite: 77, 78, 79, 80, 81, 82]:

| Component | Model | Purpose |
| :--- | :--- | :--- |
| **Microcontroller** | Cytron Maker Feather AIoT S3 (ESP32) | Main processing unit & Wi-Fi connectivity. |
| **Temp Sensor** | DHT22 | [cite_start]Measures ambient temperature/humidity with high accuracy ($\pm0.5^\circ$C)[cite: 90]. |
| **Soil Sensor** | Capacitive Soil Moisture Sensor | Measures soil water content. |
| **Weather Sensor** | Rain Sensor Module | Detects precipitation to trigger roof closure. |
| **Actuator 1** | Micro Servo (SG90) | Controls the automated roof mechanism. |
| **Actuator 2** | DIY Cooling Fan | Provides active cooling via Relay control. |
| **Relay** | 1-Channel 5V Relay | Switches the high-power fan on/off. |

---

## 🔌 Pin Configuration
[cite_start]Wiring setup for the ESP32[cite: 109, 110]:

| Device | ESP32 Pin |
| :--- | :--- |
| **Rain Sensor** | GPIO 4 |
| **DHT22** | GPIO 6 |
| **Soil Moisture** | GPIO 8 |
| **Relay (Fan)** | GPIO 14 |
| **Servo (Roof)** | GPIO 21 |

---

## 💻 Software & Dependencies

### 1. Firmware (ESP32)
* **IDE:** Arduino IDE
* **Libraries Required:**
    * `WiFi.h` (Standard ESP32 Lib)
    * `PubSubClient.h` (by Nick O'Leary) - For MQTT communication.
    * `DHT.h` (by Adafruit) - For temperature reading.
    * `ESP32Servo.h` (by Kevin Harrington) - For servo control.

### 2. Backend (Server)
* [cite_start]**Host:** Google Cloud Platform (GCP) Compute Engine[cite: 72].
* **OS:** Debian/Linux.
* **Broker:** Eclipse Mosquitto.
    * *Configuration:* Must allow listeners on Port `1883` (TCP) and Port `9001` (WebSockets).

### 3. Frontend (Dashboard)
* **Languages:** HTML5, CSS3, JavaScript.
* **Libraries:**
    * `Paho MQTT` (mqttws31.min.js) - For WebSocket MQTT connections.
    * `Chart.js` - For rendering the real-time temperature graph.
    * `Google Fonts (Nunito)` - For UI styling.

---

## 🚀 Installation & Setup

### Step 1: Broker Configuration (GCP VM)
1.  Install Mosquitto on your Linux VM.
2.  Edit `mosquitto.conf` to enable WebSockets:
    ```text
    listener 1883
    allow_anonymous true
    
    listener 9001
    protocol websockets
    allow_anonymous true
    ```
3.  Open Firewall ports `1883` and `9001` in your Cloud Console.

### Step 2: Microcontroller Setup
1.  Open the `SmartFarm_ESP32.ino` file in Arduino IDE.
2.  Install the required libraries via Library Manager.
3.  Update the **Wi-Fi Credentials** (`ssid`, `pass`) and **MQTT Server IP**.
4.  Flash the code to the ESP32.

### Step 3: Dashboard Setup
1.  Open `index.html`.
2.  Ensure the `VM_IP` variable matches your Google Cloud External IP.
3.  Open the file in any modern web browser.

---

## 👥 Contributors
* [cite_start]**Muhammad Firdaus Bin Mohd Rosalan** (Matric: 163743) [cite: 11]
* [cite_start]**Muhammad Farid Azril Bin Mohd Faudzi** (Matric: 164665) [cite: 11]

---

## 📄 License
[cite_start]This project is developed for educational purposes under the School of Computer Sciences, Universiti Sains Malaysia[cite: 3].
