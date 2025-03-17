// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
	@file XMLParser.cpp */

#include <string>
#include "XMLParser.hpp"

XMLParser::XMLParser()
{
	elementNameBag = std::make_shared<Bag<std::string>>();
	parseStack = std::make_shared<Stack<std::string>>();
	tokened_input = false;
	parsed_input = false;
} // end default constructor

bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	tokenizedInputVector.clear();
	size_t index = 0;
	std::string my_string = "";
	size_t space_remove = 0;
	for (space_remove = 0; space_remove < inputString.length(); space_remove++)
	{
		if (std::isspace(inputString[space_remove]))
		{
			// find space
		}
		else
		{
			break;
		}
	}
	my_string = inputString.substr(space_remove);
	if (my_string.empty())
	{
		return false;
	}
	size_t delimiters = 0;
	for (char my_char : my_string)
	{
		if (my_char == '<' || my_char == '>')
		{
			delimiters++;
		}
	}
	if (delimiters % 2)
	{
		return false;
	}
	while (index < my_string.length())
	{
		TokenStruct my_token;
		if (std::isspace(my_string[index]))
		{
			index++;
		}
		else if (my_string[index] == '<')
		{
			size_t end_delimiter = my_string.find('>', index);
			if (end_delimiter == std::string::npos)
			{
				return false;
			}
			std::string my_tag = my_string.substr(index, (end_delimiter + 1) - index);
			size_t length = my_tag.length();
			bool start_slash = my_tag[1] == '/';
			bool end_slash = my_tag[length - 2] == '/';
			bool start_question = my_tag[1] == '?';
			bool end_question = my_tag[length - 2] == '?';
			if (!start_slash && !end_slash && !start_question && !end_question)
			{
				my_token.tokenType = START_TAG;
			}
			else if (start_slash && !end_slash && !start_question && !end_question)
			{
				my_token.tokenType = END_TAG;
			}
			else if (!start_slash && end_slash && !start_question && !end_question)
			{
				my_token.tokenType = EMPTY_TAG;
			}
			else if (!start_slash && !end_slash && start_question && end_question)
			{
				my_token.tokenType = DECLARATION;
				my_token.tokenString = my_tag.substr(2, my_tag.length() - 4);
				tokenizedInputVector.push_back(my_token);
				index += my_tag.length();
				continue;
			}
			else
			{
				return false;
			}

			std::string my_name = "";
			if (my_tag[0] == '<' && my_tag[length - 1] == '>')
			{
				my_name = my_tag.substr(1, length - 2);
			}
			if (my_tag[1] == '/')
			{
				my_name = my_name.substr(1, my_name.length() - 1);
			}
			else if (my_tag[length - 2] == '/')
			{
				my_name = my_name.substr(0, my_name.length() - 1);
			}
			size_t temp = my_name.length();
			for (size_t space_index = 0; space_index < temp; space_index++)
			{
				if (std::isspace(my_name[space_index]))
				{
					my_name = my_name.substr(0, space_index);
					break;
				}
			}

			std::string invalid_characters = "!\"#$%&'()*+,-/;<=?@[\\]^`{|}~ ";
			std::string invalid_start = "-.0123456789";
			if (my_name.empty())
			{
				return false;
			}
			for (char my_char : invalid_characters)
			{
				if (my_name.find(my_char) != std::string::npos)
				{
					return false;
				}
			}
			for (char my_char : invalid_start)
			{
				if (my_name[0] == my_char)
				{
					return false;
				}
			}
			my_token.tokenString = my_name;
			tokenizedInputVector.push_back(my_token);
			index += my_tag.length();
		}
		else
		{
			my_token.tokenType = CONTENT;
			size_t next_delimiter = my_string.find('<', index);
			if (next_delimiter == string::npos)
			{
				next_delimiter = my_string.length();
			}
			size_t space_index = index;
			for (space_index; space_index < next_delimiter; space_index++)
			{
				if (std::isspace(my_string[space_index]))
				{
					break;
				}
			}
			my_token.tokenString = my_string.substr(index, space_index - index);
			for (char my_char : my_token.tokenString)
			{
				if (my_char == '<' || my_char == '>')
				{
					return false;
				}
			}
			size_t content_index = next_delimiter;
			index = next_delimiter;
			tokenizedInputVector.push_back(my_token);
		}
	}
	tokened_input = true;
	return true;
} // end

bool XMLParser::parseTokenizedInput()
{
	bool end_of_document = false;
	parseStack->clear();
	elementNameBag->clear();
	if (!tokened_input)
	{
		return false;
	}
	for (size_t i = 0; i < tokenizedInputVector.size(); i++)
	{
		if (end_of_document)
		{
			return false;
		}
		TokenStruct my_token = tokenizedInputVector[i];
		if (my_token.tokenType == CONTENT && parseStack->isEmpty())
		{
			return false;
		}
		else if (my_token.tokenType == START_TAG)
		{
			parseStack->push(my_token.tokenString);
			elementNameBag->add(my_token.tokenString);
		}
		else if (my_token.tokenType == END_TAG)
		{
			if (parseStack->isEmpty() || parseStack->peek() != my_token.tokenString)
			{
				return false;
			}
			parseStack->pop();
		}
		else if (my_token.tokenType == EMPTY_TAG)
		{
			elementNameBag->add(my_token.tokenString);
		}
		else if (my_token.tokenType == DECLARATION)
		{
			if (!parseStack->isEmpty() && my_token.tokenString.substr(0, 3) == "xml")
			{
				return false;
			}
			continue;
		}
		if (parseStack->isEmpty())
		{
			end_of_document = true;
		}
	}

	parsed_input = parseStack->isEmpty();

	return parsed_input;
}

void XMLParser::clear()
{
	elementNameBag->clear();
	parseStack->clear();
	tokenizedInputVector.clear();
	tokened_input = false;
	parsed_input = false;
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &inputString) const
{
	if (tokened_input && parsed_input)
	{
		return elementNameBag->contains(inputString);
	}
	throw std::logic_error("did not call tokenizedInputString and parseTokenizedInput");
}

int XMLParser::frequencyElementName(const std::string &inputString) const
{
	{
		if (tokened_input && parsed_input)
		{
			return elementNameBag->getFrequencyOf(inputString);
		}
		throw std::logic_error("did not call tokenizedInputString and parseTokenizedInput");
		return -1;
	}
