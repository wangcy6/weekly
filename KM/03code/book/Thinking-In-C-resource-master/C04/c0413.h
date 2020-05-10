#ifndef _VIDEO_H
#define _VIDEO_H
#pragma once
#include <string>
class CVideo{
int m_ID;
int m_Price;
int m_Size;
bool m_Rent;
int m_RentalCosts;
double m_RentDate;
double m_ReturnDate;
std::string m_Name;
	public:
void printf();
int getPrice();
int getID();
int getSize();
std::string getName();
void initialize(int id, int price,  int size, int rentDate,
			int returnDate, int retalCosts, std::string name);
int rentedMoney();
int rentalDays();
};

#endif//_VIDEO_H
