#ifndef FUN_H
#define FUN_H

#include "token.h"
#include <map>
#include <string>

namespace jnthn{
namespace calc{


	num jmul(num* args){
		return args[0] * args[1];
	}
	num jdiv(num* args){
		return args[0] / args[1];
	}
	num jsub(num* args){
		return args[0] - args[1];
	}
	num jadd(num* args){
		return args[0] + args[1];
	}
	num jpow(num* args){
		num total = 1;	
		for(int i = 0; i < args[1]; i++){
			total *= args[0];
		}
		return total;
	}

	int ariArgs[2] = {-1, 1};
}
}

#endif
