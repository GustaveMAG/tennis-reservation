# 🎾 Tennis Court Reservation System

This is a C project developed by **Gustave de Magondeau** and **Romain Monnier**.

It was our very first real programming project for school (2024-2025). The goal was to build a complete console application to manage a booking system using standard C libraries.

## 📖 About the Project

We created a simple tool to manage tennis court reservations. The program allows users to register players, check available courts (like Roland Garros or Wimbledon), and book time slots.

We focused on making the data persistent: everything is saved into text files (`joueurs.txt` and `reservations.txt`), so the data remains even after closing the program.

## ✅ Features

We implemented the following features based on the project requirements:

* **Player Management**: You can add new players and see the full list sorted by name.
* **Court Management**: A list of pre-loaded famous tennis courts.
* **Booking System**:
    * Book a court for a specific player, date, and time.
    * **Safety check**: The program stops you if you try to book a slot that is already taken.
    * Cancel a booking if needed.
* **File System**: Auto-load and auto-save of all data.

## 💻 Technical Details

Since this was a learning project, we used several key C concepts:
* **Structures**: To define Players, Courts, and Bookings.
* **Arrays**: To manage lists of data in memory.
* **File I/O**: Reading and writing `.txt` files to keep data between sessions.
* **Algorithms**: We wrote our own sorting logic to display lists alphabetically.

## 🚀 How to Run It

You just need a C compiler (like GCC).

1.  Download the files.
2.  Open a terminal in the folder.
3.  Compile the code:
    ```bash
    gcc tennis-reservation.c -o tennis
    ```
4.  Run it:
    * Windows: `.\tennis.exe`
    * Mac/Linux: `./tennis`

## 👥 Authors

* **Gustave de Magondeau**
* **Romain Monnier**

---
*Project for C Programming Module (2024-2025).*
