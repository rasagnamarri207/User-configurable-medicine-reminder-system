# 💊 User-Configurable Medicine Reminder System

## 📌 Project Overview

The **User-Configurable Medicine Reminder System** is an embedded system designed to help users remember their scheduled medicines by allowing them to configure medicine timings and receive automatic alerts.

The system continuously monitors the **Real-Time Clock (RTC)** and compares the current time with the medicine schedules stored in controller memory. When the scheduled medicine time is reached, the system displays **"Take Medicine Now"** on the LCD and activates the buzzer.

### 🖼️ Project Overview

![User-Configurable Medicine Reminder System](a_clean_infographic_style_project_readme_poster_l.png)

---

## 🎯 Objectives

* Display the current RTC date and time on the LCD.
* Allow users to configure medicine timings.
* Monitor medicine schedules continuously in real time.
* Generate an alert when the scheduled medicine time occurs.
* Allow the user to acknowledge the reminder using a switch.
* Automatically stop the alert after the specified timeout period.

---

## 🧩 System Block Diagram

![Medicine Reminder System Block Diagram](a_clean_infographic_style_project_readme_poster_l.png)

### Main Components

| Component                 | Function                                                      |
| ------------------------- | ------------------------------------------------------------- |
| **LPC2148**               | Main controller of the system                                 |
| **RTC**                   | Maintains current date and time                               |
| **4×4 Matrix Keypad**     | Used to enter and configure medicine timings                  |
| **16×2 LCD**              | Displays RTC time, configuration menus, and reminder messages |
| **Buzzer**                | Generates medicine reminder alerts                            |
| **Switch-1 / EINT0**      | Enters configuration/setup mode                               |
| **Switch-2 / EINT1**      | Acknowledges the medicine reminder                            |
| **USB-UART / DB-9 Cable** | Used for serial communication/testing                         |

These components are listed in the project requirements.

---

## ⚙️ Working Principle

### 1️⃣ System Configuration

**Switch-1 (EINT0)** is used to enter setup mode.

When Switch-1 is pressed, the LCD displays configuration options:

```text
┌─────────────────────────┐
│     CONFIGURATION       │
├─────────────────────────┤
│ 1. Edit RTC Time        │
│ 2. Medicine Schedule    │
└─────────────────────────┘
```

The user selects the required option using the keypad.

The user can either:

* Edit the RTC date and time.
* Configure one or more medicine timings.

After configuration, the system returns to normal operation.

---

## 🕐 Clock-Only Mode

If no medicine schedule is configured, the system operates as a **digital clock**.

The LCD continuously displays the current RTC date and time, while medicine-alert checking and buzzer operation remain inactive until at least one medicine timing is configured.

Example:

```text
┌────────────────┐
│ 19-08-2026     │
│ 14:30:25       │
└────────────────┘
```

---

## 🔄 Real-Time Monitoring

Once one or more medicine schedules are configured:

```text
              ┌───────────────┐
              │      RTC      │
              │ Current Time  │
              └───────┬───────┘
                      ↓
             ┌─────────────────┐
             │ Compare Current │
             │ Time with Saved │
             │   Schedules     │
             └────────┬────────┘
                      ↓
                ┌────────────┐
                │ Time Match?│
                └─────┬──────┘
                  YES │ NO
                      ↓
                ┌─────────────┐
                │ Take Medicine│
                │     Now      │
                └──────┬──────┘
                       ↓
                 Buzzer Alert
```

The controller continuously reads the RTC and compares the current time with all stored medicine timings.

---

## 🔔 Medicine Alert

When the RTC time matches a configured medicine schedule:

1. LCD displays **"Take Medicine Now"**.
2. Buzzer generates periodic ON/OFF alerts.
3. A **1-minute acknowledgment timer** starts.
4. The user can press Switch-2 to acknowledge the reminder.

### Alert Flow

```text
        Medicine Time Match
                │
                ↓
      ┌─────────────────────┐
      │ LCD: Take Medicine  │
      │        Now          │
      └──────────┬──────────┘
                 ↓
          Buzzer ON/OFF
                 │
                 ↓
        Start 1-Minute Timer
                 │
          ┌──────┴──────┐
          ↓             ↓
   Switch-2 Pressed   Timeout
          │             │
          ↓             ↓
    Stop Buzzer      Stop Buzzer
    Clear Reminder   Clear Reminder
          │             │
          └──────┬──────┘
                 ↓
        Normal Monitoring
```

---

## 🖲️ User Acknowledgment

**Switch-2 (EINT1)** is used to acknowledge that the medicine has been taken.

When Switch-2 is pressed:

```text
Switch-2 Pressed
       ↓
Stop Buzzer
       ↓
Clear Reminder
       ↓
Return to RTC Monitoring
```

