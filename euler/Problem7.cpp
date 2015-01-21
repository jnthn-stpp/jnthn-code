#include <Stream.h>
#include <iostream>

using namespace jnthn::stream;

long primes[10001];

long all(long x){
	return x;
}

bool seive(long x){
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

FunPromise data = FunPromise(&all, 2);
FilPromise promise = FilPromise(&data, &seive);
Stream stream = Stream(&promise);

int main(){
	std::cout << "Answer: " << stream[10000] << std::endl;
}
