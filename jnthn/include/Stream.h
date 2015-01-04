#ifndef STREAM_H
#define STREAM_H
namespace jnthn{
namespace stream{

template<typename num>
class Stream;
template<typename num>
class Promise;
template<typename num>
class NumPromise;
template<typename num>
class FunPromise;
template<typename num>
class FilPromise;

template<typename num>
class Stream{

	Promise<num> * first;

	public:
	Stream(Promise<num> * p);
	num operator[](const int index);
	Stream& operator++(){ 

		first = first->getNext();
		return *this;	
	};

};

template<typename num>
class Promise {
	
	protected:
	bool collected;
	bool generated;
	num range;
	Promise<num> * nxt;
	public:
	virtual Promise<num> * getNext() = 0;
	virtual num getData() = 0;
};

template<typename num>
class NumPromise : public Promise<num> {
	public:
	typedef num (*function)(num domain); 	
	virtual num getData() = 0;
	virtual Promise <num> * getNext() = 0;
	
	protected:
	num domain;
	function fun;

};

template<typename num>
class FunPromise : public NumPromise<num> {
	protected:
	num delta;
	public:
	typedef num (*function)(num domain); 	
	FunPromise(FunPromise::function fun, num domain, num delta=1);
	virtual num getData();
	virtual Promise<num>* getNext();
};

template<typename num>
class FilPromise : public Promise<num> {
	public:
	typedef bool (*function)(num value);
	FilPromise(Promise<num>* data, FilPromise<num>::function filter);
	virtual num getData();
	virtual Promise<num>* getNext();

	protected:
	function filter;
	Promise<num>* data;
};

}
}
#endif
