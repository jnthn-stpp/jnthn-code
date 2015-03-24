#include "calc.h"
#include <string>
#include <iostream>
#include <cstdlib>

//using namespace std;
void welcome();

bool running;
bool print;

int main(){
	running = true;
	print = false;
	welcome();
	jnthn::calc::setupDefFuns();


	while(running){

		std::string line;
		std::cout << "> ";
		std::getline(std::cin, line);

		if(line =="quit"){
			running = false;
			continue;
		}else if(line =="clear"){
			std::system("clear");
			continue;
		}else if(line =="p"){
			print = !print;
			continue;
		}

		std::vector<jnthn::calc::token *> stream = jnthn::calc::parseLine(line);
		if(print){
			printTStream(stream);
		}
		for(int i = 10; i >= 0; i--){
			jnthn::calc::simplify(i, stream);
		}

		jnthn::calc::setAns(stream[0]->value);

		std::cout << std::endl << "===> " << stream[0]->value <<std::endl;

	

		for(int i = 0; i < stream.size(); i++){
			jnthn::calc::token * temp = stream[i];
			delete temp;
			stream.erase(stream.begin() + i);
		}

		stream.clear();
}
}

void welcome(){
	system("clear");
	std::cout << "Welcome to the JNTHN Calculator:" << std::endl;	
	std::cout  << std::endl;	
	std::cout << "It is a simple Basic Calculator implementation," << std::endl;	
	std::cout << "that currently supports basic arithmatic. Floating" << std::endl;	
	std::cout << "point numbers are not yet supported." << std::endl;	
	std::cout  << std::endl;	
	std::cout << "Type 'clear' to clear the screen and 'quit'" << std::endl;	
	std::cout << "to end the program" << std::endl;	
}


