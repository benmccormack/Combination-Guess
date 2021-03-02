/*
Program compiled in xCode
--------
Exam Replacement Assignment.
A program which takes the users combination code, encrypts it and compares it to the already encrypted access code before
decrypting the users code again. The amount of correct and incorrect entires made by the user is recorded.
-------
By Ben McCormack
22.4.2020 
*/

#include <stdio.h>
#include <stdlib.h>
//Symbolic Name(s)
#define SIZE 4
//Structure Template for the calculation of correct and incorrect entries
struct code_counter
{
	int correct_code;
	int wrong_code;
};
//This function is used for the menu
void menu(int *selection);
//The function is to get the code from the user or randomly generate a code
void userInput(int *userNums);
//The function responsible for the encryption of the code.
void encrypt(int *userNums);
//The function which compares the users code and the access code.
void compareCode(int *userNums, int *access_code);
//The function which decrypts the users code.
void decryptCode(int *userNums);
//The function which shows the amount of times the correct and wrong code has been entered
void codeCheck();
//The function which will terminate the program
void terminate();
//global variable for the codeCheck function
struct code_counter score;



int main()
{
	int menuCounter;
	int menuSelect;
	int userNums[SIZE];
	int access_code[SIZE] = {4,5,2,3};

	while(menuSelect !=6)
	{
		menu(&menuSelect);

		if (menuSelect == 1)
		{
			//The function which asks the user to enter their 4 numbers or randomly generate them will now be called
			userInput(userNums);
			menuCounter=1;
		} //end if statement for menu option 1
		else if(menuSelect == 2)
		{
			if (menuCounter==1)
			{
				//The function that encrpyts the users code is now called
				encrypt(userNums);
				menuCounter = 2;
			}
			else if (menuCounter>1)
			{
				printf("Error. You're code has already been encrypted.\n");
			}
			else
			{
				printf("You must enter your your code or generate it before encrypting\n");
			} //end if else statement
		}
		else if(menuSelect == 3)
		{
			//The function to compare the users code to the access code is now called.
			compareCode(userNums,access_code);
		}
		else if(menuSelect == 4)
		{
			if (menuCounter>1)
			{
				//The function to decrypt the users code will now be called
				decryptCode(userNums);
			}
			else
			{
				printf("You must encrypt your code before completing this step.\n");
			}

		}
		else if(menuSelect == 5)
		{
			codeCheck();
		}
		else
		{
			printf("Invalid Input entered please try again.\n");
		}

		
	} //end while loop.

	if (menuSelect == 6)
	{
		//The function that will gracefully terminate the program upon the users request.
		terminate();
		return 0;
	} //end if statement for menu option 6

} //end main()

/*Implementing the menu function */
void menu(int *selection)
{
  printf("\n\n====================== Welcome to the code encryptor ======================\n\n");
  printf("\n1. Press 1 to enter a code or generate a random code.\n");
  printf("\n2. Press 2 to encrypt your code.\n");
  printf("\n3. Press 3 to check if encrypted code matches access code.\n");
  printf("\n4. Press 4 to decrypt code.\n");
  printf("\n5. Press 5 to display the number of times encrypted code is correct/incorrect.\n");
  printf("\n6. Press 6 to exit the program\n");
  printf("\n\n===========================================================================\n\n");

  //The users menu slection is recorder
  scanf("%d",selection);
}

