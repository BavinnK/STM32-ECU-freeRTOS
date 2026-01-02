# Bevin: A Diabolical ECU Simulator with FreeRTOS

**Bevin** is an embedded systems project that transforms a Nucleo-F446RE board into a functional, multi-tasking Engine Control Unit (ECU) simulator. This project was born from a passion for automotive engineering and a deep curiosity about how the complex digital systems in modern vehicles manage hundreds of sensors and actuators in real-time. The core mission is to demonstrate foundational Operating System concepts in a practical, hands-on application.

The entire system is built in C, leveraging a manual, low-level HAL (Hardware Abstraction Layer) approach and the FreeRTOS real-time kernel.

## The Journey and Motivation

My journey into this project began from experience in the automotive service industry. I was fascinated by the engine control modules that act as the "brain" of a car, orchestrating everything from fuel injection to cooling systems. How could a single processor handle so much data concurrently? This question led me to explore the world of embedded operating systems.

The initial inspiration came from the simplicity of the Arduino `setup()` and `loop()` model. While powerful, this "super-loop" architecture follows a "first-come, first-served" sequential execution model. I realized that in a critical system like an ECU, a long-running, non-critical task (like updating a display) could starve a vital, high-priority task (like responding to an overheat condition). This potential for task starvation is a catastrophic failure mode.

This project, therefore, is a direct answer to that problem. By implementing a real-time operating system (RTOS), we can move from a simple sequential loop to a truly pre-emptive, priority-based multitasking system, guaranteeing that critical tasks always get the CPU time they need.

It's important to note the distinction: this is **multitasking**, not multi-processing. We are managing multiple concurrent software tasks on a **single CPU core**. Multi-processing would require multiple physical cores.

## Development Challenges

This project was developed under a number of unique constraints:
*   **Hardware Limitations:** Based in Iraq, access to a wide variety of development boards and components is limited. The Nucleo-F446RE was chosen for its availability and powerful feature set.
*   **Software & Toolchain:** The initial development was severely hampered by a broken STM32CubeIDE installation due to geo-restrictions on required downloads. This was resolved using a VPN, but it highlighted the challenges of working with locked-down development ecosystems. All subsequent work, including the integration of the FreeRTOS kernel and display libraries, was done manually to ensure full control and understanding of the system's architecture.

## Core Concepts Demonstrated
This project serves as a hands-on implementation of key OS principles:
- **Pre-emptive Multitasking:** Multiple independent tasks (reading sensors, controlling fans, updating a display) run concurrently, managed by a priority-based scheduler.
- **Inter-Task Communication:** Tasks communicate safely using **Queues** to pass data, decoupling the system's components (e.g., sensor task sends data to a logic task).
- **ISR-to-Task Synchronization:** A **Binary Semaphore** is used to efficiently signal a task from a high-priority hardware interrupt (Timer Input Capture for the ultrasonic sensor).
- **Shared Resource Management:** A **Mutex** is used to protect the shared SPI bus, ensuring that access to the TFT display is atomic and preventing data corruption from race conditions.

## System Architecture
The ECU operates on a decoupled, producer-consumer model:
1.  **Producer Tasks (`xTaskReadADC`, `xTaskHcsr04`):** These tasks interface directly with the hardware to gather raw sensor data.
2.  **Central Logic Task (`xTaskECULogic`):** The "brain" of the ECU. It consumes raw data, applies control logic, and dispatches commands and state information to actuator tasks.
3.  **Actuator/Consumer Tasks (`xTaskFanSpeed`, `xTaskdrawScreen`):** These tasks wait for commands or data and control physical hardware (relays, TFT display).

## Hardware Components
*   **MCU:** STM32F446RE (Nucleo-F446RE Development Board)
*   **Engine Temperature Sensor:** LM35 (Analog, connected to ADC)
*   **Throttle/RPM Input:** Potentiometer (Analog, connected to ADC)
*   **Fuel Level Sensor:** HC-SR04 Ultrasonic Sensor (driven by Timer Input Capture)
*   **Cooling System:** 3-Stage Fan controlled by two 5V Relay Modules (driven by Open-Drain GPIOs with external pull-ups)
*   **Dashboard Display:** ILI9341 TFT LCD (SPI Interface)
*   **Debug Output:** UART to PC Serial Terminal

## How to Get the Code
The source code is organized within the `Core` directory of this repository, following a standard structure for embedded projects.
- **`Core/Inc`:** Contains all header files (`.h`), including `main.h`, driver headers, and the crucial FreeRTOS configuration file `FreeRTOSConfig.h`.
- **`Core/Src`:** Contains all C source files (`.c`), including `main.c` (which handles initialization and starts the scheduler) and the bare-metal peripheral drivers.
- **`Core/ThirdParty/FreeRTOS`:** Contains the manually integrated FreeRTOS kernel source code, separated into `include`, `Source`, and `portable` directories.

## Project Status: OPERATIONAL
The core system is fully functional. All tasks are operational, data is flowing correctly through the system, and the hardware is responding to commands generated by the control logic. The project successfully demonstrates the power and necessity of a real-time operating system in a complex embedded application.