If Switch-2 is not pressed within one minute, the system automatically stops the buzzer and returns to normal RTC monitoring.

---

## 🔄 Complete Software Flow

```text
                 START
                   │
                   ↓
        Initialize Peripherals
                   │
                   ↓
       RTC + LCD + Keypad
       Buzzer + Timer
       Enable EINT0 & EINT1
                   │
                   ↓
        Display RTC Date/Time
                   │
                   ↓
        Check EINT0 / Switch-1
              │           │
             YES          NO
              │           │
              ↓           │
      Configuration Mode  │
              │           │
       ┌──────┴──────┐    │
       ↓             ↓    │
   Edit RTC     Configure  │
                 Medicine  │
              │             │
              └──────┬──────┘
                     ↓
             Store Schedule
                     │
                     ↓
              Normal Mode
                     │
                     ↓
            Compare RTC Time
             With Schedules
                     │
                Time Match?
                /          \
              NO            YES
              │              │
              │              ↓
              │       Display Alert
              │       Start Buzzer
              │       Start Timer
              │              │
              │       Check EINT1
              │          /       \
              │        YES       NO
              │         │         │
              │         ↓         ↓
              │    Stop Buzzer  Timeout
              │    Clear Alert      │
              │         │            ↓
              └─────────┴──────→ Normal Monitoring
```

The project software flow specifies peripheral initialization, RTC display, EINT0-based schedule configuration, continuous RTC comparison, alert generation, EINT1 acknowledgment, timeout handling, and repeated monitoring.

---

## 🛠️ Hardware Requirements

* **LPC2148**
* **16×2 LCD**
* **4×4 Matrix Keypad**
* **Buzzer**
* **Switches**
* **USB-UART Converter / DB-9 Cable**

## 💻 Software Requirements

* **Embedded C Programming**
* **Flash Magic**

---

## ⭐ Key Features

* 💊 User-configurable medicine schedules
* 🕐 Real-time RTC-based monitoring
* ⌨️ 4×4 keypad interface
* 🖥️ 16×2 LCD display
* 🔔 Automatic buzzer alerts
* 🖲️ External interrupt-based acknowledgment
* ⏱️ 1-minute alert timeout
* ⚙️ RTC configuration
* 🔄 Continuous operation
* 📅 Multiple medicine timing support

---

## 🔌 Technologies Used

| Technology           | Usage                                      |
| -------------------- | ------------------------------------------ |
| **ARM7 / LPC2148**   | Main embedded controller                   |
| **Embedded C**       | Application programming                    |
| **RTC**              | Timekeeping and schedule comparison        |
| **GPIO**             | Switch, keypad, LCD and buzzer interfacing |
| **EINT0**            | Configuration interrupt                    |
| **EINT1**            | Reminder acknowledgment interrupt          |
| **Timer**            | Alert timeout handling                     |
| **LCD Interface**    | User information display                   |
| **Keypad Interface** | User input                                 |
| **Flash Magic**      | Microcontroller programming                |

---

## 📂 Suggested GitHub Project Structure

```text
User-Configurable-Medicine-Reminder/
│
├── src/
│   ├── main.c
│   ├── lcd.c
│   ├── keypad.c
│   ├── rtc.c
│   ├── delay.c
│   └── interrupts.c
│
├── include/
│   ├── lcd.h
│   ├── keypad.h
│   ├── rtc.h
│   ├── delay.h
│   └── interrupts.h
│
├── docs/
│   └── Project_Report.pdf
│
├── images/
│   ├── block_diagram.png
│   ├── authentication_flow.png
│   └── hardware_setup.png
│
└── README.md
```

---

## 🚀 Applications

The system can be used as a basis for:

* 💊 Personal medicine reminder systems
* 🏠 Home healthcare assistance
* 👴 Elderly medicine reminders
* 🏥 Healthcare monitoring environments
* 💉 Scheduled medication alert systems

---

## 🔮 Future Enhancements

Possible future improvements include:

* Mobile application notifications.
* Wi-Fi/GSM-based remote alerts.
* Cloud-based medicine schedules.
* Multiple-user support.
* Medicine history and logging.
* Voice-based reminders.
* Battery backup for uninterrupted operation.

---

## 👨‍💻 Project Summary

The **User-Configurable Medicine Reminder System** demonstrates the integration of **LPC2148, RTC, LCD, keypad, buzzer, timers, and external interrupts** to create an embedded medicine-alert solution.

The core working concept is:

> **Configure medicine time → Monitor RTC → Detect scheduled time → Alert user → Acknowledge or automatically stop after timeout.**

This project demonstrates practical concepts in **Embedded C, ARM7 microcontrollers, RTC interfacing, keypad interfacing, LCD interfacing, timers, and external interrupts**.
