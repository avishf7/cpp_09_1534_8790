/*
File: funcs.h
Description:
Course: 150018 C++ Workshop, Exercise 9, Question 2
Author: Dan Zilberstein
Students: eli ialoz 311201354
		& avishay farkash 205918790
*/
#pragma once

//swap by refrence any two values
template <typename T>
void mySwap(T& L, T& R)
{
	T temp;

	if (sizeof(T) > 4)
	{
		memmove(&temp, &L, sizeof(T));
		memmove(&L, &R, sizeof(T));
		memmove(&R, &temp, sizeof(T));
	}
	else
	{
		temp = L;
		L = R;
		R = temp;
	}
}

//return the big value between any two numbers
template <typename T>
int max(T num1, T num2)
{
	if (num1 > num2)
		return num1;
	return num2;
}