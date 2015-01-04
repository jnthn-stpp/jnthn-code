#include "vector.h"

using namespace jnthn::math;

typedef enum vType {
	ROW,
	COLUMN
};

Vector::Vector(int size, vType type=COLUMN){
	data = new num[size];
	this.type = type;
	length = sizeof(data) / sizeof(data[0]);
}

Vector::Vector(num* data, vType type=COLUMN){
	this.data = data;
	this.type = type;
	length = sizeof(data) / sizeof(data[0]);
}
int Vector::get(int index){
	if(index < length){
		return data[index];
	} else {
		throw "vector index length error";	
	}
}

void Vector::set(int index, num value){
	if(index < length){
		data[index] = value;
	} else {
		throw "vector index length error";
	}
}

const Vector Vector::operator+(const Vector rvalue) const{
	if((type != rvalue.getType()) || (length != rvalue.getLength()){
	throw "Vector Addition Error";
	} else {
		num nData[length];
		for( int i = 0; i < length, i++){
			nData[i] = data[i] + rvalue.get(i);
		}
		return Vector(nData, type);
	}
}

const vType Vector::getType(){
	return type;
}

void Vector::setType(vType type){
	this.type = type;
}

int Vector::getLength(){
	return length;
}
