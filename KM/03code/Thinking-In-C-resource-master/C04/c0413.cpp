#include <iostream>
#include "c0413.h"

using namespace std;

void CVideo::printf()
{
	cout<<"The Video`s name is "<<m_Name
		<<"\nID = "<<m_ID
		<<"\nprice = "<<m_Price
		<<"\nsize  = "<<m_Size
		<<"\nRentalCoasts is"<<m_RentalCosts
		<<"\nIs rented?"<<(m_Rent?"Yes.":"NO");
}

int CVideo::getPrice()
{
	return m_Price;
}
int CVideo::getID()
{
	return m_ID;
}
int CVideo::getSize()
{
	return m_Size;
}
std::string CVideo::getName()
{
	return m_Name;
}

void CVideo::initialize(int id, int price, int size, int rentDate,
			int returnDate, int rentalCosts, std::string name)
{
	m_ID = id;
	m_Price  = price;
	m_Size = size;
	m_RentDate = rentDate;
	m_ReturnDate = returnDate;
	m_RentalCosts = rentalCosts;
	m_Name = name;
}
int CVideo::rentedMoney()
{
	return rentalDays() * m_RentalCosts;
}
int CVideo::rentalDays()
{
	return m_RentDate - m_ReturnDate;
}
