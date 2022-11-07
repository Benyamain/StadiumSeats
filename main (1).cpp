/* Benyamain Yacoob & Ara Oladipo
 11-30-2021
 Intro to Programming
 Project #3 */

#include <iostream>
#include <iomanip>

using namespace std;

// Declaration of global variables
const int ROWS = 10;
const int SEATS_PER_ROW = 30;
const int MAX_SEATS_IN_THEATER = 300;
char seatsAvailable[ROWS][SEATS_PER_ROW];
int totalTicketsSold = 0;
int totalDollarsMade = 0;
 
// validateInput: Tells manager to confirm their desired input
// INPUT: A character ( choiceConfirmation ) that needs to be either 'Y' or 'N'
// Function called when input from user needs to be confirmed
// OUTPUT: Asks for confirmation
char validateInput(char choiceConfirmation)
{
    choiceConfirmation = toupper(choiceConfirmation);

    while (choiceConfirmation != 'Y' && choiceConfirmation != 'N')
    {
        cout << "ERROR: Invalid input.\n";
        cout << "Please type (Y/N): ";
        cin >> choiceConfirmation;

        choiceConfirmation = toupper(choiceConfirmation);
    }
    
    return choiceConfirmation;
}

// showAvailableSeats: Tells the manager what seats are available in the entire auditorium
// INPUT: None
// Function called by switch case in the main function
// OUTPUT: Returns all the current seats available
void showAvailableSeats()
{
    cout << setw(55) << "Seats\n\n\t";

    // Printing the seats
    for (int i = 0; i < SEATS_PER_ROW; i++)
        cout << setw(3) << i;

    cout << endl << endl;

    // Populate array with # from 0 to 29
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < SEATS_PER_ROW; j++)
            seatsAvailable[i][j] = '#'; // Presets seating chart to having all seats available
    }

    // Printing the values of the array
    for (int i = 0; i < ROWS; i++)
    {
        cout << "Row " << setw(2) << i << "  ";

        for (int j = 0; j < SEATS_PER_ROW; j++)
            cout << setw(3) << static_cast<char>(seatsAvailable[i][j]); // Convert ASCII value into '#'

        cout << endl;
    }

    // Displays the legend for the manager to look at
    cout << endl << setw(60) << "Legend:   *    =   Sold" << endl;
    cout << endl << setw(66) << "          #    =   Available\n" << endl;
    cout << endl << setw(70) << "Welcome to Rascal's Theatrical Center!\n";
}

// showSeatingChart: Visually shows the manager the updated seating chart
// INPUT: None
// Function called by switch case in the main function
// OUTPUT: Returns a picture of taken/available seats
void showSeatingChart()
{
    cout << setw(55) << "Seats\n\n\t";

    for (int i = 0; i < SEATS_PER_ROW; i++)
        cout << setw(3) << i;

    cout << endl << endl << endl;

    for (int i = 0; i < ROWS; i++)
    {
        cout << "Row " << setw(2) << i << "  ";

        for (int j = 0; j < SEATS_PER_ROW; j++)
            cout << setw(3) << static_cast<char>(seatsAvailable[i][j]);

        cout << endl;
    }
}

// showAvailableSeatsInRows: Tells manager how many seats are available in each row
// INPUT: None
// Function called by switch case in the main function
// OUTPUT: Returns a message of remaining available seats in each row
void showAvailableSeatsInRows()
{
    for (int i = 0; i < ROWS; i++)
    {
        int amountOfSeats = 0;

        cout << "Row " << i << " has ";

        for (int j = 0; j < SEATS_PER_ROW; j++)
        {
            if (seatsAvailable[i][j] == '#')
                amountOfSeats += 1; // Each time '#' is seen, the amount of seats in each row is incremented
        }

        cout << amountOfSeats << " seats" << endl;
    }
}

// showAllAvailableSeats: Visually shows the manager the updated seating chart
// INPUT: None
// Function called by switch case in the main function
// OUTPUT: Returns number of all the current seats available
void showAllAvailableSeats()
{
    int allSeatsAvailable = 0;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < SEATS_PER_ROW; j++)
        {
            if (seatsAvailable[i][j] == '#')
                allSeatsAvailable++;    // Each time '#' is seen, we count the total amount of seats available
        }
    }

    cout << "The auditorium has a total of " << allSeatsAvailable << " seats available\n";
}

