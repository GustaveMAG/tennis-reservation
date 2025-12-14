Here is a version that sounds more authentic and "human." It reads like a genuine student project description—direct, simple, and honest about it being a first step into C programming.

-----

# 🎾 Tennis Court Reservation System

This is a C project developed by **[Your Name]** and **Romain Monnier**.

It was our very first real programming project for school (2024-2025). [cite_start]The goal was to build a complete console application to manage a booking system using standard C libraries[cite: 1, 24].

## 📖 About the Project

We created a simple tool to manage tennis court reservations. The program allows users to register players, check available courts (like Roland Garros or Wimbledon), and book time slots.

[cite_start]We focused on making the data persistent: everything is saved into text files (`joueurs.txt` and `reservations.txt`), so the data remains even after closing the program[cite: 5, 35].

## ✅ Features

We implemented the following features based on the project requirements:

  * [cite_start]**Player Management**: You can add new players and see the full list sorted by name [cite: 37-39].
  * [cite_start]**Court Management**: A list of pre-loaded famous tennis courts[cite: 40].
  * **Booking System**:
      * [cite_start]Book a court for a specific player, date, and time[cite: 44].
      * **Safety check**: The program stops you if you try to book a slot that is already taken.
      * [cite_start]Cancel a booking if needed[cite: 45].
  * [cite_start]**File System**: Auto-load and auto-save of all data[cite: 35].

## 💻 Technical Details

[cite_start]Since this was a learning project, we used several key C concepts[cite: 3, 4, 33]:

  * [cite_start]**Structures**: To define Players, Courts, and Bookings[cite: 26].
  * [cite_start]**Arrays**: To manage lists of data in memory[cite: 34].
  * [cite_start]**File I/O**: Reading and writing `.txt` files to keep data between sessions[cite: 5].
  * [cite_start]**Algorithms**: We wrote our own sorting logic to display lists alphabetically[cite: 39].

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

  * **[Your Name]**
  * **Romain Monnier**

-----

*Project for C Programming Module (2024-2025).*