/* Implementing the function which takes input from the user or randomly generates 4 numbers*/
void userInput(int *userNums)
{
	//This variable holds the users choice. If they want to enter their own numbers or generate them
	int userChoice;
	//counter variable
	int i;

	printf("Press 1 if you would like to enter your own four numbers.\n");
	printf("Press 2 if you would like to randomly generate four numbers.\n");

	scanf("%d",&userChoice);

	if (userChoice == 1)
	{
		printf("Please enter 4 numbers\n");
		for (int i = 0; i < SIZE; ++i)
		{
			scanf("%d",&*(userNums+i));
			if (*(userNums+i) > 9 || *(userNums+i) < 0)
			{
				//User is presented with an error message and returned to the main menu if an invalid number is entered while selecting their combination
				printf("Invalid number entered.... returning to menu please try again.\n");
				return;
			}
		} //end for loop
	}
	else if (userChoice == 2)
	{
		printf("You're numbers have been randomly generated\n");
		for (int i = 0; i < SIZE; ++i)
		{
			//The users combination is being randomly generated number by number and placed into an array.
			*(userNums+i) = rand()%9;
		} //end for loop

	}
	else
	{
		//If the user makes an invalid menu entry they are told so and returned to the main menu.
		printf("Invalid input entered... returning to menu.\n");
	} //end if else statement
} //end function userInput

/*Implementing the function which encrypts the users code*/
void encrypt(int *userNums)
{
	//tmp variable to hold the number being swapped
	int tmp;
	//counter variable
	int i;

	//Encryption Process - Swapping the first and third number
	tmp = *(userNums+0);
	*(userNums+0) = *(userNums+2);
	*(userNums+2) = tmp;

	//Encryption Process - Swapping the second and fourth number
	tmp = *(userNums+1);
	*(userNums+1) = *(userNums+3);
	*(userNums+3) = tmp;

	//Encryption Process - Adding 1 to each number
	for (int i = 0; i < SIZE; ++i)
	{
		//One is added to each number. The for loop cycles through every element in the array
		*(userNums+i) = *(userNums+i) + 1;
	} //end for loop

	//Encryption Process - Making numbers that are equal to 10 a 0

	for (int i = 0; i < SIZE; ++i)
	{
		if(*(userNums+i) == 10)
		{
			*(userNums+i) = 0;
		} //end if statement
	} //end for loop
} //end function encrypt()

/*Implementing the function that compares the user code and the access code*/
void compareCode(int *userNums, int *access_code)
{
	//Counter to keep track of the correct numbers in the users encrypted code.
	int correctNum = 0;
	//counter variable
	int i;

	for (int i = 0; i < SIZE; ++i)
	{
		//If the users number is the same as the number in the access code the counter is increased.
		if (*(userNums+i)==*(access_code+i))
		{
			correctNum++;
		} //end if statement
	} //end for loop

	//The following message is displayed if the correct code is entered
	if (correctNum == 4)
	{
		printf("Correct Code entered\n");
		//The counter for the correct entry of the code is increased by 1
		score.correct_code++;
	}
	else
	{
		//The following message is displayed if the incorrect code is entered.
		printf("Wrong code enterd\n");
		//The counter for the incorrect entry of the code is increased by 1
		score.wrong_code++;
	} //end if else statement
} //end function compareCode()

/*Implementing the function that decrypts the code previously encrypted*/
void decryptCode(int *userNums)
{
	int tmp;
	int i;

	//Decryption Process - Subtacting one from each number
	for (int i = 0; i < SIZE; ++i)
	{
		*(userNums+i)=*(userNums+i)-1;
	} //end for loop

	//Decryption Process - Changing any number equal to -1 to a 9
	for (int i = 0; i < SIZE; ++i)
	{
		if (*(userNums+i)==-1)
		{
			*(userNums+i) = 9;
		} //end if statement
	} //end for loop

	//Decryption Process - Swapping the first number with the third number
	tmp = *(userNums+0);
	*(userNums+0) = *(userNums+2);
	*(userNums+2) = tmp;

	//Decryption Process - Swapping the second number with the fourth number
	tmp = *(userNums+1);
	*(userNums+1) = *(userNums+3);
	*(userNums+3) = tmp;

} //end function decryptCode()

/*Implementing the function which displays the amount of times the correct code and incorrect code has been entered*/
void codeCheck()
{
	printf("The correct code has been entered %d times\n", score.correct_code);
	printf("The wrong code has beene entered %d times\n",score.wrong_code);
}
/*Implemeting the function thst will terminate the program*/
void terminate()
{
	printf("Thanks for playing.\n");
} //end function terminate()
