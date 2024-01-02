//###########################################################################
// Regex.cpp
// Text regular expression
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Regex.h"


/// @brief Constructor
Regex::Regex()
	:array(NULL)
{
}


/// @brief Deconstructor
Regex::~Regex()
{
	Clear();
}


/// @brief Split
/// @param s 
/// @param split 
/// @return 
Regex::String* Regex::Split(const char* s, const char split)
{
	const int32_t start_delimiter = -1;
	
	String** nextNode = &strings;
	int32_t startIndex = start_delimiter;
	int32_t recordBytes = 0;

    for (int32_t i = 0; ; i++)
	{
		if (split != s[i] && start_delimiter == startIndex)
		{
			startIndex = i;
		}
		else if ((split == s[i] && start_delimiter != startIndex) || '\0' == s[i])
		{
			recordBytes = i - startIndex;
			char* str = new char[recordBytes + 1]();
			
			if (NULL != str)
			{
				for (int32_t j = 0; j < recordBytes; j++)
				{
					str[j] = s[startIndex + j];
				}
				str[recordBytes] = '\0';

				*nextNode  = new String(str);
				nextNode   = &(*nextNode)->next;
				startIndex = start_delimiter;
			}
			else return NULL;
		}

		if ('\0' == s[i]) break;
	};

    return strings;
}


/// @brief Get item size
/// @return size
int Regex::Size()
{
	int size = 0;

	for (String* node = strings; NULL != node; node = node->next)
	{
		size++;
	}

	return size;
}


/// @brief Item to array
/// @return array
char** Regex::ToArray()
{
	int i = 0;
	
	array = new char*[Size()]();

	for (String* node = strings; NULL != node; node = node->next)
	{
		array[i++] = (char*)node->str;
	}

	return array;
}


/// @brief release memory
void Regex::Clear()
{
	String* node = strings;

	while (NULL != node)
	{
		String* next = node->next;
		delete[] node->str;
		delete[] node;
		node = next;
	}

	if (NULL != array) delete[] array;
}
