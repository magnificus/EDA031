#ifndef DATE_H
#define DATE_H

#include <iostream>


using namespace std;
class Date {
public:
	Date();                    // today's date
	Date(int y, int m, int d); // yyyy-mm-dd
	int getYear() const;       // get the year
	int getMonth() const;      // get the month
	int getDay() const;        // get the day
	void next();               // advance to next day
	void incrementYear();
	void incrementMonth();
	void incrementDay();

	std::ostream& printDate(std::ostream & out) const;
	std::istream& parseDate(std::istream & is) const;


	friend istream &operator>>(istream& is, const Date& date);
	friend ostream &operator<<(ostream& os, const Date& date);
	//ostream& operator<<(std::ostream& os);

private:
	int year;  // the year (four digits)
	int month; // the month (1-12)
	int day;   // the day (1-..)
	static int daysPerMonth[12]; // number of days in each month
};

ostream &operator<<(ostream& os, const Date& date)
{
    return date.printDate(os); //just one line!
}

istream &operator>>(istream& is, const Date& date)
{
    return date.parseDate(is); //just one line!
}

#endif
