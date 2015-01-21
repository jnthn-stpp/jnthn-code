#include "../include/Stream.h"

using namespace jnthn::stream;

//Stream//////////////////////////////////////
Stream::Stream(Promise * p){
	if( p != 0){
		first = p->copy();
	} 
}
num Stream::operator[](const int index){
	Promise * current = first;
	for(int i = 0; i < index; i++){
		current = current->getNext();
		current->getData();
	}
	num value = current->getData();
	return value;
}

Stream& Stream::operator++(){
	Promise * old = first;
	old = first;
	first = (first->getNext())->copy();
	delete old;
	return *(this);
}

Stream::~Stream(){
	delete first;
}

//Promise//////////////////////////////////]

Promise::~Promise(){
	if(generated){
		delete nxt;
	}
}

//FunPromise/////////////////////////////////
FunPromise::FunPromise(function fun, num domain, num delta){
	this->fun = fun;
	this-> domain = domain;
	this-> delta = delta;
	collected = false;
	generated = false;
	id = 54;
}

num FunPromise::getData(){
	if(!collected){
		collected = true;
		range = fun(domain);
	}
	return range;
}

Promise* FunPromise::getNext(){
	if(!generated){
		generated = true;
		nxt = new FunPromise(fun, (domain + delta), delta);
	}
	return nxt;
}

Promise * FunPromise::copy(){
	return new FunPromise(fun, domain, delta);
}

//FilPromise////////////////////////////////////////
FilPromise::FilPromise(Promise * data, FilPromise::function filter){

	this->data = data->copy();
	this->filter = filter;
	generated = false;
	collected = false;
}

num FilPromise::getData(){
	if(!collected){
		while(!(filter(data->getData()))){
			data = data->getNext();
		}
		collected = true;
		range = data->getData();
	}
	return range;
}

Promise * FilPromise::getNext(){
	if(!collected){
		getData();
	}
	if(!generated){
		nxt = new FilPromise(data->getNext(), filter);
		generated = true;
	}
	return nxt;
}

Promise * FilPromise::copy(){
	Promise * ndata = data->copy();
	return new FilPromise(ndata, filter);
}

FilPromise::~FilPromise(){
	if(generated){
		delete nxt;
	}
		delete data;
}