// manager: Function that allows manager to interact with user interface to select some option
// INPUT: None
// Function automatically called in the main function
// OUTPUT: Automatically shows the menu for manager to look at
int manager()
{
    int managerChoice;
    char choiceConfirmation;    // We want to take into consideration if the manager chooses the wrong option accidentally

    do
    {
        // Displays the menu options
        cout << "\n----------------------------------------------------------------------------------------------------\n\n";
        cout << "\n(1) Sell tickets\t(2) Display the total dollar value of all tickets sold\n";
        cout << "(3) Display the total number of tickets sold\t(4) Display the number of seats available in each row\n";
        cout << "(5) Display the number of seats available in the entire auditorium\t(6) Display the current seating chart\n";
        cout << "(7) Exit the system\n\n";
        cout << "What do you want to do today?: ";
        cin >> managerChoice;
        cout << "Did you mean to press " << managerChoice << " (Y/N)?: ";
        cin >> choiceConfirmation;
        cout << "\n----------------------------------------------------------------------------------------------------\n\n";

        choiceConfirmation = validateInput(choiceConfirmation);
    } while (choiceConfirmation != 'Y');

    return managerChoice;
}

// sellTickets: Sell a ticket for a customer
// INPUT: None
// Function called by switch case in the main function
// OUTPUT: Returns price of ticket and its seating location
void sellTickets()
{
    int userRow, userSeat, desiredTicketsNum, trial = 0, totalCustomerTicketPrices = 0;
    bool continueLoop;

    do
    {
        cout << "How many ticket(s) do you want to buy?: ";
        cin >> desiredTicketsNum;

        if (desiredTicketsNum > MAX_SEATS_IN_THEATER)
        {
            cout << "Exceeds maximum number of tickets to buy!\n";
            cout << "The maximum number of tickets you can buy is 300.\n";
        }
        else if (desiredTicketsNum <= 0)
            cout << "You have to buy a ticket.\n";
            
    } while (desiredTicketsNum > MAX_SEATS_IN_THEATER || desiredTicketsNum <= 0);

    do
    {
        continueLoop = false;

        // Prompts user to request desired seat
        cout << "\nEnter the desired seat you want by telling me the row number, then the seat number.";
        cout << "\nFor example, Row 5 Seat 5 would be typed as (5 5): ";
        cin >> userRow >> userSeat;

        if (userRow < 0)
            cout << "There is no row number below 0.";
        else if (userRow > ROWS - 1)
            cout << "There is no row number above 9.";
        else if (userSeat < 0)
            cout << "There is no seat number below 0.";
        else if (userSeat > SEATS_PER_ROW - 1)
            cout << "There is no seat number above 29.";
        else
        {
            int ticketFormula = 5 * userRow + 10;   // Ticket cost for entire auditorium

            if (seatsAvailable[userRow][userSeat] == '#')
            {
                char choiceConfirmation;

                cout << "Row " << userRow << " seat " << userSeat << " is";
                cout << " available. The price of this seat is: $" << ticketFormula;
                cout << "\nDo you want to buy it (Y/N)?: ";
                cin >> choiceConfirmation;

                // Calling the function for manager to confirm input
                choiceConfirmation = validateInput(choiceConfirmation);

                if (choiceConfirmation == 'Y')
                {
                    trial++;

                    seatsAvailable[userRow][userSeat] = '*';    // Updates the seat to now being taken

                    totalTicketsSold++; // Increments number of tickets sold each time a ticket is bought
     
                    totalDollarsMade += ticketFormula;  // How much money the theater makes after whatever number of tickets

                    totalCustomerTicketPrices += ticketFormula;
                }
                else
                    cout << "Choose another ticket seat.";
            }
            else
            {
                char choiceConfirmation;

                cout << "\nSorry, these seats aren't available!" << endl;
                cout << "Do you want to continue (Y/N)?: ";
                cin >> choiceConfirmation;

                choiceConfirmation = validateInput(choiceConfirmation);

                if (choiceConfirmation == 'Y')
                    continueLoop = true;
                else
                    break;
            }
        }
    } while (trial < desiredTicketsNum || userRow < 0 || userRow > ROWS - 1 || userSeat < 0 || userSeat > SEATS_PER_ROW - 1 || continueLoop == true);

    cout << "\nThe total ticket cost is: $" << totalCustomerTicketPrices;
    cout << "\nTickets were purchased successfully." << endl;
}

int main()
{
    showAvailableSeats();   // Calling function

    // Exits the menu system by pressing number 7
    bool codeRunning = true;    // Terminates main function if set to false

    do
    {
        int managerChoice = manager();  // Store entered value from manager to be later used in the switch expression

        switch (managerChoice)
        {
        case 1: sellTickets();
            break;

        case 2: cout << "The theater has made a total of: $" << totalDollarsMade << endl;
            break;

        case 3: cout << "The theater has sold a total of: " << totalTicketsSold << " ticket(s)\n";
            break;

        case 4: showAvailableSeatsInRows();
            break;

        case 5: showAllAvailableSeats();
            break;

        case 6: showSeatingChart();
            break;

        case 7: codeRunning = false;
            cout << "\nHave a great day!";
            break;

        default:    cout << "That is not a valid number choice.\n";
            break;
        }
    } while (codeRunning);

    return 0;
}




