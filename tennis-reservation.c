#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 100
#define MAX_COURTS 10
#define MAX_BOOKINGS 100

// Basic structures
typedef struct {
    int id;
    char name[50];
    int nbBookings;
} Player;

typedef struct {
    int id;
    char name[50];
} Court;

typedef struct {
    int bookingId; // Unique ID to avoid deleting the wrong booking
    int playerId;
    int courtId;
    char date[15];
    char time[10];
} Booking;

// Global counter to ensure unique IDs even after reloading
int globalBookingIdCounter = 0;

// Prototypes
void addPlayer(Player players[], int *numPlayers);
void displayPlayers(Player players[], int numPlayers);
void displayCourts(Court courts[], int numCourts);
void bookCourt(Player players[], int numPlayers, Court courts[], int numCourts, Booking bookings[], int *numBookings);
void displayBookings(Player players[], int numPlayers, Court courts[], int numCourts, Booking bookings[], int numBookings);
void cancelBooking(Player players[], int numPlayers, Booking bookings[], int *numBookings);
void loadPlayers(Player players[], int *numPlayers);
void savePlayers(Player players[], int numPlayers);
void loadBookings(Booking bookings[], int *numBookings);
void saveBookings(Booking bookings[], int numBookings);
void menu(Player players[], int *numPlayers, Court courts[], int numCourts, Booking bookings[], int *numBookings);

// Helper to clear input buffer (fixes infinite loops with scanf)
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Player players[MAX_PLAYERS];
    Booking bookings[MAX_BOOKINGS];
    
    // Hardcoded list of courts
    Court courts[MAX_COURTS] = {
        {1, "Roland Garros"}, {2, "Wimbledon"}, {3, "US Open"},
        {4, "Australian Open"}, {5, "Monte Carlo"}, {6, "Indian Wells"},
        {7, "Madrid Open"}, {8, "Rome Open"}, {9, "Miami Open"}, {10, "Shanghai Masters"}
    };

    int numPlayers = 0, numBookings = 0;
    int numCourts = MAX_COURTS;

    // Load data on startup
    loadPlayers(players, &numPlayers);
    loadBookings(bookings, &numBookings);

    // Sync global ID counter with loaded data to prevent duplicates
    for(int i=0; i<numBookings; i++) {
        if(bookings[i].bookingId > globalBookingIdCounter) {
            globalBookingIdCounter = bookings[i].bookingId;
        }
    }

    menu(players, &numPlayers, courts, numCourts, bookings, &numBookings);

    return 0;
}

void addPlayer(Player players[], int *numPlayers) {
    if (*numPlayers >= MAX_PLAYERS) {
        printf("❌ Maximum number of players reached.\n");
        return;
    }
    
    printf("\n➡️ Add a player\nName: ");
    clearInputBuffer(); // Clear buffer before reading string
    
    // Using fgets to allow spaces in names
    if (fgets(players[*numPlayers].name, 50, stdin)) {
        // Trick to remove the newline char that fgets keeps
        players[*numPlayers].name[strcspn(players[*numPlayers].name, "\n")] = 0; 
        
        players[*numPlayers].id = *numPlayers + 1;
        players[*numPlayers].nbBookings = 0;
        (*numPlayers)++;
        printf("✅ Player added successfully!\n");
    } else {
        printf("❌ Error reading player name.\n");
    }
    savePlayers(players, *numPlayers); // Auto-save
}

void displayPlayers(Player players[], int numPlayers) {
    printf("\n📋 Players List\n");
    // Nice formatting with columns
    printf("%-5s %-25s %-10s\n", "ID", "Name", "Bookings");
    printf("------------------------------------------\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("%-5d %-25s %-10d\n", players[i].id, players[i].name, players[i].nbBookings);
    }
}

void displayCourts(Court courts[], int numCourts) {
    printf("\n🏟️ Courts List\n");
    for (int i = 0; i < numCourts; i++)
        printf("🔹 ID: %d - Name: %s\n", courts[i].id, courts[i].name);
}

void bookCourt(Player players[], int numPlayers, Court courts[], int numCourts, Booking bookings[], int *numBookings) {
    if (*numBookings >= MAX_BOOKINGS) {
        printf("❌ Booking list full.\n");
        return;
    }

    int playerId, courtId;
    char date[15], time[10];

    printf("\n➡️ Court Booking\n");
    displayPlayers(players, numPlayers);
    
    printf("Select a player (ID): ");
    if (scanf("%d", &playerId) != 1) { clearInputBuffer(); return; }

    // Validate player ID
    int playerFound = 0;
    for(int i=0; i<numPlayers; i++) {
        if(players[i].id == playerId) playerFound = 1;
    }
    if(!playerFound) { printf("❌ Invalid player ID!\n"); return; }

    displayCourts(courts, numCourts);
    printf("Select a court (ID): ");
    if (scanf("%d", &courtId) != 1) { clearInputBuffer(); return; }
    if (courtId < 1 || courtId > numCourts) { printf("❌ Invalid court ID!\n"); return; }

    printf("Date (DD/MM/YYYY): ");
    scanf("%s", date); 
    printf("Time (HH:00): ");
    scanf("%s", time);

    // Check availability
    for (int i = 0; i < *numBookings; i++) {
        if (bookings[i].courtId == courtId && strcmp(bookings[i].date, date) == 0 && strcmp(bookings[i].time, time) == 0) {
            printf("❌ This time slot is already booked!\n");
            return;
        }
    }

    // Create booking with unique ID
    globalBookingIdCounter++;
    bookings[*numBookings].bookingId = globalBookingIdCounter;
    bookings[*numBookings].playerId = playerId;
    bookings[*numBookings].courtId = courtId;
    strcpy(bookings[*numBookings].date, date);
    strcpy(bookings[*numBookings].time, time);
    (*numBookings)++;

    // Update player stats
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].id == playerId) {
            players[i].nbBookings++;
            break;
        }
    }

    printf("✅ Booking confirmed! Booking ID: %d\n", globalBookingIdCounter);
    savePlayers(players, numPlayers);
    saveBookings(bookings, *numBookings);
}

