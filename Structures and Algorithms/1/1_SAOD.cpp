#include <iostream>
#include <random>
#include <string>

int getRandom()
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution value(1, 10000);
	return value(mt);
}

struct Stack
{//it has the value that becomes the top of the stack
	int top{}; //the value in the one (this) node/struct
	Stack* next{}; //pointer to the next struct stack
}; 

Stack* m_stackPointer;
Stack* m_auxiliaryStackPointer; //pointer to the head of the stack - to the last element - to the top of the stack

void emptyStackInitialization()
{
	m_stackPointer = nullptr;
	m_auxiliaryStackPointer = nullptr;
}

bool isEmpty()
{
	if (m_stackPointer == nullptr)
	{
		return true;
	}
	else
		return false;
}

bool isAuxiliaryEmpty()
{
	if (m_auxiliaryStackPointer == nullptr)
	{
		return true;
	}
	else
		return false;
}

Stack* push(Stack* stackPointer, int newTop)
{
	Stack* current = new Stack; //dynamically allocate new node/element
	current->top = newTop; //initialization of a new value
	current->next = stackPointer; //point to the previous node/element (we need to archieve the element before the last)
	stackPointer = current; //making the new element the last element of the stack
	return stackPointer;
}

void pop()
{
	//we need to delete current
	Stack* current = m_stackPointer; //making from the last node/element/head/or tail? of the stack the "current"
	//bc we cannot delete m_stackPointer
	m_stackPointer = m_stackPointer->next; //so we need m_stackPointer to be the element before the last
	//we can acsess it using next, bc the last node/tail points to the previous node
	delete current;  //aand finally we delete current! good job
}

void show(Stack* stackPointer) 
{
	if (stackPointer != nullptr)
	{
		std::cout << "\n";
		Stack* current;
		current = stackPointer;
		for (int i{ 1 }; current != nullptr; i++)
		{
			std::cout << i << ". " << current->top << '\n';
			current = current->next;
		}
		std::cout << "\n";
	}
	else
	{
		std::cout << "Stack is empty.\n\n";
	}
}

int getNumber()
{
	while (true)
	{
		int num;
		std::cin >> num;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Input error, you did not enter a number. Repeat the input: \n";
		}
		else if (static_cast<int>(num) != num)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "You entered a non-natural number. Repeat the input: \n ";
		}
		else if (num <= 0)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "You entered a non-positive number or zero. Repeat the input: \n ";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return num;
		}
	}
}

void pushManyRandomValues()
{
	std::cout << "Enter a number of values to be entered into the stack: ";
	int number{ getNumber() };
	for (int i{ 0 }; i < number; i++)
	{
		m_stackPointer = push(m_stackPointer, getRandom());
	}
	std::cout << "\n";
}

void moveToAuxiliaryStack() {
	Stack* current = m_stackPointer; //temp for the last element of stack
	m_stackPointer = m_stackPointer->next; //change the top of the main stack
	current->next = m_auxiliaryStackPointer; 
	m_auxiliaryStackPointer = current; //make from current the top of the aux stack
}

void getElementsFromAuxiliaryStack()
{
	Stack* current = m_auxiliaryStackPointer; //cuurent is the top from aux stack
	m_auxiliaryStackPointer = m_auxiliaryStackPointer->next; //change the top of aux stack to the previous
	current->next = m_stackPointer; //bond top with the previos
	m_stackPointer = current; //so make top of stack is the elem from aux
}

void MenuForChoices()
{
	std::cout << "What do you want to do?\n" <<
		"1) Check if the main stack is empty.\n" <<
		"2) Check if the auxiliary stack is empty.\n" <<
		"3) Add the element to the top of the main stack.\n" <<
		"4) Add several random elements to the top of the main stack.\n" <<
		"5) Delete the element from the top of the main stack.\n" <<
		"6) Show the main stack.\n" <<
		"7) Show the auxiliary stack.\n" <<
		"8) Exit.\n";
}

char getCase()
{
	while (true)
	{
		MenuForChoices(); //here the text
		std::cout << "Your choice is: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8")
		{
			return choice[0];
		}
		else
		{
			std::cout << "\nInput error! Repeat, please:\n";
		}
	}
}

char getOneOrTwo()
{
	while (true)
	{
		std::cout << "Your choice is: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2")
		{
			return choice[0];
		}
		else
		{
			std::cout << "\nInput error! Repeat, please:\n";
		}
	}
}

void addElementToMainStack()
{
	std::cout << "\nI have a question about the origin of the element:\n"
		<< "1. Really creating a new element.\n"
		<< "2. Selecting it from the top of the auxiliary stack.\n";

	switch (getOneOrTwo())
	{
		case '1':
			std::cout << "Please, enter a number: ";
			m_stackPointer = push(m_stackPointer, getNumber());
			std::cout << "\n";
			break;
		case '2':
			if (isAuxiliaryEmpty())
			{
				std::cout << "\nOh, it seems like the auxiliary stack is empty :(\n\n";
			}
			else
			{
				getElementsFromAuxiliaryStack();
			}
			break;

	}
}

void DeleteOrRemoveFromMainstack()
{
	switch (getOneOrTwo())
	{
	case '1':
		pop();
		break;
	case '2':
		moveToAuxiliaryStack();
		break;
	}
}

void deleteElement()
{
	if (isEmpty())
	{
		std::cerr << "\nThe main stack is empty, you cannot delete elements!\n\n";
	}
	else
	{
		std::cout << "\nWhat to do with the top element?\n"
			<< "1. Really delete with memory release.\n"
			<< "2. Include it at the top of the auxiliary stack.\n";

		DeleteOrRemoveFromMainstack();
	}
}

void checkMainStack()
{
	std::cout << '\n';
	if (isEmpty())
	{
		std::cout << "The main stack is empty!\n\n";
	}
	else
	{
		std::cout << "The main stack is NOT empty!\n\n";
	}
}

void checkAuxiliaryStack()
{
	std::cout << '\n';
	if (isAuxiliaryEmpty())
	{
		std::cout << "The auxiliary stack is empty!\n\n";
	}
	else
	{
		std::cout << "The auxiliary stack is NOT empty!\n\n";
	}
}

void menu()
{
	bool cycle{ true };
	while (cycle) {
		switch (getCase()) //here menu
		{
		case '1':
			checkMainStack();
			break;

		case '2':
			checkAuxiliaryStack();
			break;

		case '3':
			addElementToMainStack();
			break;

		case '4':
			pushManyRandomValues();
			break;

		case '5':
			deleteElement();
			break;

		case '6':
			std::cout << "\nThis is how the main stack looks like:\n";
			show(m_stackPointer);
			break;

		case '7':
			std::cout << "\nThis is how the auxiliary stack looks like:\n";
			show(m_auxiliaryStackPointer);
			break;

		case '8':
			cycle = false;
		}
	}
}

int main()
{
	emptyStackInitialization();
	menu();
	return 0;
}
