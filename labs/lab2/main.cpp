#include "Time.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
int main () {
	int hour;
	std::cout << "give an hour:" << std::endl;
	std::cin >> hour;
	int min;
	std::cout << "give an minute:" << std::endl;
	std::cin >> min;
	int sec;
	std::cout << "give an second:"<< std::endl;
	std::cin >> sec;
	Time t1;
	Time t2;
	Time t3;

	t2.sethour(hour);
	t2.setmin(min);
	t2.setsec(sec);
	std::cout << "Enter t3 info:" << std::endl;

	int hour2;
	std::cout << "give an hour:" << std::endl;
	std::cin >> hour2;
	int min2;
	std::cout << "give an minute:" << std::endl;
	std::cin >> min2;
	int sec2;
	std::cout << "give an second:"<< std::endl;
	std::cin >> sec2;
	t3.sethour(hour2);
	t3.setmin(min2);
	t3.setsec(sec2);

	std::vector <Time> times;
	times.push_back(t2);
	times.push_back(t3);

	// std::cout << t1.gethour() << t1.getmin() << t1.getsec() << std::endl;
	// std::cout << t2.gethour() << t2.getmin() << t2.getsec() << std::endl;

	// t1.PrintAMPM();
	// t2.PrintAMPM();

	t2.changetimes(t3)
	t2.PrintAMPM();
	t3.PrintAMPM();
}