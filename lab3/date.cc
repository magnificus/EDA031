#include <ctime>  // time and localtime
#include "date.h"
#include <iostream>
#include <regex>


using namespace std;


int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(){
	Date* date = new Date();
	//istream tempdate;
	//tempdate << "2015-32-22";
	//date << tempdate;
	//ostream s;
	//date >> s;
	//date << tempdate;
	cout << *date;
	//delete date;
}

Date::Date() {
	time_t timer = time(0); // time in seconds since 1970-01-01
	tm* locTime = localtime(&timer); // broken-down time
	year = 1900 + locTime->tm_year;
	month = 1 + locTime->tm_mon;
	day = locTime->tm_mday;
}

Date::Date(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}

int Date::getYear() const {
	return year;
}

int Date::getMonth() const {
	return month;
}

int Date::getDay() const {
	return day;
}

istream& Date::parseDate(std::istream& is) const
{
	std::string in(std::istreambuf_iterator<char>(is), {});

	int currentPos = 0;
	int target = in.find("-");
	day = stoi(in.substr(currentPos, target));
	currentPos = target+1;
	target = in.find("-", target+1);
	month = stoi(in.substr(currentPos, target));
	currentPos = target+1;
	target = in.find("-", target+1);
	year = stoi(in.substr(currentPos, target));



  return is;
}


//ostream& Date::operator<<(std::ostream& os){
//
//	cout << "day: " << day << " month:" << month << " year: " << year;
//	os << to_string(year) << "-" << to_string(month) << "-" << to_string(day);
	//os << "asd";
//	return os;
//}



std::ostream& Date::printDate(std::ostream & out) const
{
		//cout << "day: " << day << " month:" << month << " year: " << year;
		out << to_string(year) << "-" << to_string(month) << "-" << to_string(day);
		//out << "asd";
		//cout << "fuck allM";
		return out;
}


void Date::incrementYear(){
	year++;
}



void Date::incrementMonth(){
	if (month == 12){
		incrementYear();
		month = 1;
	} else{
		month++;
	}
}
void Date::incrementDay(){
	if (daysPerMonth[month-1] == day){
		incrementMonth();
		day = 1;
	} else{
		day++;
	}
}
void Date::next() {
	incrementDay();
}
