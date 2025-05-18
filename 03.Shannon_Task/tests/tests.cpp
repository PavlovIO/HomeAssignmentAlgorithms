/* Ilya Pavlov st129535@student.spbu.ru

*/
#include <gtest/gtest.h>
#include "Shannon.h"
#include <fstream>
#include <random>
#include <filesystem>  
#include <cstdlib>    

class ShannonCodingTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary directory for test files
        temp_dir = "test_temp";
#ifdef _WIN32
        _mkdir(temp_dir.c_str());
#else 
        mkdir(temp_dir.c_str(), 0777);
#endif
    }

    void TearDown() override {
        // Clean up temporary files
        // Simple implementation - in real code you'd want to remove files properly
        std::string cmd;
#ifdef _WIN32
        cmd = "rmdir /s /q \"" + temp_dir + "\"";
#else
        cmd = "rm -rf \"" + temp_dir + "\"";
#endif
        system(cmd.c_str());
    }

    std::string temp_dir;
};

// Helper function to generate random strings
std::string generateRandomString(size_t length) {
    static const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        " \t\n\r\f\v!@#$%^&*()_+-=[]{}|;:',.<>?/\"\\";

    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<size_t> dist(0, sizeof(charset) - 2);

    std::string result;
    result.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        result += charset[dist(rng)];
    }
    return result;
}

TEST_F(ShannonCodingTest, EmptyString) {
    std::string input = "";
    std::map<char, std::string> table;
    
    std::string encoded = shannon_encoder(input, table);
    std::string decoded = shannon_decoder(encoded, table);
    
    EXPECT_EQ(input, decoded);
    EXPECT_TRUE(encoded.empty());
}

TEST_F(ShannonCodingTest, SingleCharacter) {
    std::string input = "a";
    std::map<char, std::string> table;
    
    std::string encoded = shannon_encoder(input, table);
    std::string decoded = shannon_decoder(encoded, table);
    
    EXPECT_EQ(input, decoded);
    EXPECT_EQ(table.size(), 1);
}

TEST_F(ShannonCodingTest, RepeatedSingleCharacter) {
    std::string input(100, 'x');
    std::map<char, std::string> table;
    
    std::string encoded = shannon_encoder(input, table);
    std::string decoded = shannon_decoder(encoded, table);
    
    EXPECT_EQ(input, decoded);
    EXPECT_EQ(table.size(), 1);
}

TEST_F(ShannonCodingTest, AllUniqueCharacters) {
    std::string input = "abcdefghijklmnopqrstuvwxyz";
    std::map<char, std::string> table;
    
    std::string encoded = shannon_encoder(input, table);
    std::string decoded = shannon_decoder(encoded, table);
    
    EXPECT_EQ(input, decoded);
    EXPECT_EQ(table.size(), input.size());
}

TEST_F(ShannonCodingTest, SpecialCharacters) {
    std::string input = "Hello\tWorld\n\r\\:\"";
    std::map<char, std::string> table;
    
    std::string encoded = shannon_encoder(input, table);
    std::string decoded = shannon_decoder(encoded, table);
    
    EXPECT_EQ(input, decoded);
}

TEST_F(ShannonCodingTest, RandomStringSmall) {
    std::string input = generateRandomString(50);
    std::map<char, std::string> table;
    
    std::string encoded = shannon_encoder(input, table);
    std::string decoded = shannon_decoder(encoded, table);
    
    EXPECT_EQ(input, decoded);
}

TEST_F(ShannonCodingTest, RandomStringMedium) {
    std::string input = generateRandomString(1000);
    std::map<char, std::string> table;
    
    std::string encoded = shannon_encoder(input, table);
    std::string decoded = shannon_decoder(encoded, table);
    
    EXPECT_EQ(input, decoded);
}

TEST_F(ShannonCodingTest, RandomStringLarge) {
    std::string input = generateRandomString(10000);
    std::map<char, std::string> table;
    
    std::string encoded = shannon_encoder(input, table);
    std::string decoded = shannon_decoder(encoded, table);
    
    EXPECT_EQ(input, decoded);
}

TEST_F(ShannonCodingTest, FileRoundTrip) {
    std::string input = "This is a test string with some special characters: \t\n\r\\:";
    std::string input_file = temp_dir + "/input.txt";
    std::string encoded_file = temp_dir + "/encoded.bin";
    std::string dict_file = temp_dir + "/dict.txt";
    std::string output_file = temp_dir + "/output.txt";
    
    // Write input to file
    std::ofstream in_file(input_file);
    in_file << input;
    in_file.close();
    
    // Read input from file
    std::string file_content = readFileToString(input_file);
    
    // Encode
    std::map<char, std::string> table;
    std::string encoded = shannon_encoder(file_content, table);
    
    // Write encoded data and dictionary
    writeEncodedData(encoded_file, encoded);
    writeDictionary(dict_file, table);
    
    // Read back encoded data and dictionary
    std::string read_encoded = readEncodedData(encoded_file);
    std::map<char, std::string> read_table = readDictionary(dict_file);
    
    // Decode
    std::string decoded = shannon_decoder(read_encoded, read_table);
    
    // Write decoded output
    std::ofstream out_file(output_file);
    out_file << decoded;
    out_file.close();
    
    // Read output file
    std::string output_content = readFileToString(output_file);
    
    EXPECT_EQ(input, output_content);
}

TEST_F(ShannonCodingTest, BinaryData) {
    std::string input;
    for (int i = 0; i < 256; ++i) {
        input += static_cast<char>(i);
    }
    
    std::map<char, std::string> table;
    std::string encoded = shannon_encoder(input, table);
    std::string decoded = shannon_decoder(encoded, table);
    
    EXPECT_EQ(input, decoded);
    EXPECT_EQ(table.size(), 256);
}
