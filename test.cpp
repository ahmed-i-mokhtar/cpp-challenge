#include <gtest/gtest.h>
#include "solution.h"

input_folder = "input/"
output_folder = "output/"

TEST(CSVReaderTest, ReadBasicCSV) {
    auto data = readCSV<double>(input_folder+"test1.csv");
    ASSERT_EQ(data.size(), 3);
    ASSERT_EQ(data[0].size(), 3);
    EXPECT_DOUBLE_EQ(data[1][1], 0.0);
}

TEST(CSVReaderTest, ReadSingleRowCSV) {
    auto data = readCSV<double>(input_folder+"test4.csv");
    ASSERT_EQ(data.size(), 1);
    ASSERT_EQ(data[0].size(), 3);
    EXPECT_DOUBLE_EQ(data[0][0], 0.0);
}

TEST(CSVReaderTest, ReadSingleColumnCSV) {
    auto data = readCSV<double>(input_folder+"test5.csv");
    ASSERT_EQ(data.size(), 3);
    ASSERT_EQ(data[0].size(), 1);
    EXPECT_DOUBLE_EQ(data[1][0], 0.0);
}

TEST(InterpolationTest, InterpolateBasic) {
    auto data = readCSV<double>(input_folder+"test1.csv");
    interpolateBadValues(data);
    EXPECT_DOUBLE_EQ(data[1][1], 5.0); // (2 + 6 + 4 + 8) / 4 = 5
}

TEST(InterpolationTest, InterpolateMultipleBadValues) {
    auto data = readCSV<double>(input_folder+"test2.csv");
    interpolateBadValues(data);
    EXPECT_DOUBLE_EQ(data[0][1], 20.0); // (10 + 50 + 30) / 3 = 30
    EXPECT_DOUBLE_EQ(data[2][2], 70.0); // (60 + 80) / 2 = 70
}

TEST(InterpolationTest, InterpolateSingleRow) {
    auto data = readCSV<double>(input_folder+"test4.csv");
    interpolateBadValues(data);
    EXPECT_DOUBLE_EQ(data[0][0], 2.5); // (2 + 3) / 2 = 2.5
}

TEST(InterpolationTest, InterpolateSingleColumn) {
    auto data = readCSV<double>(input_folder+"test5.csv");
    interpolateBadValues(data);
    EXPECT_DOUBLE_EQ(data[1][0], 2.0); // (1 + 3) / 2 = 2.0
}

TEST(InterpolationTest, NoInterpolationNeeded) {
    auto data = readCSV<double>(input_folder+"test3.csv");
    interpolateBadValues(data);
    EXPECT_DOUBLE_EQ(data[1][1], 5.0); // No change expected
}


TEST(CSVWriterTest, WriteCSV) {
    auto data = readCSV<double>(input_folder+"test1.csv");
    interpolateBadValues(data);
    writeCSV(output_folder+"output1.csv", data);

    auto writtenData = readCSV<double>(output_folder+"output1.csv");
    EXPECT_EQ(writtenData.size(), data.size());
    EXPECT_EQ(writtenData[0].size(), data[0].size());
    EXPECT_DOUBLE_EQ(writtenData[1][1], 5.0); // Check interpolated value
}
