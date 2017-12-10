// OneDay.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace std;

//function prototype
void readFile(string, string[], const int);
void intro(int, string[]);
void startGame(int, string[], string[], string[], string[], string[], string[], string[]);
void credits();
void finish();
void bestEnding(string, int, string[], string[], string[], string[], string[], string[], string[], int []);
void worstEnding(string, int, string[], string[], string[], string[], string[], string[], string[], int []);
int isExitChoice(int);
int inputValid(int);

int main()
{
    //Arrays to store choices and narratives
    const int introNar = 1;             // //size for intro array
    const int sizeNarChoices = 18;      //size for Narrative and Choice arrays
    const int sizeLoops = 4;            //size for Loops Narrative array
    const int sizeMainNar = 11;         //size for Main Narrative array
    const int sizedepNar = 2;   //size for dependent Narrative array
    const int endNar = 4; //size for ending Narrative array

    string introNarrative[introNar];     //intro to game
    string choices[sizeNarChoices];	    //choices
    string narrative[sizeNarChoices];	    //choices narrative
    string loopsNarrative[sizeLoops]; //narrative in loops
    string mainNarrative[sizeMainNar];    //main narratives
    string dependentNarrative[sizedepNar]; //narrative that depends on previous choices
    string endingNarrative[endNar]; //ending narrative

    //Store data from files to arrays
    string fileName;
    int mainOption;

    fileName = "introToGame.txt";	//name of file with intro
    readFile(fileName, introNarrative, introNar);

    fileName = "choices.txt";	//name of file with choices
    readFile(fileName, choices, sizeNarChoices);

    fileName = "narrative.txt";	//name of file with narrative
    readFile(fileName, narrative, sizeNarChoices);

    fileName = "loopsNarrative.txt";	//name of file with narrative inside the loops
    readFile(fileName, loopsNarrative, sizeLoops);

    fileName = "mainNarrative.txt";	//name of file with main narrative
    readFile(fileName, mainNarrative, sizeMainNar);

    fileName = "dependentNarrative.txt";	//name of file with dependent narrative- depends on first decision
    readFile(fileName, dependentNarrative, sizedepNar);

    fileName = "endingNarrative.txt";	//name of file with ending narrative
    readFile(fileName, endingNarrative, endNar);

    //Prompt user to - start game, see credits or exit
    cout << "Welcome to One Day! Type the following number to:" << endl;

    bool exitOption = false;
    while (!exitOption)
    {
        cout << endl << "1. Play Game." << endl << "2. Credits. " << endl << "3. Exit(available during the game too)." << endl;
        cin >> mainOption;
        inputValid(mainOption);

        switch (mainOption)
        {
        case 1:
        {
            //display intro
            intro(1, introNarrative);
            startGame(mainOption, introNarrative, choices, narrative, loopsNarrative, mainNarrative, dependentNarrative, endingNarrative);
            break;
        }
        case 2:
        {
            credits();
            break;
        }
        case 3:
        {
            exitOption = true;
            break;
        }
        }
    }
    finish();
    exit(0);
}

//Read from file
void readFile(string fileName, string foo[], int size)
{
    string line;
    int i = 0;

    ifstream myfile;

    myfile.open(fileName);

    //store lines in the same element
    //when character '*' is found move to the next element
    for (int i = 0; i < size; i++)
    {
        while (getline(myfile, line))
        {
            if (line == "*")	//ignore line with *
            {
                break;
            }
            else
            {
                foo[i] += line + "\n";

            }
        }
    }
    myfile.close();
}

//Test if player wants to exit the game
int isExitChoice(int choice)
{
    //bool result;
    //result = false;
    if (choice == 3)
    {
        cout << "Exit this Game (Y/N)?";
        char exitYN;
        cin >> exitYN;
        if (exitYN == 'Y' || exitYN == 'y')
        {
            //result = true;
            finish();
            exit(0);
        }
        else if (exitYN == 'N' || exitYN == 'n')
        {
            cout << "Please, enter 1 or 2:" << endl;
            cin >> choice;
        }
    }
    //return result;
    return choice;
}

//Test if input is valid
int inputValid(int choice)
{
    //Test if input is not an integer
    while (!choice)
    {
        cin.clear();
        cin.ignore(80, '\n');
        cout << "Please, enter an integer: " << endl;
        cin >> choice;
    }
    //Test if input is bigger than 3
    while (choice > 3)
    {
        cout << "Please, choose 1 or 2: " << endl;
        cin >> choice;
    }
    //Test if input is smaller than 1
    while (choice < 1)
    {
        cout << "Please, choose 1 or 2: " << endl;
        cin >> choice;
    }
    return choice;
}

