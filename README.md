# 🚀 Ignition V2.0: Pure Bare-Metal ECU Simulator with FreeRTOS

**A high-performance Engine Control Unit (ECU) simulator built from the registers up on the STM32F446RE.**

---

## 🛠️ Project Overview

**Ignition V2.0** is the ultimate evolution of a multitasking ECU simulator. While V1.0 was built using the standard ST HAL, **V2.0 represents a complete "HAL Purge."** Every peripheral driver was rewritten from scratch at the register level to achieve maximum efficiency, lower memory footprint, and high-speed execution.


![photo_2026-02-11_19-32-28](https://github.com/user-attachments/assets/e0f52c18-ef4c-4406-97d7-8bf302c7c269)

---

## 🧠 The "HAL Purge": Engineering Beyond the Abstraction

The core mission of V2.0 was to remove all dependencies on the `stm32f4xx_hal` libraries. This required performing "brain surgery" on the system architecture:

*   **⚡ 180MHz Manual Clock Config:** Bypassed `HAL_RCC_OscConfig` to manually tune the PLL, Flash Latency (5WS), and Power Over-drive mode.
*   **📡 Custom DMA-to-RAM Pipeline:** Replaced `HAL_ADC_Start_DMA` with a custom register-level driver that handles multi-channel scan modes and circular data transfers with zero CPU overhead.
*   **🗣️ Interrupt-Driven UART:** Built a non-blocking UART driver using custom Ring Buffers, replacing the blocking `HAL_UART_Transmit` calls.
*   **🖥️ TFT Library Porting:** Refactored a 3rd-party ILI9341 driver by stripping out all HAL SPI and GPIO calls, replacing them with my own high-speed bare-metal implementations.

---

## 🏗️ System Architecture
 
![photo_2026-02-11_19-32-23](https://github.com/user-attachments/assets/4ee336dd-9221-4e8c-ad20-fe689f50bb27)

The ECU manages five concurrent high-priority tasks using **FreeRTOS**:

1.  **ADC-DMA Task:** Continuously monitors Engine Temp and Throttle position via a 15MHz sampled DMA pipeline.
2.  **Logic Engine:** Calculates RPM and Cooling requirements based on real-time sensor data.
3.  **Dashboard Task:** Renders a high-refresh-rate UI using my custom bare-metal SPI driver.
4.  **Fuel Management:** Precise fuel level calculation using Timer Input Capture and Binary Semaphores.
5.  **Actuator Control:** Manages the 3-stage fan cooling system via GPIO-driven relay modules.

---

## 📂 Repository Structure

The engineering effort is visible in the **`Core`** directory:

*   📂 **`Core/mydriver/`**: The pure bare-metal library created for this project (`gpiox.c`, `MyDMA.c`, `MyUsart.c`, `MyTimer.c`, `MyAdcDMA.c`).
*   📂 **`Core/Inc` & `Core/Src`**: Application logic and the refactored ILI9341 GFX library.
*   📂 **`Core/legacy_driver/`**: Archived Phase 1 HAL-based code for performance benchmarking and reference.
*   📂 **`Core/ThirdParty/FreeRTOS`**: Manually integrated kernel source.

---

### 📦 The Reusable SDK
I have extracted the drivers from this project into a standalone, modular SDK for the F446RE.  
🔗 **Explore the Library:** [stm32-baremetal-drivers-F446RE](https://github.com/BavinnK/stm32-baremetal-drivers-F446RE)

---

## 🌍 Resilience and Background

Developed in the Kurdistan region of Iraq, this project was born from a desire to master the "magic" inside automotive control modules. Every register bit was verified using the **700+ page Reference Manual**, overcoming geographic and toolchain limitations through persistence and low-level mastery.

---

## 🏁 Status: OPERATIONAL (180MHz)
Ignition V2.0 is a production-grade demonstration of bare-metal firmware design and real-time operating system integration.
