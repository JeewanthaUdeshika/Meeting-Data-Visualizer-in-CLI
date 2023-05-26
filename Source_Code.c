/* CO222 Project 2 - Meeeting Data Visuallizer
 *
 * Final test with linked list
 *
 * P.H.J.U. Ariyawansha (E/18/028)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Definning the struct data type
typedef struct _
{
	char name[50];
	int partici;
	int time;
	int meetingCount;
} data;

typedef struct node
{
	data student;
	struct node *next;
} meeting;

// Defining linked data head
meeting *head = NULL;
int lineNum = 0;

// Declaring Functions
void readFile(FILE *);
void duplicate();
void delete (meeting *);
void sort(char);
int digit(int);
int maxLen(int);
void printBar(int, int, char *, int, int);
void printGraph(char, int, int, char);
int max(char);
int reverse();
int sum(char, int);

int main(int argc, char **argv)
{
	// Declaring variables
	char fileName[50],
		type = 'm',	  // set defalt type to meetings
		scaled = 'n'; // set defalt to not scaled

	int tPartici = 0,
		tTime = 0,
		tMeetings = 0,
		meetCount = 0,
		total,
		lines = 10; // set defalt lines to 10

	// check are thre any command line arguments
	if (argc > 1)
	{
		// Recognizing file from the arguments
		for (int i = 1; i < argc; i++)
		{
			if ((strlen(argv[i]) > 4) && (strcmp(&argv[i][0], "--scaled") != 0))
			{

				// Getting address to last 4 characters
				char *ext = &argv[i][strlen(argv[i]) - 4];

				if (strcmp(ext, ".csv") == 0)
				{ // If argument ends in .csv recognized as file name
					strcpy(fileName, argv[i]);

					// Getting data from file
					FILE *meetingData = fopen(fileName, "r");

					if (meetingData == NULL)
					{ // If there is no file in this name
						printf("Cannot open one or more given data file\n");
						return 0;
					}
					else
					{
						readFile(meetingData); // Reading the file
					}
				}

				else if (strcmp(&argv[i][0], "--") != 0)
				{ // If there is not argument with .csv
					printf("Only .csv files should be given as inputs\n");
					return 0;
				}
			}
		}

		duplicate();		 // Check and remove duplicate items
		lineNum = reverse(); // make list in reverce and getting number of elements

		// Getting sum of the parameters
		meeting *current = head;
		while (current != NULL)
		{

			tPartici += current->student.partici;
			tTime += current->student.time;
			tMeetings += current->student.meetingCount;
			meetCount++;

			current = current->next;
		}

		total = tMeetings; // Setting default value
		for (int i = 1; i < argc; i++)
		{
			// Checking is it an option or not
			if (argv[i][0] == '-')
			{

				// Checking the type of graph
				if (argv[i][1] == 'm')
				{
					type = 'm';
					total = tMeetings;
				}
				else if (argv[i][1] == 'p')
				{
					type = 'p';
					total = tPartici;
				}
				else if (argv[i][1] == 't')
				{
					type = 't';
					total = tTime;
				}
				/*else{
					printf("Invalid option [%s]\nusage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[i]);
					return 0;
				}*/

				// Checking number of lines
				if (argv[i][1] == 'l')
				{
					if (isdigit(*argv[i + 1]) > 0)
					{ // If argument after '-l' is integer
						lines = atoi(argv[i + 1]);
					}
					else
					{
						printf("Invalid options for [-l]\nusage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
						return 0;
					}
				}
				/*else{
                                         printf("Invalid option [%s]\nusage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[i]);
					 return 0;
				}*/
			}
		}

		// Checking scaaled argument
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(&argv[i][0], "--scaled") == 0)
			{
				scaled = 's';
			}
		}
	}

	// If there are no any commands,
	else
	{
		printf("No input files were given\nusage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
		return 0;
	}

	// Printting the graph
	printGraph(type, total, lines, scaled);
	return 0;
}