void startGame(int choice, string introNarrative[], string choices[], string narrative[], string loopsNarrative[], string mainNarrative[], string dependentNarrative[], string endingNarrative[])
{
    const int sizePlayChoices = 9;     //size of playerChoices array (9 decisions)
    string playerName;
    int playerChoices[sizePlayChoices];

    //Decision #1
    //Print choices from array
    cout << endl << choices[0] ; //ignore
    cout << choices[1] << endl;  //intervene
    cin >> choice;

    //Test if input is valid
    choice = inputValid(choice);
    choice = isExitChoice(choice);

    cout << endl;
    playerChoices[0] = choice; //store player choice in array

    switch (choice)
    {
    case 1:
    {
        cout << endl << narrative[0] << endl;
        break;
    }
    case 2: //good choice
    {
        cout << endl << narrative[1] << endl;
        break;
    }
    }

    //MAIN NARRATIVE
    cout << mainNarrative[0];

    //Decision #2
    cout << endl << choices[2]; //ignore
    cout << choices[3] << endl;  //follow
    cin >> choice;

    //Test if input is valid
    choice = inputValid(choice);
    choice = isExitChoice(choice);
    cout << endl;
    playerChoices[1] = choice; //store player choice in array

    //Print narrative according to the value of choice
    //Exit if choice is 3
    switch (choice)
    {
    case 1:
    {
        //show narrative for that choice
        cout << narrative[2] << endl;

        //Loop #1
        while (choice == 1) //player decided to ignore
        {
            //show narrative for that loop 1 //create array for loops*
            cout << endl << loopsNarrative[0] << endl;

            //show choices again
            cout << endl << choices[2]; //ignore
            cout << choices[3]; //follow
            cin >> choice;

            //Test if input is valid
            choice = inputValid(choice);
            choice = isExitChoice(choice);
            cout << endl;
            playerChoices[1] = choice; //store player choice in array
        }
    }   //don't break to continue with case 2
    case 2:
    {
        cout << endl << narrative[3] << endl;   //decided to follow
        break;
    }
    }

    //Decision #3
    //Print choices from array
    cout << endl << choices[4]; //inform
    cout << choices[5]; //convince
    cin >> choice;

    //Test if input is valid
    choice = inputValid(choice);
    choice = isExitChoice(choice);
    cout << endl;
    playerChoices[2] = choice; //store player choice in array

    //Print narrative according to the value of choice
    //Exit if choice is 3
    switch (choice )
    {
    case 2:
    {
        cout << endl << narrative[5] << endl;

        //Following path depends on decision 1

        //Player chose 1 (ignore)on first decision
        if (playerChoices[0] == 1)
        {
            cout << "The boy asks for your name: " << endl;
            cin >> playerName;
            cout << "Okay " << playerName << "," << " why are you here?" << endl;
            cout << "I am here to convince you that what you are about to do is wrong." << endl;

            //Show rest of dependent narrative
            cout << dependentNarrative[0] << endl;

            //Loop #2
            while(choice == 2)  //keeps deciding to convince (choice 5)
            {
                //Show narrative for that loop 2
                cout << endl << loopsNarrative[1] << endl;

                //Give the player the opportunity to inform or convince again
                //Print choices from array
                cout << endl << choices[4]; //inform
                cout << choices[5]; //convince
                cin >> choice;

                //Test if input is valid
                choice = inputValid(choice);
                choice = isExitChoice(choice);
                cout << endl;
                playerChoices[2] = choice; //store player choice in array
            }
        }   //don't break to continue with case 1

        //Player chose 2 (intervene)on first decision
        else if(playerChoices[0] == 2)
        {
            cout << dependentNarrative[0] << endl;
            cout << "He tells you that his name is Lars and you introduce yourself to him as: ";
            cin >> playerName;
            cout << endl;
            cout << "Before you go on with your separate ways, you invite Lars over to your house around late afternoon. He agrees to hang out with you." << endl;
            cout << mainNarrative[3];   //best main narrative 2
            cout << mainNarrative[4];   //best main narrative 3
            bestEnding(playerName, choice, introNarrative, choices, narrative, loopsNarrative, mainNarrative, dependentNarrative, endingNarrative, playerChoices);
            break;
        }
    }
    case 1:
    {
        cout << endl << narrative[4] << endl;
        //Show main narrative 2 //worst imperfect ending
        cout << mainNarrative[1];

        //Show main narrative 3 ////worst imperfect ending
        cout << mainNarrative[2];
        worstEnding(playerName, choice, introNarrative, choices, narrative, loopsNarrative, mainNarrative, dependentNarrative, endingNarrative, playerChoices);
        break;
    }
    }
}

