<div align="center">

# 🧠 Simulated EEG BCI-Controlled Prosthetic Hand
**Translating Brain Signals into Physical Movement (Simulation Approach)**

[![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)]()
[![Platform](https://img.shields.io/badge/Software-MATLAB_&_Arduino-blue?style=for-the-badge)]()
[![Simulation](https://img.shields.io/badge/Simulation-NDS_&_MediaPipe-lightgrey?style=for-the-badge)]()

*A Senior Graduation Project — Misr University for Science & Technology (MUST)*
<br>Faculty of Engineering | Biomedical Engineering Department

</div>

---

## 📖 Overview
This project introduces a **simulated Brain–Computer Interface (BCI)** system designed to assist upper-limb amputees. By decoding simulated neural activity, the system translates Motor Imagery (MI) into physical movement commands. The core innovation lies in a high-accuracy **MATLAB Signal Processing Pipeline** integrated with an **Artificial Neural Network (ANN)**, which drives a low-cost, high-torque prosthetic assembly via an Arduino UNO controller.

> **Note on Implementation:** Due to a technical malfunction with the planned EEG device preventing real signal acquisition, we adapted the project to use a highly sophisticated simulated BCI approach. This allowed us to maintain the complete software and hardware pipeline while simulating the neural input.

---

## ⚙️ Simulated System Architecture
To simulate the BCI input accurately, we integrated several advanced open-source tools to generate and stream neural-like data:

1. **Simulated Data Acquisition (MediaPipe):** We used Google's MediaPipe Hand Landmarker to capture 21 hand key points via camera tracking. This behavioral data acts as the basis for our simulated motor intentions.
2. **Simulated Data Processing (Neural Data Simulator - NDS):** We utilized the [Neural Data Simulator (NDS)](https://github.com/agencyenterprise/neural-data-simulator), an open-source Python package designed to generate real-time electrophysiology data. NDS translates the kinematics from MediaPipe into simulated 14-channel EEG-like waveforms (AF3, F7, F3, FC5, T7, P7, O1, O2, P8, T8, FC6, F4, F8, AF4).
3. **Data Streaming (Lab Streaming Layer - LSL):** The simulated neural data is streamed in real-time to MATLAB using [liblsl-Matlab](https://github.com/labstreaminglayer/liblsl-Matlab), effectively bridging the simulated signal source and our processing hub.
4. **Processing & Decoding (MATLAB):** MATLAB receives the LSL stream, processes the signals, and uses a Multi-layer Perceptron (MLP) Artificial Neural Network to classify the motor imagery.
5. **Actuation (Arduino & Hardware):** Classified commands are sent via Serial to an Arduino Uno, which drives high-torque metal gear servos (MG996R) using PWM to articulate the 3D-printed fingers.

---

## 🧠 Neural Network Performance
Our Artificial Neural Network (ANN) was trained using a back-propagation algorithm to map the complex, non-linear relationships of the simulated EEG features:
- **Average Classification Accuracy:** 82.1%
- **Training Convergence:** Demonstrated a consistent decline in Mean Squared Error (MSE) across epochs, indicating successful learning without overfitting.
- **Regression Analysis:** Achieved stable R-values across Training, Validation, and Testing phases, proving a strong correlation between targets and outputs.
- **Error Distribution:** Normal distribution of errors around zero, confirming the model is unbiased toward any specific output class.

---

## 🛠️ Hardware Integration
- **Microcontroller:** Arduino Uno R3 (ATmega328P, 16 MHz)
- **Actuators:** MG996R Metal Gear Servo Motors (11 kg/cm torque at 6V, 180° rotation)
- **Prosthetic Hand Design:** A lightweight, 3D-printed PLA assembly utilizing a bio-mimetic tendon-like structure. Nylon tension strings handle flexion, while a spring-return mechanism manages extension.

---

## 🚀 Future Roadmap
Our project successfully demonstrates a full-loop BCI solution (via simulation) translating neural motor imagery into mechanical grasping. To advance this foundation, we plan the following:
- [ ] **Real EEG Integration:** Transition from simulated data back to live EEG acquisition.
- [ ] **Sensory Feedback:** Integrate pressure sensors for tactile sensation.
- [ ] **Deep Learning:** Transition to LSTM networks for time-series optimization.
- [ ] **Portability:** Replace the PC processing hub with a Raspberry Pi for standalone use.
- [ ] **Cloud Integration:** Implement remote monitoring and subject training data logs.

---

## 👥 The Team
**Supervisor:** Dr. Islam A. Foad

---

## Special Credits and Huge Thanks to these Github Repos:
**NDS:** https://github.com/agencyenterprise/neural-data-simulator/

**liblsl-Matlab:**: https://github.com/labstreaminglayer/liblsl-Matlab/
