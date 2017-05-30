class Time{
public:
	Time();
	Time (uintptr_t ahour,uintptr_t amin, uintptr_t asec);

	//MEMBER FUNCTIONS
	//ACCESSORS
	uintptr_t gethour() const;
	uintptr_t getmin() const;
	uintptr_t getsec() const;
	//MODIFIERS
	void sethour(uintptr_t ahour);
	void setmin(uintptr_t amin);
	void setsec(uintptr_t asec);
	//OTHER
	uintptr_t PrintAMPM() const;

private: //(member variables)
	uintptr_t hour;
	uintptr_t min;
	uintptr_t sec;

};

bool IsEarlierThan (const Time&t1, const Time&t2);
void changetimes (Time&t1,Time t2);
// 	if (t1.gethour() < t2.gethour()) {
// 		return true;
// 	}
// 	else {
// 		if (t1.getmin() < t2.getmin()) {
// 			return true;
// 		}
// 		else {
// 			if (t1.getsec() < t2.getsec()) {
// 				return true;
// 			}
// 			else {
// 				return false;
// 			}
// 		}
// 	}
// }