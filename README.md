# 🚇 Metro Mate — Egyptian Online Metro Portal

A C++ console application that simulates a real-world metro system with full user account management, subscription plans, ride tracking, and an admin control panel.

---

## 📌 Features

### Passenger
- **Account system** — Register and log in with a username, password, and phone number
- **Subscription plans** — Choose from Wallet, Student, or Public plans with different pricing and ride limits
- **Check-in / Check-out** — Simulate boarding and exiting metro stations
- **Ride history** — View a personal log of all past rides with dates and stations
- **Profile management** — Update username, password, or phone number at any time
- **Wallet & balance** — Top up balance and manage subscription purchases

### Admin
- **User management** — View, edit, and delete user accounts
- **Subscription management** — Add, modify, or remove subscription plans
- **Ride logs** — View all ride records across every user in the system

---

## 🛠️ Tech Stack

| Layer | Technology |
|---|---|
| Language | C++ (C++17) |
| IDE | Visual Studio 2022 |
| Platform | Windows (x64) |
| Libraries | `<iostream>`, `<string>`, `<windows.h>`, `<conio.h>`, `<algorithm>` |

---

## 🗂️ Project Structure

```
FINAL SYSTEM FILE/
├── Source.cpp                  # All application logic
├── FINAL SYSTEM FILE.sln       # Visual Studio solution file
├── FINAL SYSTEM FILE.vcxproj   # Project configuration
└── x64/Debug/                  # Compiled output
```

---

## 🚀 Getting Started

### Prerequisites
- Windows OS
- Visual Studio 2019 or later (with C++ Desktop Development workload)

### Run
1. Clone the repository
2. Open `FINAL SYSTEM FILE.sln` in Visual Studio
3. Build the solution (`Ctrl + Shift + B`)
4. Run the executable (`Ctrl + F5`)

---

## 🧾 Subscription Plans

| Plan | Price (EGP) | Ride Limit |
|---|---|---|
| Wallet | 200 | 700 rides |
| Student | 33 | 180 rides |
| Public | 60 | 280 rides |

---

## 👤 Default Admin Access

> Admin accounts are pre-configured in the system. Contact the system owner for credentials.

---


## 📄 License

This project was built as an academic simulation. Feel free to explore and build on it.
