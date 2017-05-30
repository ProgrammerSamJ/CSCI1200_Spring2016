#include <iostream>
#include <iomanip>
#include "Time.h"

Time::Time() {
	hour = 0;
	min = 0;
	sec = 0;
}
Time::Time(uintptr_t ahour, uintptr_t amin, uintptr_t asec) {
	hour = ahour;
	min = amin;
	sec = asec;
}
 uintptr_t Time::gethour() const {
 	return hour;
 }

 uintptr_t Time::getmin() const {
 	return min;
 }

 uintptr_t Time::getsec() const {
 	return sec;
 }
 void Time::sethour(uintptr_t h) {
 	hour = h;
 }
 void Time::setmin(uintptr_t m) {
 	min = m;
 }
 void Time::setsec(uintptr_t s) {
 	sec = s;
 }
 uintptr_t Time::Pruintptr_tAMPM() const {
 	if (hour == 12) {
 		if ((min < 10) && (sec < 10)) {
			std::cout << (12) << ":0" << min << ":0" << sec << " PM" << std::endl;
		}
 		else if (min < 10) {
 			std::cout << (12) << ":0" << min << ':' << sec << " PM" << std::endl;
		}
		else if (sec < 10) {
			std::cout << (12) << ':' << min << ":0" << sec << " PM" << std::endl;
		}
		else {
 			std::cout << (12) << ':' << min << ':' << sec << " PM" << std::endl;
 		}
 	}
 	else if (hour > 12) {
 		if ((min < 10) && (sec < 10)) {
			std::cout << (hour-12) << ":0" << min << ":0" << sec << " PM" << std::endl;
		}
 		else if (min < 10) {
 			std::cout << (hour-12) << ":0" << min << ':' << sec << " PM" << std::endl;
		}
		else if (sec < 10) {
			std::cout << (hour-12) << ':' << min << ":0" << sec << " PM" << std::endl;
		}
		else {
 			std::cout << (hour-12) << ':' << min << ':' << sec << " PM" << std::endl;
 		}
 	}
 	else if (hour == 0) {
 		if ((min < 10) && (sec < 10)) {
			std::cout << 12 << ":0" << min << ":0" << sec << " AM" << std::endl;
		}
 		else if (min < 10) {
 			std::cout << 12 << ":0" << min << ':' << sec << " AM" << std::endl;
		}
		else if (sec < 10) {
			std::cout << 12 << ':' << min << ":0" << sec << " AM" << std::endl;
		}
 		else {
 			std::cout << 12 << ':' << min << ':' << sec << " AM" << std::endl;
 		}
 	}
 	else {
 		if ((min < 10) && (sec < 10)) {
			std::cout << hour << ":0" << min << ":0" << sec <<" AM" << std::endl;
		}
 		else if (min < 10) {
 			std::cout << hour << ":0" << min << ':' << sec << " AM" << std::endl;
		}
		else if (sec < 10) {
			std::cout << hour << ':' << min << ":0" << sec << " AM" << std::endl;
		}
		else {
 			std::cout << hour << ':' << min << ':' << sec<< " AM" << std::endl;
		}
 	}
}

bool IsEarlierThan (const Time &t1, const Time &t2) {
	if (t1.gethour() < t2.gethour()) {
		return true;
	}
	if (t1.gethour() > t2.gethour()) {
		return false;
	}
	else {
		if (t1.getmin() < t2.getmin()) {
			return true;
		}
		if (t1.getmin() > t2.getmin()) {
			return false;
		}
		else {
			if (t1.getsec() < t2.getsec()) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

void changetimes(Time&t1,Time t2) {
	t1.sethour(t1.gethour()+1);
	t1.setmin(t1.getmin()+30);
	t1.setsec(t1.getsec());
	t2.sethour(t2.gethour()+1);
	t2.setmin(t2.getmin()+30);
	t2.setsec(t2.getsec());
}