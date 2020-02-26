#include <iostream>
#include <cassert>
#include <limits>
#include <initializer_list>

void clearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

class IntArray
{
private:
	int m_length{ 0 };
	int* m_array{ nullptr };

public:
	 
	IntArray() {}

	IntArray(int length) : m_length{ length }
	{
		// If length is not >0 the error message will be displayed
		assert(length > 0 && "Length must be a positive integer");

		// Dynamically allocate the array using new[]
		m_array = new int[m_length] {};
	}

	// Constructor for list initialisation
	// Uses the other constructor to allocate memory, to reduce redundant code
	IntArray(const std::initializer_list<int>& list) :
		IntArray(static_cast<int>(list.size())) 
	{
		int count{ 0 };
		for (auto& element : list)
		{
			m_array[count] = element;
			count++;
		}
	}

	// Deep copy to avoid problems with copying IntArray objects and delete[]
	IntArray(const IntArray& array) : m_length{ array.m_length }
	{
		m_array = new int[m_length];

		for (int count{ 0 }; count < array.m_length; count++)
			m_array[count] = array.m_array[count];
	}

	~IntArray()
	{
		delete[] m_array;
	}

	// Overload << for IntArray objects so that std::cout will print every element of the array, separated by spaces
	friend std::ostream& operator<<(std::ostream& out, const IntArray& array)
	{
		for (int count{ 0 }; count < array.m_length; count++)
			out << array.m_array[count] << ' ';

		// Return out so output commands can be chained as usual
		return out;
	}

	int& operator[] (const int index)
	{
		assert(index >= 0);
		assert(index < m_length);
		return m_array[index];
	}

	// Assignment operator that does a deep copy
	IntArray& operator= (const IntArray& array)
	{
		if (this == &array)
			return *this;
		// Delete array in case it already exists
		delete[] m_array;

		m_length = array.m_length;

		m_array = new int[m_length];

		for (int count{ 0 }; count < array.m_length; count++)
			m_array[count] = array.m_array[count];

		return *this;
	}

	void fillArray()
	{
		for (int element{}; element < m_length; element++)
		{
			m_array[element] = changeElementValue(element);
		}
	}

	void chooseElement()
	{
		std::cout << "\nWhat element would you like to change? ";
		int element{};
		std::cin >> element;

		// ensure user enters a valid number
		while (!std::cin || element < 0 || element >= m_length)
		{
			// if a character was entered first
			if (!std::cin)
				std::cout << "\nPlease enter an integer: ";
			// if an invalid number was entered
			if (element < 0 || element >= m_length)
				std::cout << "\nInteger must be between 0 and " << m_length - 1 << ": ";

			clearInput();
			std::cin >> element;
		}

		// In case user entered an integer followed by invalid characters (eg a float)
		// extract and discard the invalid characters
		clearInput();

		m_array[element] = changeElementValue(element);
	}

	int changeElementValue(const int element)
	{
		std::cout << "\nEnter an integer to place in element " << element << ": ";
		int value{};
		std::cin >> value;

		// If user enters a character, extract and discard everything in stream and ask for an integer
		while (!std::cin)
		{
			std::cout << "\nPlease enter an integer: ";
			clearInput();
			std::cin >> value;
		}
		// in case user entered an integer followed by invalid characters (eg a float)
		// extract and discard the invalid characters
		clearInput();

		return value;
	}
};


int main()
{
	std::cout << "Choose the length of arrayA: ";
	int length{};
	std::cin >> length;
	clearInput();

	IntArray arrayA(length);

	arrayA.fillArray();

	std::cout << "\narrayA: " << arrayA << '\n';

	IntArray arrayB{};
	std::cout << "\nCopying arrayA into a new array, arrayB.\n";
	arrayB = arrayA;

	std::cout << "\nChange two elements in arrayA.";
	arrayA.chooseElement();
	arrayA.chooseElement();

	std::cout << "\nCreating arrayC using list initialisation.\n";

	IntArray arrayC{ 9,8,7,6,5,4 };

	std::cout << "\nThe value in element 0 of arrayA is " << arrayA[0];
	std::cout << "\narrayA: " << arrayA;
	std::cout << "\narrayB: " << arrayB;
	std::cout << "\narrayC: " << arrayC << '\n';
	
	return 0;
} 