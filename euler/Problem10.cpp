#include <Stream.h>
#include <iostream>
#include <ctime>

using namespace jnthn::stream;

long primes[200000];

bool isPrime(long test){

	int i = 0;
	while(primes[i] != 0){
		if(test % primes[i] == 0){
			return false;	
		}

		i++;
	}

	primes[i] = test;
	return true;
}

long all(long x){
	return x;
}

FunPromise<long> fun = FunPromise<long>(&all, 2);
FilPromise<long> promise = FilPromise<long>(&fun, &isPrime);
Stream<long> stream = Stream<long>(&promise);

std::clock_t t;

int main(){
	t = std::clock();
	long answer = 0;
	int position = 1;
	while(stream[0] <= 2000000){
		answer += stream[0];	
		++stream;
		//std::cout << stream[0] / 100000 << " : " << answer << std::endl;
		 /*if((stream[0] / 100000) == position){
			position++;
			std::cout << "#" << std::flush;
		} */
	}
	t = clock() - t;

	std::cout << "Answer: " << answer << std::endl;
	std::cout << "Time: " << ((float) t / CLOCKS_PER_SEC) << " seconds" << std::endl;
}
