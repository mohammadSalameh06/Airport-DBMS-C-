#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>




struct passenger {
    int id;
    char firstName[50];
    char lastName[50];
    char contactInfo[50];
    char passportNumber[20];
    struct passenger* next;
};

struct flight {
    int id;
    char flightNumber[20];
    char destination[50];
    char gate[10];
    char arrivalTime[20];
    char departureTime[20];
    struct flight* next;
};

struct employee {
    int id;
    char firstName[50];
    char lastName[50];
    char contactNumber[20];
    char email[50];
    char role[50];
    struct employee* next;
};

struct ticket {
    int ticketNumber;
    int passengerId;
    int flightId;
    char seatNumber[10];
    struct ticket* next;
};

struct airport {
    int id;
    char code[10];
    char name[50];
    char location[50];
    struct airport* next;
};

void* managePassengers(void* data);
void* manageFlights(void* data);
void* manageEmployees(void* data);
void* manageTickets(void* data);




struct passenger* headPassenger = NULL;
struct flight* headFlight = NULL;
struct employee* headEmployee = NULL;
struct ticket* headTicket = NULL;
struct airport* headAirport = NULL;

void savePassengersToFile() {
    FILE *file = fopen("passengers.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }


    struct passenger *temp = headPassenger;
    while (temp != NULL) {
        fprintf(file, "ID=%d,FirstName=%s,LastName=%s,contactInfo=%s,passportNumber=%s\n", temp->id, temp->firstName, temp->lastName, temp->contactInfo, temp->passportNumber);
        temp = temp->next;
    }

    fclose(file);
    printf("Passengers data saved successfully.\n");
}



void saveFlightsToFile() {
    FILE *file = fopen("flights.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    struct flight *temp = headFlight;
    while (temp != NULL) {
        fprintf(file, "%s,%s,%d\n", temp->flightNumber, temp->destination, temp->id);
        temp = temp->next;
    }

    fclose(file);
}

void saveEmployeesToFile() {
    FILE *file = fopen("employees.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    struct employee *temp = headEmployee;
    while (temp != NULL) {
        fprintf(file, "ID=%d, First Name=%s, Last Name=%s, Contact Number=%s, Email=%s, Role=%s\n",
                temp->id, temp->firstName, temp->lastName, temp->contactNumber, temp->email, temp->role);
        temp = temp->next;
    }

    fclose(file);
}


void saveTicketsToFile() {
    FILE *file = fopen("tickets.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    struct ticket *temp = headTicket;
    while (temp != NULL) {
        fprintf(file, "%d,%d,%d\n", temp->ticketNumber, temp->passengerId, temp->flightId);
        temp = temp->next;
    }

    fclose(file);
}

void saveAirportsToFile() {
    FILE *file = fopen("airports.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    struct airport *temp = headAirport;
    while (temp != NULL) {
        fprintf(file, "%s,%s,%d\n", temp->name, temp->location, temp->id);
        temp = temp->next;
    }

    fclose(file);
}

struct passenger* findPassengerById(int id) {
    struct passenger* temp = headPassenger;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct flight* findFlightById(int id) {
    struct flight* temp = headFlight;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct employee* findEmployeeById(int id) {
    FILE *file = fopen("employees.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    struct employee* temp = headEmployee;
    while (temp != NULL) {
        if (temp->id == id) {
            fclose(file);
            return temp;
        }
        temp = temp->next;
    }

    fclose(file);
    return NULL;
}


struct ticket* findTicketById(int ticketNumber) {
    struct ticket* temp = headTicket;
    while (temp != NULL) {
        if (temp->ticketNumber == ticketNumber) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct airport* findAirportById(int id) {
    struct airport* temp = headAirport;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
///////////passengerFunctions\\\\\\\\\\\\\\/
void addPassenger() {
    
    
    struct passenger *newPassenger = (struct passenger *)malloc(sizeof(struct passenger));
    if (newPassenger == NULL) {
        perror("Memory allocation error");
        return;
    }

    printf("\nEnter passenger ID: ");
    scanf("%d", &newPassenger->id);
    printf("Enter passenger first name: ");
    scanf(" %[^\n]s", newPassenger->firstName);  
    printf("Enter passenger last name: ");
    scanf(" %[^\n]s", newPassenger->lastName);
    printf("Enter contact info: ");
    scanf(" %[^\n]s", newPassenger->contactInfo);
    printf("Enter passport number: ");
    scanf(" %[^\n]s", newPassenger->passportNumber);

    newPassenger->next = headPassenger;
    headPassenger = newPassenger;

    printf("\nPassenger added successfully.\n");

    savePassengersToFile();
}

void displayPassengers() {
    int choice, idSearch;
    char nameSearch[50];

    printf("Choose an option:\n");
    printf("1. Search by Name\n");
    printf("2. Search by ID\n");
    printf("3. Show All\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    struct passenger* temp = headPassenger;

    if (choice == 1) {
        printf("Enter Name to search: ");
        scanf(" %[^\n]s", nameSearch); // Read a string with spaces
        while (temp != NULL) {
            if (strstr(temp->firstName, nameSearch) != NULL || strstr(temp->lastName, nameSearch) != NULL) {
                printf("\nID: %d", temp->id);
                printf("\nFirst Name: %s", temp->firstName);
                printf("\nLast Name: %s", temp->lastName);
                printf("\nContact Info: %s", temp->contactInfo);
                printf("\nPassport Number: %s\n", temp->passportNumber);
            }
            temp = temp->next;
        }
    } else if (choice == 2) {
        printf("Enter ID to search: ");
        scanf("%d", &idSearch);
        while (temp != NULL) {
            if (temp->id == idSearch) {
                printf("\nID: %d", temp->id);
                printf("\nFirst Name: %s", temp->firstName);
                printf("\nLast Name: %s", temp->lastName);
                printf("\nContact Info: %s", temp->contactInfo);
                printf("\nPassport Number: %s\n", temp->passportNumber);
                break;
            }
            temp = temp->next;
        }
    } else if (choice == 3) {
        while (temp != NULL) {
            printf("\nID: %d", temp->id);
            printf("\nFirst Name: %s", temp->firstName);
            printf("\nLast Name: %s", temp->lastName);
            printf("\nContact Info: %s", temp->contactInfo);
            printf("\nPassport Number: %s\n", temp->passportNumber);
            temp = temp->next;
        }
    } else {
        printf("\nInvalid choice.\n");
    }
}


void deletePassenger(int id) {
    struct passenger* temp = headPassenger;
    struct passenger* prev = NULL;

    while (temp != NULL && temp->id == id) {
        headPassenger = temp->next;
        free(temp);
        printf("\nPassenger deleted successfully.\n");
        savePassengersToFile(); 
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nPassenger not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("\nPassenger deleted successfully.\n");
    savePassengersToFile(); 
}

void updatePassenger() {
    int id, choice;
    char newFirstName[50], newLastName[50], newContactInfo[50], newPassportNumber[20];

    printf("\nEnter Passenger ID to update: ");
    scanf("%d", &id);

    struct passenger* passengerToUpdate = findPassengerById(id);
    if (passengerToUpdate == NULL) {
        printf("\nPassenger not found.\n");
        return;
    }

    printf("Choose attribute to update:\n");
    printf("1. First Name\n");
    printf("2. Last Name\n");
    printf("3. Contact Info\n");
    printf("4. Passport Number\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new First Name: ");
            scanf(" %[^\n]s", newFirstName);
            strcpy(passengerToUpdate->firstName, newFirstName);
            break;
        case 2:
            printf("Enter new Last Name: ");
            scanf(" %[^\n]s", newLastName);
            strcpy(passengerToUpdate->lastName, newLastName);
            break;
        case 3:
            printf("Enter new Contact Info: ");
            scanf(" %[^\n]s", newContactInfo);
            strcpy(passengerToUpdate->contactInfo, newContactInfo);
            break;
        case 4:
            printf("Enter new Passport Number: ");
            scanf(" %[^\n]s", newPassportNumber);
            strcpy(passengerToUpdate->passportNumber, newPassportNumber);
            break;
        default:
            printf("\nInvalid choice.\n");
            return;
    }

    printf("\nPassenger information updated successfully.\n");
    savePassengersToFile(); // Save the updated list to file
}

///////////FlightFunctions\\\\\\\\\\\\\\/

void addFlight(int id, char flightNumber[], char destination[], char gate[], char arrivalTime[], char departureTime[]) {
    struct flight* newFlight = (struct flight*)malloc(sizeof(struct flight));
    if (newFlight == NULL) {
        perror("Memory allocation error");
        return;
    }

    newFlight->id = id;
    strcpy(newFlight->flightNumber, flightNumber);
    strcpy(newFlight->destination, destination);
    strcpy(newFlight->gate, gate);
    strcpy(newFlight->arrivalTime, arrivalTime);
    strcpy(newFlight->departureTime, departureTime);
    newFlight->next = headFlight;

    headFlight = newFlight;

    FILE *file = fopen("flights.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        free(newFlight);
        return;
    }

   
    fprintf(file, "ID=%d, Flight Number=%s, Destination=%s, Gate=%s, Arrival Time=%s, Departure Time=%s\n",
            id, flightNumber, destination, gate, arrivalTime, departureTime);

    fclose(file);
    printf("\nFlight added successfully.\n");
}

void updateFlightInfo(int id) {
    FILE *file = fopen("flights.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    struct flight flight;
    int found = 0;

    
    FILE *tempFile = fopen("temp_flights.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    
    while (fscanf(file, "ID=%d, Flight Number=%[^,], Destination=%[^,], Gate=%[^,], Arrival Time=%[^,], Departure Time=%[^\n]\n",
                  &flight.id, flight.flightNumber, flight.destination,
                  flight.gate, flight.arrivalTime, flight.departureTime) != EOF) {
        
        if (flight.id == id) {
            found = 1;

            int choice;
            printf("\nSelect attribute to update:");
            printf("\n1. Flight Number");
            printf("\n2. Destination");
            printf("\n3. Gate");
            printf("\n4. Arrival Time");
            printf("\n5. Departure Time");
            printf("\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter new Flight Number: ");
                    scanf("%s", flight.flightNumber);
                    break;
                case 2:
                    printf("Enter new Destination: ");
                    scanf("%s", flight.destination);
                    break;
                case 3:
                    printf("Enter new Gate: ");
                    scanf("%s", flight.gate);
                    break;
                case 4:
                    printf("Enter new Arrival Time: ");
                    scanf("%s", flight.arrivalTime);
                    break;
                case 5:
                    printf("Enter new Departure Time: ");
                    scanf("%s", flight.departureTime);
                    break;
                default:
                    printf("\nInvalid choice.\n");
                    fclose(file);
                    fclose(tempFile);
                    return;
            }

            printf("\nFlight information updated successfully.\n");
        }

       
        fprintf(tempFile, "ID=%d, Flight Number=%s, Destination=%s, Gate=%s, Arrival Time=%s, Departure Time=%s\n",
                flight.id, flight.flightNumber, flight.destination, flight.gate, flight.arrivalTime, flight.departureTime);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        
        remove("flights.txt");
        rename("temp_flights.txt", "flights.txt");
    } else {
        printf("\nFlight not found.\n");
    }
}

void displayFlights() {
    int choice, idSearch;
    char flightNumberSearch[20];

    printf("Choose an option:\n");
    printf("1. Search by Flight Number\n");
    printf("2. Search by ID\n");
    printf("3. Show All\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    FILE *file = fopen("flights.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int tempId;
    char flightNumber[20], destination[50], gate[10], arrivalTime[20], departureTime[20];

    if (choice == 1) {
        printf("Enter Flight Number to search: ");
        scanf(" %[^\n]s", flightNumberSearch);
    } else if (choice == 2) {
        printf("Enter ID to search: ");
        scanf("%d", &idSearch);
    }

    while (fscanf(file, "ID=%d, Flight Number=%[^,], Destination=%[^,], Gate=%[^,], Arrival Time=%[^,], Departure Time=%[^\n]\n",
                  &tempId, flightNumber, destination, gate, arrivalTime, departureTime) != EOF) {
        if ((choice == 1 && strcmp(flightNumber, flightNumberSearch) == 0) ||
            (choice == 2 && tempId == idSearch) ||
            choice == 3) {
            printf("\nFlight Number: %s", flightNumber);
            printf("\nDestination: %s", destination);
            printf("\nGate: %s", gate);
            printf("\nArrival Time: %s", arrivalTime);
            printf("\nDeparture Time: %s", departureTime);
            printf("\nID: %d\n", tempId);
        }
    }

    fclose(file);
    if (choice == 1 || choice == 2) {
        printf("\nFlight not found.\n");
    }
}



void deleteFlight(int id) {
    struct flight *temp = headFlight, *prev = NULL;

    // Check if head node itself holds the flight to be deleted
    if (temp != NULL && temp->id == id) {
        headFlight = temp->next;   // Change head
        free(temp);                // Free old head
        printf("\nFlight deleted successfully.\n");
        saveFlightsToFile();       // Save changes to the file
        return;
    }

   
while (temp != NULL && temp->id != id) {
prev = temp;
temp = temp->next;
}
if (temp == NULL) {
    printf("\nFlight not found.\n");
    return;
}

// Unlink the flight from the linked list
prev->next = temp->next;

free(temp); // Free memory
printf("\nFlight deleted successfully.\n");
saveFlightsToFile(); // Save changes to the file
}

///////////passengerFunctions\\\\\\\\\\\\\\/



void addEmployee(int id, char firstName[], char lastName[], char contactNumber[], char email[], char role[]) {
    struct employee *newEmployee = (struct employee*)malloc(sizeof(struct employee));
    if (newEmployee == NULL) {
        perror("Memory allocation error");
        return;
    }

    newEmployee->id = id;
    strcpy(newEmployee->firstName, firstName);
    strcpy(newEmployee->lastName, lastName);
    strcpy(newEmployee->contactNumber, contactNumber);
    strcpy(newEmployee->email, email);
    strcpy(newEmployee->role, role);
    newEmployee->next = headEmployee;

    headEmployee = newEmployee;

    FILE *file = fopen("employees.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        free(newEmployee); 
        return;
    }

    
    fprintf(file, "ID=%d, First Name=%s, Last Name=%s, Contact Number=%s, Email=%s, Role=%s\n",
            id, firstName, lastName, contactNumber, email, role);

    fclose(file);
    printf("\nEmployee added successfully.\n");
}


void updateEmployeeInfo(int id) {
    FILE *file = fopen("employees.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    struct employee employee;
    int found = 0;

    
    FILE *tempFile = fopen("temp_employees.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    while (fscanf(file, "ID=%d, First Name=%[^,], Last Name=%[^,], Contact Number=%[^,], Email=%[^,], Role=%[^\n]\n",
                  &employee.id, employee.firstName, employee.lastName,
                  employee.contactNumber, employee.email, employee.role) != EOF) {
        if (employee.id == id) {
            found = 1;

            int choice;
            printf("\nSelect attribute to update:");
            printf("\n1. First Name");
            printf("\n2. Last Name");
            printf("\n3. Contact Number");
            printf("\n4. Role");
            printf("\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter new First Name: ");
                    scanf("%s", employee.firstName);
                    break;
                case 2:
                    printf("Enter new Last Name: ");
                    scanf("%s", employee.lastName);
                    break;
                case 3:
                    printf("Enter new Contact Number: ");
                    scanf("%s", employee.contactNumber);
                    break;
                case 4:
                    printf("Enter new Role: ");
                    scanf("%s", employee.role);
                    break;
                default:
                    printf("\nInvalid choice.\n");
                    fclose(file);
                    fclose(tempFile);
                    return;
            }

            printf("\nEmployee information updated successfully.\n");
        }

        fprintf(tempFile, "ID=%d, First Name=%s, Last Name=%s, Contact Number=%s, Email=%s, Role=%s\n",
                employee.id, employee.firstName, employee.lastName,
                employee.contactNumber, employee.email, employee.role);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("employees.txt");
        rename("temp_employees.txt", "employees.txt");
    } else {
        printf("\nEmployee not found.\n");
    }
}




void displayEmployees() {
    int id;
    printf("\nEnter employee ID: ");
    scanf("%d", &id);

    FILE *file = fopen("employees.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int tempId;
    char firstName[50], lastName[50], contactNumber[20], email[50], role[50];

    while (fscanf(file, "ID=%d, First Name=%[^,], Last Name=%[^,], Contact Number=%[^,], Email=%[^,], Role=%[^\n]\n",
                  &tempId, firstName, lastName, contactNumber, email, role) == 6) {
        if (tempId == id) {
            printf("\nName: %s %s", firstName, lastName);
            printf("\nEmployee ID: %d", tempId);
            printf("\nContact Number: %s", contactNumber);
            printf("\nEmail: %s", email);
            printf("\nRole: %s", role);
            printf("\nID: %d\n", tempId);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\nEmployee not found.\n");
}


void deleteEmployee(int id) {
    FILE *file = fopen("employees.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temp file");
        fclose(file);
        return;
    }

    int tempId;
    char firstName[50], lastName[50], contactNumber[20], email[50], role[50];

    
    while (fscanf(file, "ID=%d, First Name=%[^,], Last Name=%[^,], Contact Number=%[^,], Email=%[^,], Role=%[^\n]\n",
                  &tempId, firstName, lastName, contactNumber, email, role) == 6) {
        if (tempId != id) {
            fprintf(tempFile, "ID=%d, First Name=%s, Last Name=%s, Contact Number=%s, Email=%s, Role=%s\n",
                    tempId, firstName, lastName, contactNumber, email, role);
        }
    }

    fclose(file);
    fclose(tempFile);

    
    remove("employees.txt");
    rename("temp.txt", "employees.txt");

    printf("\nEmployee deleted successfully.\n");
}

void addTicket(int ticketNumber, int passengerId, int flightId, char seatNumber[]) {
    struct ticket* newTicket = (struct ticket*)malloc(sizeof(struct ticket));
    if (newTicket == NULL) {
        perror("Memory allocation error");
        return;
    }

    newTicket->ticketNumber = ticketNumber;
    newTicket->passengerId = passengerId;
    newTicket->flightId = flightId;
    strcpy(newTicket->seatNumber, seatNumber);
    newTicket->next = headTicket;

    headTicket = newTicket;

    FILE *file = fopen("tickets.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        free(newTicket);  
        return;
    }

    fprintf(file, "Ticket Number=%d, Passenger ID=%d, Flight ID=%d, Seat Number=%s\n",
            ticketNumber, passengerId, flightId, seatNumber);

    fclose(file);
    printf("\nTicket added successfully.\n");
}
void updateTicketInfo(int ticketNumber) {
    FILE *file = fopen("tickets.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp_tickets.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    int tempTicketNumber, tempPassengerId, tempFlightId;
    char tempSeatNumber[10];

    int found = 0;

    while (fscanf(file, "Ticket Number=%d, Passenger ID=%d, Flight ID=%d, Seat Number=%s\n",
                  &tempTicketNumber, &tempPassengerId, &tempFlightId, tempSeatNumber) == 4) {
        if (tempTicketNumber == ticketNumber) {
            found = 1;

            int choice;
            printf("\nSelect attribute to update:");
            printf("\n1. Passenger ID");
            printf("\n2. Flight ID");
            printf("\n3. Seat Number");
            printf("\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter new Passenger ID: ");
                    scanf("%d", &tempPassengerId);
                    break;
                case 2:
                    printf("Enter new Flight ID: ");
                    scanf("%d", &tempFlightId);
                    break;
                case 3:
                    printf("Enter new Seat Number: ");
                    scanf("%s", tempSeatNumber);
                    break;
                default:
                    printf("\nInvalid choice.\n");
                    fclose(file);
                    fclose(tempFile);
                    return;
            }

            printf("\nTicket information updated successfully.\n");
        }

        fprintf(tempFile, "Ticket Number=%d, Passenger ID=%d, Flight ID=%d, Seat Number=%s\n",
                tempTicketNumber, tempPassengerId, tempFlightId, tempSeatNumber);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("tickets.txt");
        rename("temp_tickets.txt", "tickets.txt");
    } else {
        printf("\nTicket not found.\n");
    }
}




void deleteTicket(int ticketNumber) {
    FILE *file = fopen("tickets.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp_tickets.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    int tempTicketNumber, tempPassengerId, tempFlightId;
    char tempSeatNumber[10];

    
    while (fscanf(file, "Ticket Number=%d, Passenger ID=%d, Flight ID=%d, Seat Number=%s\n",
                  &tempTicketNumber, &tempPassengerId, &tempFlightId, tempSeatNumber) == 4) {
        if (tempTicketNumber != ticketNumber) {
            fprintf(tempFile, "Ticket Number=%d, Passenger ID=%d, Flight ID=%d, Seat Number=%s\n",
                    tempTicketNumber, tempPassengerId, tempFlightId, tempSeatNumber);
        }
    }

    fclose(file);
    fclose(tempFile);

    
    remove("tickets.txt");
    rename("temp_tickets.txt", "tickets.txt");

    printf("\nTicket deleted successfully.\n");
}

void displayTickets() {
    FILE *file = fopen("tickets.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int ticketNumber, passengerId, flightId;
    char seatNumber[10];

    while (fscanf(file, "Ticket Number=%d, Passenger ID=%d, Flight ID=%d, Seat Number=%s\n",
                  &ticketNumber, &passengerId, &flightId, seatNumber) == 4) {
        printf("\nTicket Number: %d", ticketNumber);
        printf("\nPassenger ID: %d", passengerId);
        printf("\nFlight ID: %d", flightId);
        printf("\nSeat Number: %s", seatNumber);
        printf("\n");
    }

    fclose(file);
}


void addAirport(int id, char code[], char name[], char location[]) {
    struct airport* newAirport = (struct airport*)malloc(sizeof(struct airport));
    if (newAirport == NULL) {
        perror("Memory allocation error");
        return;
    }

    newAirport->id = id;
    strcpy(newAirport->code, code);
    strcpy(newAirport->name, name);
    strcpy(newAirport->location, location);
    newAirport->next = headAirport;

    headAirport = newAirport;

    FILE *file = fopen("airports.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        free(newAirport);  
        return;
    }

    fprintf(file, "ID=%d, Code=%s, Name=%s, Location=%s\n", id, code, name, location);

    fclose(file);
    printf("\nAirport added successfully.\n");
}

void updateAirportInfo(int id) {
    FILE *file = fopen("airports.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    struct airport airport;
    int found = 0;

    FILE *tempFile = fopen("temp_airports.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    while (fscanf(file, "ID=%d, Code=%[^,], Name=%[^,], Location=%[^\n]\n",
                  &airport.id, airport.code, airport.name, airport.location) != EOF) {
        if (airport.id == id) {
            found = 1;

            int choice;
            printf("\nSelect attribute to update:");
            printf("\n1. Code");
            printf("\n2. Name");
            printf("\n3. Location");
            printf("\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter new Code: ");
                    scanf(" %[^\n]s", airport.code);
                    break;
                case 2:
                    printf("Enter new Name: ");
                    scanf(" %[^\n]s", airport.name);
                    break;
                case 3:
                    printf("Enter new Location: ");
                    scanf(" %[^\n]s", airport.location);
                    break;
                default:
                    printf("\nInvalid choice.\n");
                    fclose(file);
                    fclose(tempFile);
                    return;
            }

            printf("\nAirport information updated successfully.\n");
        }

        fprintf(tempFile, "ID=%d, Code=%s, Name=%s, Location=%s\n",
                airport.id, airport.code, airport.name, airport.location);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("airports.txt");
        rename("temp_airports.txt", "airports.txt");
    } else {
        printf("\nAirport not found.\n");
    }
}

void deleteAirport(int id) {
    FILE *file = fopen("airports.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp_airports.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temp file");
        fclose(file);
        return;
    }

    int tempId;
    char code[10], name[50], location[50];

    
    while (fscanf(file, "ID=%d, Code=%[^,], Name=%[^,], Location=%[^\n]\n",
                  &tempId, code, name, location) == 4) {
        if (tempId != id) {
            fprintf(tempFile, "ID=%d, Code=%s, Name=%s, Location=%s\n", tempId, code, name, location);
        }
    }

    fclose(file);
    fclose(tempFile);

    
    remove("airports.txt");
    rename("temp_airports.txt", "airports.txt");

    printf("\nAirport deleted successfully.\n");
}

void displayAirports() {
    int id;
    printf("\nEnter airport ID: ");
    scanf("%d", &id);

    FILE *file = fopen("airports.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int tempId;
    char code[10], name[50], location[50];

    while (fscanf(file, "ID=%d, Code=%[^,], Name=%[^,], Location=%[^\n]\n",
                  &tempId, code, name, location) == 4) {
        if (tempId == id) {
            printf("\nID: %d", tempId);
            printf("\nCode: %s", code);
            printf("\nName: %s", name);
            printf("\nLocation: %s", location);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\nAirport not found.\n");
}



void displayMainMenu() {
    printf("\n\n--- Airport Management System ---\n");
    printf("\n1. Passengers Menu");
    printf("\n2. Flights Menu");
    printf("\n3. Employees Menu");
    printf("\n4. Tickets Menu");
    printf("\n5. Airports Menu");
    printf("\n6. Exit\n");
    printf("********************\n");

    printf("\n\nEnter your choice: ");
}

void displayPassengersMenu() {
    printf("\n\n--- Passengers Menu ---\n");
    printf("\n1. Add Passenger");
    printf("\n2. Delete Passenger");
    printf("\n3. Update Passenger Passport Number");
    printf("\n4. Display Passengers");
    printf("\n5. Back\n");
    printf("********************\n");
    printf("\n\nEnter your choice: ");
}

void displayFlightsMenu() {
    printf("\n*** Flights Menu ***\n");
    printf("1. Add new flight\n");
    printf("2. Update flight information\n");
    printf("3. Delete flight\n");
    printf("4. Display all flights\n");
    printf("5. Back to main menu\n");
    printf("********************\n");
}

void displayEmployeesMenu() {
    printf("\n\n--- Employees Menu ---\n");
    printf("\n1. Add Employee");
    printf("\n2. Update Employee");
    printf("\n3. Delete Employee");
    printf("\n4. Display Employees");
    printf("\n5. Back\n");
    printf("********************\n");
    printf("\n\nEnter your choice: ");
}

void displayTicketsMenu() {
    printf("\n\n--- Tickets Menu ---\n");
    printf("\n1. Add Ticket");
    printf("\n2. Update Employee");
    printf("\n3. Delete Ticket");
    printf("\n4. Display Tickets");
    printf("\n5. Back\n");
    printf("********************\n");
    printf("\n\nEnter your choice: ");
}

void displayAirportsMenu() {
    printf("\n\n--- Airports Menu ---\n");
    printf("\n1. Add Airport");
    printf("\n2. Update Employee");
    printf("\n3. Delete Airport");
    printf("\n4. Display Airports");
    printf("\n5. Back\n");
    printf("********************\n");
    printf("\n\nEnter your choice: ");
}

void menu() {
    int mainMenuChoice, passengersMenuChoice, flightsMenuChoice, employeesMenuChoice, ticketsMenuChoice, airportsMenuChoice;
    char name[50], flightNumber[20], destination[50],  location[50];

    int id, ticketNumber, passengerId, flightId;
pthread_t thread_id;

    displayMainMenu();

    while (1) {
        scanf("%d", &mainMenuChoice);

        switch (mainMenuChoice) {
            case 1:
            pthread_create(&thread_id, NULL, managePassengers, NULL);
                pthread_join(thread_id, NULL);
                break;
                
                while (1) {
                    displayPassengersMenu();
                    scanf("%d", &passengersMenuChoice);

                    switch (passengersMenuChoice) {
                        case 1:
                              
                            addPassenger();
                            break;
                        case 2:
                            printf("\nEnter passenger ID: ");
                            scanf("%d", &id);
                            deletePassenger(id);
                            break;
                        case 3:
                           updatePassenger();
                            break;
                        case 4:
                            displayPassengers();
                            break;
                        case 5:
                            displayMainMenu();
                            break;
                        default:
                            printf("\nInvalid choice. Please try again.\n");
                    }
                    if (passengersMenuChoice == 5) {
                        break;
                    }
                }
                break;
            case 2:
            pthread_create(&thread_id, NULL, manageFlights, NULL);
                pthread_join(thread_id, NULL);
                break;
    while (1) {
        displayFlightsMenu();
        scanf("%d", &flightsMenuChoice);

        switch (flightsMenuChoice) {
            case 1:
                {
                    char flightNumber[20], destination[50], gate[10], arrivalTime[20], departureTime[20];
                    int id;

                    printf("\nEnter flight number: ");
                    scanf(" %[^\n]s", flightNumber);
                    printf("Enter destination: ");
                    scanf(" %[^\n]s", destination);
                    printf("Enter gate: ");
                    scanf(" %[^\n]s", gate);
                    printf("Enter arrival time: ");
                    scanf(" %[^\n]s", arrivalTime);
                    printf("Enter departure time: ");
                    scanf(" %[^\n]s", departureTime);
                    printf("Enter flight ID: ");
                    scanf("%d", &id);

                    addFlight(id, flightNumber, destination, gate, arrivalTime, departureTime);
                }
                break;

            case 2:
                {
                    int flightIdToUpdate;
                    printf("\nEnter flight ID to update: ");
                    scanf("%d", &flightIdToUpdate);
                    updateFlightInfo(flightIdToUpdate);
                }
                break;

            case 3:
                {
                    int idToDelete;
                    printf("\nEnter flight ID to delete: ");
                    scanf("%d", &idToDelete);
                    deleteFlight(idToDelete);
                }
                break;

            case 4:
                displayFlights();
                break;

            case 5:
                displayMainMenu();
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
                displayMainMenu();
                break;
        }

        if (flightsMenuChoice == 5) {
            break;
        }
    }
    break;
            case 3:
            pthread_create(&thread_id, NULL, manageEmployees, NULL);
                pthread_join(thread_id, NULL);
                break;
    while (1) {
        displayEmployeesMenu();
        scanf("%d", &employeesMenuChoice);

        switch (employeesMenuChoice) {
            case 1:
                char firstName[50], lastName[50], employeeID[20], role[50], contactNumber[20], email[50];
                
                printf("Enter employee ID (numeric): ");
                scanf("%d", &id);
                printf("\nEnter employee first name: ");
                scanf(" %[^\n]s", firstName);
                printf("Enter employee last name: ");
                scanf(" %[^\n]s", lastName);
                printf("Enter employee role: ");
                scanf(" %[^\n]s", role);
                printf("Enter employee contact number: ");
                scanf(" %[^\n]s", contactNumber);
                printf("Enter employee email: ");
                scanf(" %[^\n]s", email);
                
                addEmployee(id, firstName, lastName, contactNumber, email, role);
                break;

            case 2:
                int empId;  
        printf("\nEnter the Employee ID to update: ");
        scanf("%d", &empId);
        updateEmployeeInfo(empId);
                break;

            case 3:
                int empIdToDelete;  
        printf("\nEnter employee ID to delete: ");
        scanf("%d", &empIdToDelete);
        deleteEmployee(empIdToDelete);
                break;

            case 4:
                displayEmployees();
                break;

            case 5:
                displayMainMenu();
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

        if (employeesMenuChoice == 5) {
            break;  
        }
    }
    break;
            case 4:
            pthread_create(&thread_id, NULL, manageTickets, NULL);
                pthread_join(thread_id, NULL);
    while (1) {
        displayTicketsMenu();
        scanf("%d", &ticketsMenuChoice);

        switch (ticketsMenuChoice) {
            case 1:
                int ticketNumber, passengerId, flightId;
                char seatNumber[10];

                printf("\nEnter ticket number: ");
                scanf("%d", &ticketNumber);
                printf("Enter passenger ID: ");
                scanf("%d", &passengerId);
                printf("Enter flight ID: ");
                scanf("%d", &flightId);
                printf("Enter seat number: ");
                scanf(" %[^\n]s", seatNumber);

                addTicket(ticketNumber, passengerId, flightId, seatNumber);
                break;
            case 2:
                int ticketNumberToDelete;
                printf("\nEnter ticket number to delete: ");
                scanf("%d", &ticketNumberToDelete);
                deleteTicket(ticketNumberToDelete);
                break;
            case 3:
                int ticketNumberToUpdate;
                printf("\nEnter ticket number to update: ");
                scanf("%d", &ticketNumberToUpdate);
                updateTicketInfo(ticketNumberToUpdate);
                break;
            case 4:
                displayTickets();
                break;
            case 5:
                displayMainMenu();
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }

        if (ticketsMenuChoice == 5) {
            break;
        }
    }
    break;

case 5:
    while (1) {
        displayAirportsMenu();
        scanf("%d", &airportsMenuChoice);

        switch (airportsMenuChoice) {
            case 1:
                int airportId;
                char airportCode[10], airportName[50], location[50];

                printf("\nEnter airport ID: ");
                scanf("%d", &airportId);
                printf("Enter airport code: ");
                scanf(" %[^\n]s", airportCode);
                printf("Enter airport name: ");
                scanf(" %[^\n]s", airportName);
                printf("Enter location: ");
                scanf(" %[^\n]s", location);

                addAirport(airportId, airportCode, airportName, location);
                break;
            case 2:
                int airportIdToUpdate;
                printf("\nEnter airport ID to update: ");
                scanf("%d", &airportIdToUpdate);
                updateAirportInfo(airportIdToUpdate);
                break;
            case 3:
                int airportIdToDelete;
                printf("\nEnter airport ID to delete: ");
                scanf("%d", &airportIdToDelete);
                deleteAirport(airportIdToDelete);
                break;
            case 4:
                displayAirports();
                break;
            case 5:
                displayMainMenu();
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }

        if (airportsMenuChoice == 5) {
            break;
        }
    }
    break;
            
            case 6:
                printf("\nExiting program...\n");
                exit(0);
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}


//threading

void* managePassengers(void* data) {
    printf("Passenger Management Thread\n");
    pthread_exit(NULL);
}

void* manageFlights(void* data) {
    printf("Flight Management Thread\n");
    pthread_exit(NULL);
}

void* manageEmployees(void* data) {
    printf("Employee Management Thread\n");
    pthread_exit(NULL);
}

void* manageTickets(void* data) {
    printf("Ticket Management Thread\n");
    pthread_exit(NULL);
}