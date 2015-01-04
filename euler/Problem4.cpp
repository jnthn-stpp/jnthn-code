#include <Stream.h>
#include <iostream>
#include <cmath>

using namespace jnthn::stream;

const int limit = 998001; // 999 * 999 

int all(int x){
	return x;
}

bool isPali(int x);

FunPromise<int> nums = FunPromise<int>(&all, 10000);
FilPromise<int> promise = FilPromise<int>(&nums, &isPali);
Stream<int> stream = Stream<int>(&promise);

int main(){
	int numPali = 0;
	while(stream[numPali] < limit){
		numPali++;
	}
	numPali -= 1;
	int answer = 0;
	bool answered = false;
	int a = 0;
	int b = 0;
	for( int i = numPali; i >= 0; i--){
		int test = stream[i];
		//std::cout << "pali# " << i << ":" << test << std::endl;
		for( int j = 999; j >= std::sqrt(test); j--){
			if((test % j == 0) && !answered){
				answer = test;
				answered = true;
				a = j;
				b = answer / a;
			}
		}
	}
	std::cout << "Answer: " << answer << " (" << a <<" * " << b << ")" << std::endl;
}

bool isPali(int x){
	int size = std::log10(x);
	int xcopy = x;
	int digits[size + 1];
	for(int i = size; i >= 0; i--){
		digits[i] = xcopy / std::pow(10, i);
		xcopy -= digits[i] * std::pow(10, i);
	}
	
	int pali = 0;
	for(int i = 0; i <= size; i++){
		pali += (digits[i] * std::pow(10, size - i));
	}

	return (x == pali);
}
