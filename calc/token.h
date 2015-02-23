#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace jnthn{
namespace calc{

typedef double num;
typedef num (*cfun)(num*);
enum type {
	FUNC,
	NUM
};

struct token{
	type tType;
	int priority;
	int * args;
	int numArgs;
	cfun function;
	num value;

	token(int priority, int * args, int numArgs, cfun function){
		tType = FUNC;
		this->priority = priority;
		this->args = args;
		this->numArgs = numArgs;
		this->function = function;
	}
	token(num value){
		tType = NUM;
		this->value = value;
	}
};
}
}


#endif
