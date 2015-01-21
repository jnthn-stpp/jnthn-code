#ifndef STREAM_H
#define STREAM_H
namespace jnthn{
namespace stream{

class Stream;
class Promise;
class NumPromise;
class FunPromise;
class FilPromise;

typedef long num;

class Stream{

	Promise * first;

	public:
	Stream(Promise * p);
	num operator[](const int index);
	Stream& operator++();
	~Stream();

};

class Promise {
	
	friend class Stream;

	protected:

	bool collected;
	bool generated;
	num range;
	Promise * nxt;

	public:
	
	virtual Promise * getNext() = 0;
	virtual num getData() = 0;
	virtual Promise * copy() = 0;
	~Promise();
};

class NumPromise : public Promise {
	public:
	typedef num (*function)(num domain); 	
	virtual num getData() = 0;
	virtual Promise  * getNext() = 0;
	virtual Promise * copy() = 0;
	
	protected:
	num domain;
	function fun;

};

class FunPromise : public NumPromise {
	protected:
	num delta;
	int id;

	public:
	FunPromise(function fun, num domain, num delta=1);
	virtual num getData();
	virtual Promise* getNext();
	virtual Promise * copy();
};

class FilPromise : public Promise {
	public:
	typedef bool (*function)(num value);
	FilPromise(Promise* data, FilPromise::function filter);
	virtual num getData();
	virtual Promise* getNext();
	virtual Promise * copy();
	~FilPromise();
	protected:
	function filter;
	Promise* data;
};

}
}
#endif