////// This function read and store the information from file
void readFile(FILE *dataFile)
{
	char sentence[100];
	char *token1, *token2;

	// Reads data line by line
	while (fscanf(dataFile, "%s", sentence) != EOF)
	{
		int column = 0;
		meeting *new = (meeting *)malloc(sizeof(meeting));

		// splitting the sentence
		token1 = strtok(sentence, ",");

		while (column != 3)
		{ // reading each 3 columns
			if (column == 0)
			{
				strcpy(new->student.name, token1);
			}
			else if (column == 1)
			{
				new->student.partici = atoi(token1);
			}
			else if (column == 2)
			{
				// Getting time

				token2 = strtok(token1, ":");

				long int hour = atoi(token2);
				token2 = strtok(NULL, ":");
				long int min = atoi(token2);
				token2 = strtok(NULL, ":");

				new->student.time = hour * 60 + min;
			}

			token1 = strtok(NULL, ",");
			column++;
		}

		// Adding data to head of the lined list
		new->next = head;
		head = new;
	}

	// Closing the file
	fclose(dataFile);
}

////// This function removes the duplicate items in list
void duplicate()
{
	meeting *element = head,
			*temp = NULL,
			*duplicate = NULL;

	// there is no list
	if (element == NULL)
	{
		return;
	}

	else
	{
		// Pick an element one by one
		while (element != NULL)
		{

			temp = element;
			element->student.meetingCount = 1; // Set initial to one

			// Now comparing each elements in the list
			while (temp->next != NULL)
			{
				if (strcmp(element->student.name, temp->next->student.name) == 0)
				{
					element->student.partici += temp->next->student.partici;
					element->student.time += temp->next->student.time;
					element->student.meetingCount++;

					// When duplicate occurs change previous next to after next and free duplicate
					duplicate = temp->next;
					temp->next = temp->next->next;
					free(duplicate);
				}
				else
				{
					temp = temp->next;
				}
			}
			element = element->next;
		}
	}
}

////// This function sorts items by its size
void sort(char sortBy)
{
	meeting *element = head,
			*temp = NULL;
	data store;
	int done = 1;

	if (element == NULL)
	{
		return;
	}
	else
	{
		// sorting elements using bubble sort
		while (done)
		{

			done = 0; // If there is any swaps checkk again and again
			element = head;

			// Comparing each elements in the list
			while (element->next != NULL)
			{
				int check;
				temp = element->next;

				if (sortBy == 'm')
				{ // Sorting according to number of meetings
					check = (element->student.meetingCount < temp->student.meetingCount);
				}
				else if (sortBy == 'p')
				{ // sorting according to number of participants
					check = (element->student.partici < temp->student.partici);
				}
				else if (sortBy == 't')
				{ // sorting according to meeting time
					check = (element->student.time < temp->student.time);
				}

				if (check)
				{ // swaping elements
					done = 1;
					store = element->student;
					element->student = temp->student;
					temp->student = store;
				}

				element = element->next;
			}
		}
	}
}

////// This Functionn gives number of digits in integer
int digit(int n)
{
	int digNum = 0;

	while (n != 0)
	{
		n = n / 10;
		digNum++;
	}

	return digNum;
}

////// This function gives maximum length of the name
int maxLen(int lines)
{
	meeting *element = head;
	int maxLength = 0;
	int count = 0;

	while (count != lines)
	{
		// cheking longest name form selcted number of lines
		if (strlen(element->student.name) > maxLength)
		{
			maxLength = strlen(element->student.name);
		}
		element = element->next;
		count++;
	}

	return maxLength;
}

