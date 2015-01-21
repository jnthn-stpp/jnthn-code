#include <Stream.h>
#include <iostream>
#include <ctime>
#include <cmath>

using namespace jnthn::stream;

long primes[200000];
long length = 0;

bool isPrime(long test){

	int i = 0;
	while((primes[i] <= std::sqrt(test)) && primes[i] != 0){
		long num = primes[i];
		if((test % primes[i]) == 0){
			return false;
		}
		i++;
	}

	primes[length] = test;
	length++;
	return true;
}

long all(long x){
	if(x == 1){
		return 2;	
	} else {
		return (2 * x) - 1;
	}
}

FunPromise fun = FunPromise(&all, 1);
FilPromise promise = FilPromise(&fun, &isPrime);
Stream stream = Stream(&promise);

std::clock_t t;

int main(){
	t = std::clock();
	long answer = 0;
	int position = 1;
	while(stream[0] <= 2000000){
		answer += stream[0];
		++stream;
		//std::cout << stream[0] / 100000 << " : " << answer << std::endl;
		if((stream[0] / 100000) == position){
			position++;
			std::cout << "#" << std::flush;
		} 
	}
	t = clock() - t;

	std::cout << "Answer: " << answer << std::endl;
	std::cout << "Time: " << ((float) t / CLOCKS_PER_SEC) << " seconds" << std::endl;
}
