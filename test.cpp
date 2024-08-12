#include <gtest/gtest.h>
#include "solution.h"
#include <iostream>
#include <string>



TEST(CSVReaderTest, ReadBasicCSV) {
    auto data = readCSV<double>("../input/test1.csv");
    ASSERT_EQ(data.size(), 3);
    ASSERT_EQ(data[0].size(), 3);
    EXPECT_DOUBLE_EQ(data[1][1], 0.0);
}

TEST(CSVReaderTest, ReadSingleRowCSV) {
    auto data = readCSV<double>("../input/test4.csv");
    ASSERT_EQ(data.size(), 1);
    ASSERT_EQ(data[0].size(), 3);
    EXPECT_DOUBLE_EQ(data[0][0], 0.0);
}

TEST(CSVReaderTest, ReadSingleColumnCSV) {
    auto data = readCSV<double>("../input/test5.csv");
    ASSERT_EQ(data.size(), 3);
    ASSERT_EQ(data[0].size(), 1);
    EXPECT_DOUBLE_EQ(data[1][0], 0.0);
}

TEST(CSVReaderTest, ReadLargeCSV1) {
    auto data = readCSV<double>("../input/large_test1.csv");
    ASSERT_EQ(data.size(), 10);
    ASSERT_EQ(data[0].size(), 10);
    EXPECT_DOUBLE_EQ(data[1][2], 0.0);
    EXPECT_DOUBLE_EQ(data[4][9], 0.0);
}

TEST(CSVReaderTest, ReadLargeCSV2) {
    auto data = readCSV<double>("../input/large_test2.csv");
    ASSERT_EQ(data.size(), 10);
    ASSERT_EQ(data[0].size(), 10);
    EXPECT_DOUBLE_EQ(data[0][0], 0.0);
    EXPECT_DOUBLE_EQ(data[9][9], 0.0);
}


TEST(InterpolationTest, InterpolateBasic) {
    auto data = readCSV<double>("../input/test1.csv");
    interpolateBadValues(data);
    EXPECT_DOUBLE_EQ(data[1][1], 5.0);
}

TEST(InterpolationTest, InterpolateMultipleBadValues) {
    auto data = readCSV<double>("../input/test2.csv");
    interpolateBadValues(data);
    EXPECT_DOUBLE_EQ(data[0][1], 30.0);
    EXPECT_DOUBLE_EQ(data[2][2], 70.0);
}

TEST(InterpolationTest, InterpolateSingleRow) {
    auto data = readCSV<double>("../input/test4.csv");
    interpolateBadValues(data);
    EXPECT_DOUBLE_EQ(data[0][0], 2);
}

TEST(InterpolationTest, InterpolateSingleColumn) {
    auto data = readCSV<double>("../input/test5.csv");
    interpolateBadValues(data);
    EXPECT_DOUBLE_EQ(data[1][0], 2.0);
}

TEST(InterpolationTest, NoInterpolationNeeded) {
    auto data = readCSV<double>("../input/test3.csv");
    interpolateBadValues(data);
    EXPECT_DOUBLE_EQ(data[1][1], 5.0); // No change expected
}

TEST(InterpolationTest, InterpolateLargeMatrix1) {
    auto data = readCSV<double>("../input/large_test1.csv");
    interpolateBadValues(data);

    EXPECT_DOUBLE_EQ(data[1][2], 13);
    EXPECT_DOUBLE_EQ(data[4][9], 49.666666666666664);
    EXPECT_DOUBLE_EQ(data[6][5], 66);
}

TEST(InterpolationTest, InterpolateLargeMatrix2) {
    auto data = readCSV<double>("../input/large_test2.csv");
    interpolateBadValues(data);

    EXPECT_DOUBLE_EQ(data[0][0], 6.5);
    EXPECT_DOUBLE_EQ(data[0][9], 14.5); 
    EXPECT_DOUBLE_EQ(data[9][0], 86.5);
    EXPECT_DOUBLE_EQ(data[9][9], 94.5);
}

TEST(InterpolationTest, InterpolateLargeMatrix3) {
    auto data = readCSV<double>("../input/large_test3.csv");
    interpolateBadValues(data);

    EXPECT_DOUBLE_EQ(data[1][1], 12); 
    EXPECT_DOUBLE_EQ(data[1][7], 18); 
    EXPECT_DOUBLE_EQ(data[4][5], 46); 
    EXPECT_DOUBLE_EQ(data[6][2], 63); 
}


TEST(CSVWriterTest, WriteCSV) {
    auto data = readCSV<double>("../input/test1.csv");
    interpolateBadValues(data);
    writeCSV("../output/output1.csv", data);

    auto writtenData = readCSV<double>("../output/output1.csv");
    EXPECT_EQ(writtenData.size(), data.size());
    EXPECT_EQ(writtenData[0].size(), data[0].size());
    EXPECT_DOUBLE_EQ(writtenData[1][1], 5.0); // Check interpolated value
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}