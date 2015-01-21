#include <gtest/gtest.h>
#include "../include/Stream.h"

using namespace jnthn::stream;

long even( long x){
	long ans = x * 2;
	return ans;
}

long all(long x){
	return x;
}

bool isEven(long x){
	if(x % 2 == 0){
		return true;
	} else {
		return false;
	}
}

FunPromise fun = FunPromise(&even, 0, 1);
FunPromise toBeFiltered = FunPromise(&all, 0, 1);
FilPromise fil = FilPromise(&toBeFiltered, &isEven);


TEST(BasicTest, Basic){
	EXPECT_EQ(0, all(0));
	EXPECT_EQ(1, all(1));
	EXPECT_EQ(0, even(0));
	EXPECT_EQ(2, even(1));
	EXPECT_TRUE(isEven(2));
	EXPECT_TRUE(!isEven(1));
}
TEST(StreamTest, FunPromiseTest){
	Stream stream = Stream(&fun);

	EXPECT_EQ(0, stream[0]);
	EXPECT_EQ(4, stream[2]);
	EXPECT_EQ(2, stream[1]);

	++stream;
	EXPECT_EQ(2, stream[0]);

}

TEST(StreamTest, FilPromiseTest){
	Stream stream = Stream(&fil);

	EXPECT_EQ(0, stream[0]);
	EXPECT_EQ(4, stream[2]);
	EXPECT_EQ(2, stream[1]);
	++stream;
	EXPECT_EQ(2, stream[0]);
	++stream;
	EXPECT_EQ(4, stream[0]);
	++stream;
	EXPECT_EQ(6, stream[0]);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
	
