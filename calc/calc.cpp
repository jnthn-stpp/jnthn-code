#include "calc.h"
#include "fun.h"
#include <cstring>


using namespace jnthn::calc;

std::map<std::string, token *> funLookupTable;
token powtok = token(3, ariArgs, 2, *jpow);	
token multok = token(2, ariArgs, 2, *jmul);	
token divtok = token(2, ariArgs, 2, *jdiv);	
token addtok = token(1, ariArgs, 2, *jadd);	
token subtok = token(1, ariArgs, 2, *jsub);	

void jnthn::calc::setupDefFuns(){

	funLookupTable.insert(std::pair<std::string, token*>("^" ,&powtok));
	funLookupTable.insert(std::pair<std::string, token*>("*" ,&multok));
	funLookupTable.insert(std::pair<std::string, token*>("/" ,&divtok));
	funLookupTable.insert(std::pair<std::string, token*>("+" ,&addtok));
	funLookupTable.insert(std::pair<std::string, token*>("-" ,&subtok));
}

std::vector<token*> jnthn::calc::parseLine(std::string line){
	char * data = new char[line.length() + 1];
	std::strcpy(data, line.c_str());
	char* result;
	std::vector<token *> ret;

	result = std::strtok(data, " ");

	while(result != NULL){
		// add result-token to array
		if(funLookupTable.find(result) != funLookupTable.end()){
			token * temp = funLookupTable[result];
			ret.push_back(new token(temp->priority, temp->args, temp->numArgs, temp->function));
		} else if(std::isdigit(result[0])){
			int value;
			value = std::atoi(result);
			ret.push_back(new token(value));
		} else {
			std::cout << "Found bad token: " << result << std::endl;
		}

		result = std::strtok(NULL, " ");
	}
	delete[] data;
	//printTStream(ret);
	return ret;
}

void jnthn::calc::printTStream(std::vector<token *> stream){
	for(int i = 0; i < stream.size(); i++){
		if(stream[i]->tType == FUNC){
			std::cout << "FUNC ";
		} else if (stream[i]->tType == NUM ) {
			std::cout << "NUM :" << stream[i]->value << " ";
		}
	}
}

void jnthn::calc::simplify(int priority, std::vector<jnthn::calc::token *> & stack) { 
	for(int i = 0; i < stack.size(); i++){
		if(stack[i]->tType != FUNC || stack[i]->priority != priority){
			continue;
		} 
		int size = stack[i]->numArgs;
		jnthn::calc::num * args = new num[size]; 
		for(int j = 0; j < size; j++){
			token * t = stack[i + stack[i]->args[j]];
			if(t->tType = NUM){
				args[j] = t->value;
			} else {
				std::cout << "Invalid Token Order" << std::endl;
			}
		}
		num value = stack[i]->function(args);
		num * largs = stack[i]->args;
		delete stack[i];
		stack[i] = new token(value);
		for(int j = 0; j < size; j++){
			delete stack[i + largs[j]];
			stack.erase(stack.begin() + (i + largs[j]));
			if(i + largs[j] < i){
				i--;
			} else {
				i++;
			}
		}

		delete[] args;
		
		
	}
}
