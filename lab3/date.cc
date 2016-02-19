#include <ctime>  // time and localtime
#include "date.h"
#include <iostream>
#include <regex>


using namespace std;


int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


template<typename T>
string toString(T obj){
	stringstream ss;
	ss << obj;
  string myString = ss.str();
	return myString;
}


template <typename T>
T string_cast (string s) {
	T obj;
	stringstream convert(s);
	if (!convert){
		throw std::invalid_argument(s);
	}
	convert >> obj;
	return obj;
}



int main(){
	Date date;
	cout << toString(date);
	int ass = 12333;
	stringstream myDate("2016-23-11");
	myDate >> date;
	cout << toString(date);

	//date >> "1023-";

	try {
		int i = string_cast<int>("123");
		cout << std::endl;
		cout << i;
		double d = string_cast<double>("12.34");
		cout << std::endl;
		cout << d;
		Date date = string_cast<Date>("2015-01-10");
		cout << std::endl;
		cout << date;
		date = string_cast<Date>("what what");
	} catch (std::invalid_argument& e) {
		cout << "Error: " << e.what() << endl;
	}

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


istream& Date::parseDate(std::istream& is)
{
	std::string in(std::istreambuf_iterator<char>(is), {});
//	int y, d, m; char c1, c2;
//	is >> y >> c1 >> m >> c2 >> d;


	int currentPos = 0;
	size_t target = in.find("-");
	if (target == in.size()-1){
		is.setstate(ios::failbit);
		return is;
	}
	year = stoi(in.substr(currentPos, target));
	currentPos = target+1;
	target = in.find("-", target+1);
	if (target == in.size()-1){
		is.setstate(ios::failbit);
		return is;
	}
	month = stoi(in.substr(currentPos, target));
	currentPos = target+1;
	target = in.find("-", target+1);
	if (target == in.size()-1){
		is.setstate(ios::failbit);
		return is;
	}
	day = stoi(in.substr(currentPos, target));


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
		out << to_string(year) << "-" << to_string(month) << "-" << to_string(day);
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