void bestEnding(string playerName, int choice, string introNarrative[], string choices[], string narrative[], string loopsNarrative[], string mainNarrative[], string dependentNarrative[], string endingNarrative[], int playerChoices[])
{
    //display choice 7 and 8
    //Decision #4
    //Print choices from array
    cout << endl << choices[6]; //defend
    cout << choices[7]; //convince
    cin >> choice;

    //Test if input is valid
    choice = inputValid(choice);
    choice = isExitChoice(choice);
    cout << endl;
    playerChoices[3] = choice; //store player choice in array

    //Print narrative according to the value of choice
    //Exit if choice is 3
    switch (choice)
    {
    case 1: //choice [6] //defend
    {
        cout << endl << narrative[6] << endl;
        break;
    }
    case 2: //choice [7] //convince
    {
        cout << endl << narrative[7] << endl;
        break;
    }
    }

    //Display best main narrative 4
    cout << mainNarrative[5];
    //Display best main narrative 5
    cout << mainNarrative[6];
    //Display best main narrative 6
    cout << mainNarrative[7];

    //Decision #5
    //Print choices from array
    cout << endl << choices[8]; //go after the thief
    cout << choices[9]; //ignore thief
    cin >> choice;

    //Test if input is valid
    choice = inputValid(choice);
    choice = isExitChoice(choice);
    cout << endl;
    playerChoices[4] = choice; //store player choice in array

    //Print narrative according to the value of choice
    //Exit if choice is 3
    switch (choice)
    {
    case 1: //choice [8] //go after the thief
    {
        cout << "You all reach your house safely. Once everyone is inside, you all take a sit and Mr. Astrea begins to talk." << endl;
        cout << "Thank you from the bottom of my heart, young " << playerName << "." << " With help from you and your friend, I was able to rescue my dear daughter." << endl;
        cout << "Words can't express my gratitude." << endl;
        cout << endl << narrative[8] << endl;
        //ending
        endingNarrative[0];
        //create method to exit program now
        break;
    }
    case 2: //choice [9] //ignore thief
    {
        cout << "You turn down their invitation in an abrupt manner and start heading towards the door where you last saw the thief." << endl;
        cout << "Lars follows behind and poses the question." << endl;
        cout << "Lars: What is the matter?" << endl;
        cout << "You: I saw the thief, Lars. He went through that door upfront after getting it to open." << endl;
        cout << "That is impossible " << playerName << ". " << "Why would the same thief show up at party?" << endl;
        cout << endl << narrative[9] << endl;
        break;
    }
    }

    //Decision #6
    //Print choices from array
    cout << endl << choices[10]; //ignore thief again
    cout << choices[11]; //ignore toast find out what's happening
    cin >> choice;

    //Test if input is valid
    choice = inputValid(choice);
    choice = isExitChoice(choice);
    cout << endl;
    playerChoices[5] = choice; //store player choice in array

    //Print narrative according to the value of choice
    //Exit if choice is 3
    switch (choice)
    {
    case 1: //choice [10] //ignore thief again
    {
        cout << endl << narrative[10] << endl;
        //Loop #3
        while(choice == 1)  //keeps deciding to ignore thief again
        {
            //Show narrative for that loop 2
            cout << endl << loopsNarrative[3] << endl;

            //Give the player the opportunity to ignore thief or find what's happening
            //Print choices from array
            cout << endl << choices[10]; //ignore
            cout << choices[11]; //find what's happening
            cin >> choice;

            //Test if input is valid
            choice = inputValid(choice);
            choice = isExitChoice(choice);
            cout << endl;
            playerChoices[5] = choice; //store player choice in array
        }
    } //don't break to continue with case 2

    case 2: //choice [11] //ignore toast find out what's happening
    {
        cout << endl << narrative[11] << endl;
        //ending
        cout << "You all reach your house safely. Once everyone is inside, you all take a sit and Mr. Astrea begins to talk." << endl;
        cout << "Thank you from the bottom of my heart, young " << playerName << "." << endl;
        endingNarrative[1];
        //create method to exit program now*
        break;
    }
    }
}

