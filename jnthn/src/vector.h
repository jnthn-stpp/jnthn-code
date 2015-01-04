namespace jnthn{
namespace math{

class Vector;
typedef enum vType;

class Vector{
	
	num * data;
	vType type;
	int length;
	
	public:

	Vector(int size, vType type=COLUMN);
	Vector(num* data, vType type=COLUMN);
	
	~Vector();

	int get(int index);
	void set(int index, num value);
	const Vector operator+(const Vector rvalue) const;
	
	const vType getType();
	void setType(vType type);

	int getLength();
};
}
}
