#include "gtest/gtest.h"
#include "../include/Stream.h"

using namespace jnthn::stream;

int even( int x){
	return x*2;
}

int all(int x){
	return x;
}

bool isEven(int x){
	if(x % 2 == 0){
		return true;
	} else {
		return false;
	}
}

FunPromise<int> fun = FunPromise<int>(&even, 0);
FunPromise<int> toBeFiltered = FunPromise<int>(&all, 0);
FilPromise<int> fil = FilPromise<int>(&toBeFiltered, &isEven);
Stream<int> stream = Stream<int>(0);



TEST(StreamTest, FunPromiseTest){
	stream = Stream<int>(&fun);
	EXPECT_EQ(0, stream[0]);
	EXPECT_EQ(4, stream[2]);
	EXPECT_EQ(2, stream[1]);

}

TEST(StreamTest, FilPromiseTest){
	stream = Stream<int>(&fil);
	EXPECT_EQ(0, stream[0]);
	EXPECT_EQ(4, stream[2]);
	EXPECT_EQ(2, stream[1]);
}

TEST(StreamTest, IteratorOperatorTest){
	stream = Stream<int>(&fun);
	EXPECT_EQ(0, stream[0]);
	++stream;
	EXPECT_EQ(2, stream[0]);
	
}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
	