void displayBookings(Player players[], int numPlayers, Court courts[], int numCourts, Booking bookings[], int numBookings) {
    printf("\n📅 Current Bookings\n");
    if (numBookings == 0) {
        printf("No bookings found.\n");
        return;
    }

    // Loop through all bookings
    for (int i = 0; i < numBookings; i++) {
        char playerName[50] = "Unknown";
        char courtName[50] = "Unknown";

        // Find player name by ID
        for(int p=0; p<numPlayers; p++) {
            if(players[p].id == bookings[i].playerId) strcpy(playerName, players[p].name);
        }
        // Find court name
        if(bookings[i].courtId >=1 && bookings[i].courtId <= numCourts) {
            strcpy(courtName, courts[bookings[i].courtId-1].name);
        }

        printf("ID: %d | %s | %s | %s @ %s\n", 
               bookings[i].bookingId, playerName, courtName, bookings[i].date, bookings[i].time);
    }
}

void cancelBooking(Player players[], int numPlayers, Booking bookings[], int *numBookings) {
    if (*numBookings == 0) {
        printf("❌ No bookings to cancel.\n");
        return;
    }

    int targetId;
    printf("\n❌ Cancel a booking\n");
    printf("Enter the Booking ID to cancel: ");
    if (scanf("%d", &targetId) != 1) {
        clearInputBuffer();
        printf("❌ Invalid input.\n");
        return;
    }

    // Find index of the booking in the array
    int foundIndex = -1;
    for(int i=0; i<*numBookings; i++) {
        if(bookings[i].bookingId == targetId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("❌ Booking ID not found.\n");
        return;
    }

    // Decrease player booking count
    int pId = bookings[foundIndex].playerId;
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].id == pId) {
            players[i].nbBookings--;
            break;
        }
    }

    // Shift array left to fill the gap
    for (int i = foundIndex; i < *numBookings - 1; i++) {
        bookings[i] = bookings[i + 1];
    }
    (*numBookings)--;

    printf("✅ Booking canceled.\n");
    savePlayers(players, numPlayers);
    saveBookings(bookings, *numBookings);
}

void loadPlayers(Player players[], int *numPlayers) {
    FILE *f = fopen("joueurs.txt", "r");
    if (!f) return; 
    *numPlayers = 0;
    
    // Simple format: ID Name Count. (Assuming no spaces in file for now to keep it simple)
    while(fscanf(f, "%d %49s %d", &players[*numPlayers].id, players[*numPlayers].name, &players[*numPlayers].nbBookings) == 3){
         (*numPlayers)++;
    }
    fclose(f);
}

void savePlayers(Player players[], int numPlayers) {
    FILE *f = fopen("joueurs.txt", "w");
    if (!f) return;
    for (int i = 0; i < numPlayers; i++)
        fprintf(f, "%d %s %d\n", players[i].id, players[i].name, players[i].nbBookings);
    fclose(f);
}

void loadBookings(Booking bookings[], int *numBookings) {
    FILE *f = fopen("reservations.txt", "r");
    if (!f) return;
    *numBookings = 0;
    // Loading unique ID as well
    while (fscanf(f, "%d %d %d %s %s", &bookings[*numBookings].bookingId, &bookings[*numBookings].playerId, &bookings[*numBookings].courtId, bookings[*numBookings].date, bookings[*numBookings].time) == 5) {
        (*numBookings)++;
    }
    fclose(f);
}

void saveBookings(Booking bookings[], int numBookings) {
    FILE *f = fopen("reservations.txt", "w");
    if (!f) return;
    for (int i = 0; i < numBookings; i++)
        fprintf(f, "%d %d %d %s %s\n", bookings[i].bookingId, bookings[i].playerId, bookings[i].courtId, bookings[i].date, bookings[i].time);
    fclose(f);
}

void menu(Player players[], int *numPlayers, Court courts[], int numCourts, Booking bookings[], int *numBookings) {
    int choice;
    do {
        printf("\n🎾 Tennis Court Management 🎾\n");
        printf("1️⃣ Add a player\n");
        printf("2️⃣ Display players\n");
        printf("3️⃣ Display courts\n");
        printf("4️⃣ Book a court\n");
        printf("5️⃣ Display bookings\n");
        printf("6️⃣ Cancel a booking\n");
        printf("7️⃣ Quit\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer(); // specific fix for non-integer inputs
            choice = 0;
        }

        switch (choice) {
            case 1: addPlayer(players, numPlayers); break;
            case 2: displayPlayers(players, *numPlayers); break;
            case 3: displayCourts(courts, numCourts); break;
            case 4: bookCourt(players, *numPlayers, courts, numCourts, bookings, numBookings); break;
            case 5: displayBookings(players, *numPlayers, courts, numCourts, bookings, *numBookings); break;
            case 6: cancelBooking(players, *numPlayers, bookings, numBookings); break;
            case 7:
                printf("👋 Program ended\n");
                // Final save to be safe
                savePlayers(players, *numPlayers);
                saveBookings(bookings, *numBookings);
                break;
            default: printf("❌ Invalid choice.\n");
        }
    } while (choice != 7);
}