#ifndef __tetris_h_
#define __tetris_h_
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class Tetris {
public:
	Tetris(int w);
	//ACCESSORS
	int get_width() const;
	int get_max_height() const;
	int get_min_height() const;
	int count_squares();
	int remove_full_rows();
	//MODIFIERS/OTHER HELPFUL FUNCTIONS
	void add_piece(char piece,int rotation,int placement);
	void resize(int old_placement,int new_column_height,int square_count,char piece);
	void resize_L(char piece,int rotation,int placement);
	void resize_S(char piece,int rotation,int placement);
	void resize_T(char piece,int rotation,int placement);
	void add_left_column();
	void add_right_column();
	void remove_left_column();
	void remove_right_column();
	void print() const;
	void destroy();
	void remove_row(int n);
	bool bound_check(int placement,int piece_width);
	bool full_row_check(int row_position);
	int temp_height(int range,int array[],char piece);
	int local_max_height(int range,int range2);
private: // REPRESENTATION
	int width;
	int *heights;
	int max_height;
	int min_height;
	char **data;
};
//NON MEMBER FUNCTIONS

#endif