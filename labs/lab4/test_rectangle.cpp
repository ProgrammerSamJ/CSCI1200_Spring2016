#include <iostream>
#include "Point2D.h"
#include "Rectangle.h"
#include <vector>
using namespace std;
int main() {
	Point2D point1(0,0);
	Point2D point2(20,20);
	Point2D point3(10,10);
	Point2D point4(30,30);
	Rectangle Rectangle1(point1,point2);
	Rectangle Rectangle2(point3,point4);
	print_rectangle(Rectangle1);
	print_rectangle(Rectangle2);

	//adding points
	Point2D point5(-1,-1);
	Point2D point6(12,12);
	bool added_point = false;
  	/*cout << Rectangle1.is_point_within(point5) <<endl;
  	cout << Rectangle1.is_point_within(point6) <<endl;
  	cout << Rectangle1.add_point(point5) << endl;*/
  	cout << Rectangle2.add_point(point6) <<endl;
  	// points_in_both(Rectangle1,Pectangle2);
	return 0;
}
