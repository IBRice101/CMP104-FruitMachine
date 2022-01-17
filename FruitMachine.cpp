//Fruit Machine by Isaac Basque-Rice for CMP104, Abertay Univerity, 2019.

//TODO: rotate vertically as opposed to horizontally
//		implement a clear way to show the user a line has stopped (I.E removing a row/column)
//		implement quit functionality

#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>  
#include <conio.h> 
#include <windows.h> 
#include <time.h> 
#include <string> 
#include <iostream> 
#include <chrono>
#include <thread>

using namespace std;

//The array that stores the fruit
std::string fruit[3][6] = 
{
    {"    A    ", "    B    ", "    C    ", "    D    ", "    E    ", "    F    "},
    {"    A    ", "    B    ", "    C    ", "    D    ", "    E    ", "    F    "},
    {"    A    ", "    B    ", "    C    ", "    D    ", "    E    ", "    F    "},
};

int credit = 0;

//when gamerunning != 1 exit the rotate while loop
bool gameRunning = 1;

//used later as a way of continuing the program AFTER a win/loss state is achieved
unsigned int cont;

//userinput vars
char key;
int foo = 0;

//array for when column stopped
bool columnStopped[3] = { false, false, false };

//when column stopped = true assign columnX to columnX var
std::string column1, column2, column3;

HANDLE hconsole;

void Rotate()
{
	//Where the array starts rotating (0 = A, 1 = B... etc.)
	int columnIndexes[3] = { 0, 1, 2 };

    while (true)
    {
        while (gameRunning)
        {
            std::cout << "Isaac Basque-Rice: Fruit Machine" << std::endl;
            std::cout << "Your credit is: \x9C" << credit << std::endl;
            std::cout << "Column 1: " << column1 << std::endl;
            std::cout << "Column 2: " << column2 << std::endl;
            std::cout << "Column 3: " << column3 << std::endl;
			std::cout << "            || " << std::endl;
            std::cout << "            \\/" << std::endl;

            //rotation
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    //maxes out at 6 (3+3, i+j)
                    int currentIndex = columnIndexes[j] + i;

                    //if whatever column has NOT stopped (according to columnstopped array)
                    if (!columnStopped[j])
                    {
                        //if end reached return to beginning
                        if (currentIndex > 5 && columnStopped[j] == false)
                        {
                            currentIndex = 0;
                        }
                    }

                    //write item to screen
                    std::cout << fruit[j][currentIndex]; 

                    //listens for keyboard hit
                    if (_kbhit())
                    {
						//sets local input var to the upper case version of the keypress
                        key = toupper(_getch());
                        foo = key;

                        //stop rotation
                        if (foo == 'A')
                        {
                            columnStopped[0] = true; //stop column rotation
                            column1 = fruit[2][currentIndex]; //set column1 var to whetever is held in fruit[0][currentIndex]
                            std::system("color 0C"); //change colour to light red
                        }
                        else if (foo == 'B')
                        {
                            columnStopped[1] = true;
                            column2 = fruit[1][currentIndex];
                            std::system("color 0E"); //light blue
                        }
                        else if (foo == 'C')
                        {
                            columnStopped[2] = true;
                            column3 = fruit[0][currentIndex];
                            std::system("color 0A"); //green
                        }
                    }
                }

                std::cout << std::endl;
                columnIndexes[i]++; //increments 
                //returns the array to the start once the counter goes above 5
                if (columnIndexes[i] > 5)
                {
                    columnIndexes[i] -= 6;
                }

            }

            //wait for x amount of time then clear the screen and return to the top of the loop
            std::this_thread::sleep_for(2000ms);
            std::system("cls");
            if (columnStopped[0] == true && columnStopped[1] == true && columnStopped[2] == true)
            {
                gameRunning = 0;
            }
        }
        std::cout << "column 1: " << column1 << std::endl; std::cout << "column 2: " << column2 << std::endl; std::cout << "column 3: " << column3 << std::endl;
        return;
    }
}

