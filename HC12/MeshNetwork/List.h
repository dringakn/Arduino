/*
Name:		List.h
Created:	03 Nov 2018
Author:		Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
License:	This Library is licensed under a GPLv3 License
Description:
*/

#ifndef _LISTCLASS_h
#define _LISTCLASS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

struct element
{
	unsigned char id;
	unsigned char hops;
};

class ListClass
{
private:
	unsigned char listSize;

public:
	unsigned char counts;
	struct element *list;
	void init(struct element* lst, unsigned char size);
	boolean add(struct element item);
	boolean remove(struct element item);
	unsigned char find(struct element item);
	void sort(void);
	void print(void);
};

#endif

