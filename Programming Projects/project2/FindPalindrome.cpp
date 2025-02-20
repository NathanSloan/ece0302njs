#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string &value)
{
	for (int i = 0; i < value.size(); i++)
	{
		value[i] = tolower(value[i]);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
												  candidateStringVector,
											  vector<string> currentStringVector)
{
	if (!cutTest2(candidateStringVector, currentStringVector))
	{
		return;
	}
	if (currentStringVector.empty())
	{
		std::string stringTemp = "";
		for (std::string word : candidateStringVector)
		{
			convertToLowerCase(word);
			stringTemp += word;
		}
		if (isPalindrome(stringTemp))
		{
			savedPalindromes.push_back(candidateStringVector);
		}
		return;
	}
	else
	{
		for (int i = 0; i < currentStringVector.size(); i++)
		{
			candidateStringVector.push_back(currentStringVector.back());
			currentStringVector.pop_back();

			recursiveFindPalindromes(candidateStringVector, currentStringVector);

			currentStringVector.insert(currentStringVector.begin(), candidateStringVector.back());
			candidateStringVector.pop_back();
		}
	}
	return;
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i = 0; i < stringLength / 2; i++)
	{
		if (currentString[i] != currentString[stringLength - i - 1])
		{
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
}

FindPalindrome::~FindPalindrome()
{
	savedPalindromes.clear();
	savedWords.clear();
}

int FindPalindrome::number() const
{
	return toVector().size();
}

void FindPalindrome::clear()
{
	savedPalindromes.clear();
	savedWords.clear();
}

bool FindPalindrome::cutTest1(const vector<string> &stringVector)
{
	if (stringVector.size() == 0)
		return true;
	// tracks each letter (false = even, true = odd)
	bool seen[26] = {false};
	for (std::string word : stringVector)
	{
		convertToLowerCase(word);
		for (char letter : word)
		{
			seen[letter - 'a'] = !seen[letter - 'a'];
		}
	}
	int check = 0;
	for (int x = 0; x < 26; x++)
	{
		if (seen[x])
			check++;
	}
	return check <= 1;
}

bool FindPalindrome::cutTest2(const vector<string> &stringVector1,
							  const vector<string> &stringVector2)
{
	// convert vectors to strings
	std::string string1 = "", string2 = "";
	for (std::string word : stringVector1)
	{
		convertToLowerCase(word);
		string1 += word;
	}
	for (std::string word : stringVector2)
	{
		convertToLowerCase(word);
		string2 += word;
	}

	// ensure string2 is the smaller string
	if (string1.size() > string2.size())
	{
		std::swap(string1, string2);
	}
	int occ1[26] = {0};
	int occ2[26] = {0};
	for (char letter : string1)
	{
		occ1[letter - 'a'] += 1;
	}
	for (char letter : string2)
	{
		occ2[letter - 'a'] += 1;
	}
	for (int x = 0; x < 26; x++)
	{
		if (occ2[x] < occ1[x])
			return false;
	}
	return true;
}

bool FindPalindrome::add(const string &value)
{
	if (value.empty())
	{
		return false;
	}
	for (char letter : value)
	{
		if (!std::isalpha(letter))
		{
			return false;
		}
	}
	std::string word = value;
	convertToLowerCase(word);
	for (std::string savedWord : savedWords)
	{
		convertToLowerCase(savedWord);
		if (savedWord == word)
			return false;
	}
	savedWords.push_back(value);
	savedPalindromes.clear();
	std::vector<std::string> temp;
	if (cutTest1(savedWords))
	{
		recursiveFindPalindromes(temp, savedWords);
	}
	return true;
}

bool FindPalindrome::add(const vector<string> &stringVector)
{
	if (stringVector.empty())
		return false;
	for (std::string word : stringVector)
	{
		if (word.empty())
			return false;
		for (char letter : word)
		{
			if (!std::isalpha(letter)) // check to make sure character is contained in the alphabet
				return false;
		}
		convertToLowerCase(word);
		for (std::string savedWord : savedWords)
		{
			convertToLowerCase(savedWord);
			if (savedWord == word)
				return false;
		}
	}

	for (std::string words : stringVector)
	{
		savedWords.push_back(words); // add the string, after checking each character is contained in the alphabet
	}
	savedPalindromes.clear();
	std::vector<std::string> temp;
	if (cutTest1(savedWords)) // only needs to be called initially, as if it fails, not point in finding pallindromes
	{
		recursiveFindPalindromes(temp, savedWords);
	}
	return true;
}

vector<vector<string>> FindPalindrome::toVector() const
{
	return savedPalindromes;
}