void worstEnding(string playerName, int choice, string introNarrative[], string choices[], string narrative[], string loopsNarrative[], string mainNarrative[], string dependentNarrative[], string endingNarrative[], int playerChoices[])
{
    //display choice 7 and 8 (worst ending choices[12] and choices[13])
    //Decision #7
    //Print choices from array
    cout << endl << choices[12]; //defend
    cout << choices[13]; //don't resist
    cin >> choice;

    //Test if input is valid
    choice = inputValid(choice);
    choice = isExitChoice(choice);
    cout << endl;
    playerChoices[6] = choice; //store player choice in array

    //Print narrative according to the value of choice
    //Exit if choice is 3
    switch (choice)
    {
    case 1: //choice [12] //defend
    {
        cout << endl << narrative[12] << endl;
        break;
    }
    case 2: //choice [13] //don't resist
    {
        cout << endl << narrative[13] << endl;
        break;
    }
    }

    //Display worst main narrative 4
    cout << mainNarrative[8];
    //Display worst main narrative 5
    cout << mainNarrative[9];
    //Display worst main narrative 6
    cout << mainNarrative[10];

    //Decision #8
    //Print choices from array
    cout << endl << choices[14]; //go after thief
    cout << choices[15]; //ignore thief
    cin >> choice;

    //Test if input is valid
    choice = inputValid(choice);
    choice = isExitChoice(choice);
    cout << endl;
    playerChoices[7] = choice; //store player choice in array

    //Print narrative according to the value of choice
    //Exit if choice is 3
    switch (choice)
    {
    case 1: //choice [14] //go after the thief
    {
        cout << endl << narrative[14] << endl;
        //ending
        cout << "You all reach your house safely. Once everyone is inside, you all take a sit and Mr. Astrea begins to talk." << endl;
        cout << "Thank you from the bottom of my heart, young " << playerName << "." << endl;
        endingNarrative[2];
        //create method to exit program now*
        break;
    }
    case 2: //choice [15] //ignore thief
    {
        cout << endl << narrative[15] << endl;
        break;
    }
    }

    //Decision #9
    //Print choices from array
    cout << endl << choices[16]; //ignore again
    cout << choices[17]; //find out what's happening
    cin >> choice;

    //Test if input is valid
    choice = inputValid(choice);
    choice = isExitChoice(choice);
    cout << endl;
    playerChoices[8] = choice; //store player choice in array

    //Print narrative according to the value of choice
    //Exit if choice is 3
    switch (choice)
    {
    case 1: //choice [16] //go after the thief
    {
        cout << endl << narrative[16] << endl;
        //Loop #3
        while(choice == 1)  //keeps deciding to ignore thief again
        {
            //Show narrative for that loop 2
            cout << endl << loopsNarrative[2] << endl;

            //Give the player the opportunity to ignore thief or find what's happening
            //Print choices from array
            cout << endl << choices[16]; //ignore
            cout << choices[17]; //find what's happening
            cin >> choice;

            //Test if input is valid
            choice = inputValid(choice);
            choice = isExitChoice(choice);
            cout << endl;
            playerChoices[8] = choice; //store player choice in array
        }
    } //don't break continue with case 2
    case 2: //choice [17] //ignore thief
    {
        cout << endl << narrative[17] << endl;
        cout << "You all reach your house safely. Once everyone is inside, you all take a sit and Mr. Astrea begins to talk." << endl;
        cout << "Thank you from the bottom of my heart, young " << playerName << "." << endl;
        endingNarrative[3];
        break;
    }
    }
}

void intro(int size, string introNarrative[] )
{
    cout << endl << introNarrative[0] << endl;
}

void credits()
{
    cout << "	   CREDITS" << endl;
    cout << "	   One Day" << endl << endl;
    cout << "	  Amy Garcia" << endl;
    cout << "	  Rene Garcia" << endl;
    cout << "	 William Morgan" << endl;
    cout << "	 Brandon Perez" << endl;
    cout << "	Franklyn Medina" << endl;
    cout << endl;
}

void finish()
{
    cout << "Thanks for playing!" << endl;
}