// This function prints one ba in the graph
void printBar(int num, int total, char name[50], int scale, int charlen)
{
	int persentage = ((float)num) * (scale / (float)total);

	// Print the first line
	for (int i = 0; i < charlen + 1; i++)
	{
		printf(" ");
	}
	printf("\u2502");
	for (int i = 0; i < persentage; i++)
	{
		printf("\u2591");
	}
	printf("\n");

	// Printing the second line with name and number
	printf(" %s", name);
	for (int i = 0; i < (charlen - strlen(name)); i++)
	{
		printf(" ");
	}
	printf("\u2502");
	for (int i = 0; i < persentage; i++)
	{
		printf("\u2591");
	}
	printf("%d\n", num);

	// Printing 3rd line
	for (int i = 0; i < charlen + 1; i++)
	{
		printf(" ");
	}
	printf("\u2502");
	for (int i = 0; i < persentage; i++)
	{
		printf("\u2591");
	}
	printf("\n");
}

// This function prints the graph
void printGraph(char mode, int total, int lines, char scaled)
{
	int maxLength;
	int scale;

	meeting *element = head;

	if (lines > lineNum)
	{
		lines = lineNum;
	}

	printf("\n");

	// Printing graph for number of meetings
	if (mode == 'm')
	{
		sort('m');
		maxLength = maxLen(lines) + 1; // Getting Longest name's char number
		scale = 80 - maxLength - 3 - digit(max('m'));

		// Checking mode is scaled or not
		if (scaled == 's')
		{
			total = max('m');
		}

		// Printing Bars
		for (int i = 0; i < lines; i++)
		{
			printBar(element->student.meetingCount, total, element->student.name, scale, maxLength);

			// Printing line
			for (int i = 0; i < maxLength + 1; i++)
			{
				printf(" ");
			}
			printf("\u2502\n");

			element = element->next;
		}
	}

	// Printing graph for time duration
	else if (mode == 't')
	{
		sort('t');
		maxLength = maxLen(lines) + 1; // Getting Longest name's char number
		scale = 80 - (maxLength + 3) - digit(max('m'));

		// Checking mode is scaled or not
		if (scaled == 's')
		{
			total = max('t');
		}

		// Printing bars
		for (int i = 0; i < lines; i++)
		{
			printBar(element->student.time, total, element->student.name, scale, maxLength);

			// Printing line
			for (int i = 0; i < maxLength + 1; i++)
			{
				printf(" ");
			}
			printf("\u2502\n");

			element = element->next;
		}
	}

	// Printing graph for number of participants
	else if (mode == 'p')
	{
		sort('p');
		maxLength = maxLen(lines) + 1; // Getting Longest name's char number
		scale = 80 - (maxLength + 3) - digit(max('m'));

		// Checking mode is scaled or not
		if (scaled == 's')
		{
			total = max('p');
		}

		for (int i = 0; i < lines; i++)
		{
			printBar(element->student.partici, total, element->student.name, scale, maxLength);

			// Printing line
			for (int i = 0; i < maxLength + 1; i++)
			{
				printf(" ");
			}
			printf("\u2502\n");

			element = element->next;
		}
	}

	// printing the corner of the graph
	for (int i = 0; i < maxLength + 1; i++)
	{
		printf(" ");
	}
	printf("\u2514");
	// Printing the bottom line
	for (int i = 0; i < (78 - maxLength); i++)
	{
		printf("\u2500");
	}
	printf("\n");
}

// This gives maximum number. this should add after the sorting
int max(char type)
{

	if (type == 'm')
	{
		return head->student.meetingCount;
	}
	else if (type == 't')
	{
		return head->student.time;
	}
	else if (type == 'p')
	{
		return head->student.partici;
	}
	else
	{
		return 0;
	}
}

// Resversing the linked list
int reverse()
{

	int count = 0;
	meeting *prevN = NULL,
			*currentN = head,
			*nextN = NULL;

	while (currentN != NULL)
	{
		// store next
		nextN = currentN->next;
		// reverse the current next
		currentN->next = prevN;
		// move pointer
		prevN = currentN;
		currentN = nextN;
		count++;
	}
	head = prevN;
	return count;
}
