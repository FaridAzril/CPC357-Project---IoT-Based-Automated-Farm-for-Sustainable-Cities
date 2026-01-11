# IoT-Based Automated Farm for Sustainable Cities 


## Project Description
As cities become more crowded, finding space to grow fresh food is a challenge. This project addresses the issues of urban farming by developing an **IoT-Based Automated Vertical Farm**. The system automates essential maintenance tasks—such as climate control and rain protection—using real-time sensor data, making agriculture accessible and sustainable for city dwellers with limited space.

The system utilizes an **ESP32 microcontroller** to monitor environmental conditions (Temperature, Humidity, Soil Moisture, and Rain). It communicates via **MQTT** over Wi-Fi (2.4GHz) to a Google Cloud VM, allowing users to monitor and control the farm through a custom **Web Dashboard**.

### System Objectives
* **Automated Monitoring:** Monitors soil moisture and rain conditions to optimize water usage.
* **Crop Protection:** Automatically closes a roofing mechanism when rain is detected.
* **Active Climate Control:** Regulates temperature using an active cooling fan to prevent heat stress.
* **Sustainability:** Reduces resource wastage and supports green urban living.



##  Sustainable Development Goal (SDG) Impact
This project directly contributes to **SDG 11: Sustainable Cities and Communities**.
* **Green Zones:** Utilizes underused spaces (like balconies) to create productive green zones, reducing the "Urban Heat Island" effect.
* **Resource Efficiency:** Intelligent soil moisture monitoring prevents water wastage.
* **Food Security:** Reduces reliance on imported goods and the carbon footprint associated with shipping food.


##  Hardware Requirements
The following components were used to build the prototype:

| Component | Model | Purpose |
| :--- | :--- | :--- |
| **Microcontroller** | Cytron Maker Feather AIoT S3 (ESP32) | Main processing unit & Wi-Fi connectivity. |
| **Temp Sensor** | DHT22 | Measures ambient temperature/humidity. |
| **Soil Sensor** | Capacitive Soil Moisture Sensor | Measures soil water content (Analog/Digital). |
| **Weather Sensor** | Rain Sensor Module | Detects precipitation to trigger roof closure. |
| **Actuator 1** | Micro Servo (SG90) | Controls the automated roof mechanism (0-180°). |
| **Actuator 2** | DIY Cooling Fan | Provides active cooling via Relay control. |
| **Relay** | 1-Channel 5V Relay | Switches the high-power fan on/off. |



## Software & Dependencies

### 1. Firmware (ESP32)
* **IDE:** Arduino IDE
* **Libraries:** `WiFi.h`, `PubSubClient.h` (MQTT), `DHT.h` (Temperature), `ESP32Servo.h` (Servo Control).

### 2. Backend (Server)
* **Host:** Google Cloud Platform (GCP) Compute Engine.
* **Broker:** Eclipse Mosquitto (Configured for Port 1883 TCP & Port 9001 WebSockets).

### 3. Frontend (Dashboard)
* **Tech Stack:** HTML5, CSS3, JavaScript.
* **Libraries:** `Paho MQTT` (WebSockets), `Chart.js` (Data Visualization).


## Installation & Setup

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
4.  Upload the code to the ESP32.

### Step 3: Dashboard Setup
1.  Open `dashboard.html`.
2.  Ensure the `VM_IP` variable matches your Google Cloud External IP.
3.  Open the file in any modern web browser.



##  Dashboard Scenarios
The web dashboard provides real-time visualization and control. (See report Appendix for full images).

1.  **Default System View:** Displays "Sunny/Clear" weather, normal temperature, and "Half-Open" roof status.
2.  **Heat Stress Event:** When temperature > Threshold (e.g., 31°C), the Fan status turns **ON** and the Roof **Opens Fully**.
3.  **Rain Protection:** When rain is detected, the Weather card turns blue, and the Roof status changes to **"Closed (Rain)"**.
4.  **Low Moisture Warning:** When soil moisture drops < 32%, the Moisture card provides a visual warning to water the crops.
5.  **Remote Control:** Users can manually set the "Fan Threshold" temperature directly from the dashboard.


