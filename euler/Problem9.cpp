#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int a;
	int b;
	int c;

	int answer;

	for(int i = 16; i <= 22; i++){

		int m = i;
		int n = (500/m) - m;

		a = pow(m, 2) - pow(n, 2);
		b = 2 * m * n;
		c = pow(m, 2) + pow(n, 2);

		if(a + b + c == 1000){
			answer = a * b * c;
			break;
		}
	}

	cout << "A: " << a << endl;
	cout << "B: " << b << endl;
	cout << "C: " << c << endl;
	cout << "Answer: " << answer << endl;

}
