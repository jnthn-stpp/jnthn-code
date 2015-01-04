#include "../include/Stream.h"

using namespace jnthn::stream;

template<typename num>
Stream<num>::Stream(Promise<num> * p){
	first = p;
}
template<typename num>
num Stream<num>::operator[](const int index){

	Promise<num> * current = first;
	for(int i = 0; i < index; i++){
		current = current->getNext();
	}
	return current->getData();
}

template<typename num>
FunPromise<num>::FunPromise(FunPromise<num>::function fun, num domain, num delta){
	this->fun = fun;
	this-> domain = domain;
	this-> delta = delta;
}

template<typename num>
num FunPromise<num>::getData(){
	if(!this->collected){
		this->collected = true;
		this->range = this->fun(this->domain);
	}
	return this->range;
}

template<typename num>
Promise<num>* FunPromise<num>::getNext(){
	if(!this->generated){
		this->generated = true;
		this->nxt = new FunPromise(this->fun, (this->domain + delta), delta);
	}
	return this->nxt;
}

template<typename num>
FilPromise<num>::FilPromise(Promise<num> * data, FilPromise<num>::function filter){

	this->data = data;
	this->filter = filter;
}

template<typename num>
num FilPromise<num>::getData(){
	if(!this->collected){
		while(!(filter(this->data->getData()))){
			this->data = this->data->getNext();
		}
		this->collected = true;
		this->range = this->data->getData();
	}
	return this->range;
}

template<typename num>
Promise<num> * FilPromise<num>::getNext(){
	if(!this->collected){
		getData();
	}
	if(!this->generated){
		this->nxt = new FilPromise(data->getNext(), filter);
		this->generated = true;
	}
	return this->nxt;
}

// types:

template class Stream<int>;
template class FunPromise<int>;
template class FilPromise<int>;
template class Stream<long>;
template class FunPromise<long>;
template class FilPromise<long>;
template class Stream<double>;
template class FunPromise<double>;
template class FilPromise<double>;
