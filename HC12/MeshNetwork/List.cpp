/*
Name:		List.cpp
Created:	03 Nov 2018
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#include "List.h"

void ListClass::init(struct element* lst, unsigned char size)
{
	listSize = size;
	list = lst;
	counts = 0;
	for (size_t i = 0; i < listSize; i++)
	{
		list[i].id = list[i].hops = 255;
	}
}

boolean ListClass::add(struct element item)
{
	if (counts < listSize)
	{
		if (find(item) == 255)
		{
			// The item already doesn't exist based on id check, therefore, add it to the existing list and sort the list based upon hops count
			list[counts].id = item.id;
			list[counts].hops = item.hops;
			counts++;
			sort();
			return true;
		}
	}
	return false;
}

boolean ListClass::remove(struct element item)
{
	unsigned char id = find(item);
	if (id != 255)
	{
		// The item exist in the list based upon id check, therefore, remove the items
		for (size_t i = id; i < counts - 1; i++)
		{
			list[i].id = list[i + 1].id;
			list[i].hops = list[i + 1].hops;
		}
		list[counts-1].id = list[counts-1].hops = 255;	// Reset the empty space
		counts--;
		return true;
	}
	return false;
}

unsigned char ListClass::find(struct element item)
{
	for (size_t i = 0; i < counts; i++)
	{
		if (list[i].id == item.id)
		{
			return i;
		}
	}
	return 255;
}

void ListClass::sort(void)
{
	for (size_t i = 0; i < counts; i++)
	{
		struct element temp;
		for (size_t j = i; j < counts-1; j++)
		{
			if (list[j].hops > list[j+1].hops)
			{
				// Sort in ascending order based on hops count
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
			else if (list[j].hops == list[j + 1].hops)
			{

				if (list[j].id > list[j + 1].id)
				{
					// Sort in ascending order based on id
					temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
				}
			}
		}
	}
}

void ListClass::print(void)
{
	for (size_t i = 0; i < counts; i++)
	{
		Serial.print(list[i].id); 
		Serial.print(','); 
		Serial.println(list[i].hops);
	}
}