//should play at the start of each session
void Welcome(std::string name) 
{
    bool controls = 0;

    std::cout << "Welcome to the fruit machine, " << name << std::endl;
    std::system("color 01");
    std::this_thread::sleep_for(1s); //sleep for 1 second

    std::cout << "This Program was developed by" << std::endl;
    std::system("color 02");
    std::this_thread::sleep_for(1s);

    std::cout << "Isaac Basque-Rice" << std::endl;
    std::system("color 03");
    std::this_thread::sleep_for(1s);

    std::cout << "For CMP104" << std::endl;
    std::system("color 04");
    std::this_thread::sleep_for(1s);

    std::system("cls");
    std::system("color 07");

    std::cout << "Would you like to know the rules? (0 for no, 1 for yes)" << std::endl;
    std::cin >> controls;
    if (controls == 0)
    {
        return;
    }
    else
    {
        std::cout << "Rules:" << std::endl;
        std::cout << "    A to stop column 1, \n    B to stop column 2, \n    C to stop column 3" << std::endl;
		std::this_thread::sleep_for(1s);
        std::cout << "    where the arrow points is where you must watch." << std::endl;
		std::this_thread::sleep_for(1s);
        std::cout << "    0 for no, 1 or more for anything else (as can be seen above)" << std::endl;
		std::this_thread::sleep_for(1s);
        std::cout << "    If your credit drops below 0, you lose" << std::endl;
        
        this_thread::sleep_for(5s);
        return;
    }
}

int main()
{
	//dynamic
    std::string name;
	bool con = 1;

	//static
	int smPrize = 2;
	int lgPrize = 5;
	int loss = 3;

    //std::cout << "What is your name?" << std::endl;
    //std::cin >> name;
    //std::system("cls");
    //Welcome(name);

    std::cout << "How much money would you like to input?" << std::endl;
    std::cout << "\x9C"; std::cin >> credit;

	if (credit == 0)
	{
		con = false;
		std::cout << "You entered nothing, you can't do this, goodbye" << std::endl;
	}

	while (con)
	{
		Rotate();

		//big jackpot
		if (column1 == column2 && column2 == column3)
		{
			std::cout << "JACKPOT!!" << std::endl;
			std::cout << "you win \x9C" << lgPrize << std::endl; //note: '\x9C' is the escape char for the �/£ (GPB) symbol
			credit += lgPrize;
			std::cout << "your new balance is \x9C" << credit << std::endl;
			std::cout << "Would you like to continue? (0 for no, 1 or more for yes)" << std::endl;
			std::cin >> cont;

			if (cont == 0)
			{
				std::cout << "Congratulations! you won \x9C" << credit << std::endl;
				std::cout << "Goodbye!" << std::endl;
				columnStopped[0] = true; columnStopped[1] = true; columnStopped[2] = true;
				column1.clear(); column2.clear(); column3.clear();
				con = 0;
				return 0;
			}
			else
			{
				gameRunning = 1;
				columnStopped[0] = false; columnStopped[1] = false; columnStopped[2] = false;
				column1.clear(); column2.clear(); column3.clear();
			}
		}
		//small jackpot
		else if (column1 == column2 || column2 == column3 || column1 == column3) //perhaps too generous?
		{
			std::cout << "you won \x9C" << smPrize << std::endl;
			credit += smPrize;
			std::cout << " your new balance is \x9C" << credit << std::endl;
			std::cout << " Would you like to continue? (0 for no, 1 or more for yes)" << std::endl;
			std::cin >> cont;

			if (cont == 0)
			{
				std::cout << "Congratulations! you won \x9C" << credit << std::endl;
				std::cout << "Goodbye!" << std::endl;
				columnStopped[0] = true; columnStopped[1] = true; columnStopped[2] = true;
				column1.clear(); column2.clear(); column3.clear();
				con = 0;
				return 0;
			}
			else
			{
				gameRunning = 1;
				columnStopped[0] = false; columnStopped[1] = false; columnStopped[2] = false;
				column1.clear(); column2.clear(); column3.clear();
			}
		}
		//no win
		else
		{
			std::cout << "Better luck next time!" << std::endl;
			credit -= loss;
			std::cout << "your credit is now " << credit << std::endl;
			std::cout << "Would you like to continue? (0 for no, 1 or more for yes)" << std::endl;
			std::cin >> cont;

			if (cont == 0)
			{
				std::cout << "you won \x9C" << credit << std::endl;
				std::cout << "Goodbye!" << std::endl;
				columnStopped[0] = true; columnStopped[1] = true; columnStopped[2] = true;
				column1.clear(); column2.clear(); column3.clear();
				con = 0;
				return 0;
			}
			else if (credit == 0 || credit <= 0)
			{
				std::cout << "you do not have any funds, goodbye" << endl;
				columnStopped[0] = true; columnStopped[1] = true; columnStopped[2] = true;
				column1.clear(); column2.clear(); column3.clear();
				con = 0;
				return 0;
			}
			else
			{
				gameRunning = 1;
				columnStopped[0] = false; columnStopped[1] = false; columnStopped[2] = false;
			}
		}
	}

    return 0;
}
