#include <iostream>
#include <vector>
#include <list>
void reverse_vector(std::vector<int> &v){
	int x,y;
	for(int i=0;i<v.size()/2;i++){
		int x = v[i];
		int y = v[v.size()-1-i];
		v[i] = y;
		v[v.size()-1-i] = x;
	}
}
void reverse_vector2(std::list<int> &l){
	std::list<int>::reverse_iterator ri;
	std::list<int>::iterator it;
	it = l.begin();
	int i = 0;
	int x,y;
	//int i=0;
	for (ri = l.rbegin();ri != l.rend();ri++){ 
		if (i < (l.size()/2)) {
			x = *ri;
			y = *it;
			*ri = y;
			*it = x;
			it++;
		}
		i++;
	}
}
void print(std::vector<int> &v){
	for(int i=0;i<v.size();i++){
		std::cout << v[i] << std::endl;
	}
}
void add(std::vector<int> &v,int num){
	for(int i=0;i<num;i++){
		v.push_back(i);
	}
}

int main() {
	std::cout << "//////BEFORE REVERSE/////" <<std::endl;
	std::vector<int> v1;
	add(v1,7);
	print(v1);
	reverse_vector(v1);
	std::cout << "//////AFTER REVERSE/////" <<std::endl;
	print(v1);

	std::list<int> a;
	unsigned int i;
	std::cout << "//////BEFORE REVERSE LIST/////" <<std::endl;
	for ( i=1; i<10; ++i ) a.push_back( i*i );
		std::list<int>::iterator ri;
	for( ri = a.begin(); ri != a.end(); ++ri )
		std::cout << *ri << std::endl;
	std::cout << "//////AFTER REVERSE LIST/////" <<std::endl;
	reverse_vector2(a);
	for( ri = a.begin(); ri != a.end(); ++ri )
		std::cout << *ri << std::endl;
return 0;
}