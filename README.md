# ToolBot - Line Follower Robot with Blynk-Controlled Drawers

## Objective
The goal of this project was to design and build an autonomous **line follower robot** capable of navigating a predefined path, detecting the **destination**, and automatically opening drawers using a **servo mechanism**. The robot also features **obstacle detection** using ultrasonic sensors, stopping when an obstacle is detected and sending a notification via the **Blynk app**. Integration with Blynk allows remote control for starting/stopping the robot, manually opening drawers, and monitoring status. This project combines robotics, embedded systems, and IoT-based remote interaction, providing hands-on experience in hardware-software integration.

![Concept](link-to-your-hardware-image)

---

### Skills Learned

- Programming microcontrollers (Arduino Uno, ESP8266) for robotics and IoT applications.  
- Implementing line following algorithms using **two IR/TCRT5000 sensors**.  
- Controlling DC motors with an L298N motor driver and PWM signals.  
- Servo control for actuating mechanical components (drawers).  
- Integrating **ultrasonic sensors** for obstacle detection and notifications.  
- Integrating **Blynk app** for mobile control, notifications, and remote operations.  
- Debugging sensor-based robotic systems and combining multiple modules (motors, sensors, WiFi) seamlessly.  

---

### Tools Used

- **Arduino Uno** — main microcontroller for robot control.  
- **ESP8266 / NodeMCU** — WiFi module for Blynk integration.  
- **L298N Motor Driver** — controlling DC motors for movement.  
- **DC Motors** — propulsion for the robot.  
- **TCRT5000 / IR Sensors (2)** — line detection (left & right).  
- **Ultrasonic Sensors (2)** — front and back obstacle detection.  
- **SG90 Servo Motor** — drawer actuation.  
- **Blynk App** — mobile control for robot start/stop, drawer operation, obstacle notifications.  
- **Arduino IDE** — programming and uploading code to Arduino.  

---

## Steps

### 1. Hardware Setup and Obstacle Detection
The robot chassis was assembled with:  
- Two **DC motors** connected via an L298N motor driver  
- Two **IR sensors** (left & right) for line following  
- Two **ultrasonic sensors** (front & back) for obstacle detection  
- An **SG90 servo motor** mounted for drawer operation  
- Arduino Uno as the main controller and ESP8266 for Blynk integration  

The **ultrasonic sensors** continuously monitor the front and back for obstacles. If an obstacle is detected within a set distance, the robot **stops immediately** and sends a **notification via the Blynk app**. This ensures safe operation and allows remote monitoring of obstacles while the robot navigates the path.


---

### 2. Sensor Calibration and Line Following
The IR sensors were calibrated to detect the line effectively. Basic line-following logic was implemented:  
- **Left sensor off line → turn right**  
- **Right sensor off line → turn left**  


---

### 3. Obstacle Detection
The robot continuously monitors **front and back ultrasonic sensors** for obstacles. If an obstacle is detected within a certain distance, the robot stops and sends a **Blynk notification**.


---

### 4. Destination Detection
When the robot reaches the **destination** (e.g., T-shaped ending), both IR sensors detect the line simultaneously. The robot stops and triggers the servo to open the drawers.

---

### 5. Drawer Actuation
The SG90 servo is programmed to rotate to the **open position** when the robot reaches the destination or when commanded manually through the Blynk app. After a defined period, the servo returns to the closed position.

---

### 6. Blynk Integration
The Blynk app provides remote interaction:  
- **Start/Stop robot** via V0 button.  
- **Manual drawer open** via V1 button.  
- **Obstacle detection notifications** via Blynk push notifications.  
- **Status updates** sent to V3 virtual pin.  

---

### 7. Conclusion
This project demonstrates **integration of robotics, embedded systems, and IoT**. It combines sensor-based autonomous movement, obstacle detection, and remote mobile control, illustrating how physical devices can be monitored and controlled over the internet. The project reinforces **problem-solving, hardware debugging, and software-hardware integration skills**.
