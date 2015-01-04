#include <Stream.h>
#include <iostream>

using namespace jnthn::stream;

int primes[10001];

int all(int x){
	return x;
}

bool seive(int x){
	int i = 0;
	while(primes[i] != 0){
		if(x % primes[i] == 0){
			return false;
		}
		i++;
	}

	primes[i] = x;
	return true;
}

FunPromise<int> data = FunPromise<int>(&all, 2);
FilPromise<int> promise = FilPromise<int>(&data, &seive);
Stream<int> stream = Stream<int>(&promise);

int main(){
	std::cout << "Answer: " << stream[10000] << std::endl;
}
