#include <iostream>
int main() {
	float total=0;
	std::cout << "Array size??????" << std::endl;
	int size;
	std::cin >> size;
	std::cout << "Array size is " << size << std::endl;
	float new_array[size];
	for (int n=0;n<size;n++) {
		std::cout << "Enter your number =>" <<std::endl;
		float input;
		std::cin >> input;
		new_array[n] = input;
	}
	for (int n=0;n<=size-1;n++) {
		total += new_array[n];
	}
	std::cout << "Total:" << total << std::endl;
	float mean = float(total) / float(size);
	std::cout << "mean:" << mean << std::endl;
	for (int n=0;n<size;n++) {
		std::cout << "*" << std::endl;
		if (new_array[n] < mean) {
			std::cout << new_array[n] << "is less than the average\n" << std::endl;
		}
	}
return 0;
}