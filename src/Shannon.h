/* Ilya Pavlov st129535@student.spbu.ru
	
*/
#ifndef SHANNON_H
#define SHANNON_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <bitset>
std::map<char, double> calc_freq(const std::string& data, std::map<char, std::string>& table);
void create_table( std::map<char, double>& freq, std::map<char, std::string>& table, int length );
void shannon(std::vector<std::pair<char, double>>& symbols, std::map<char, std::string>& table, int start, int end, double total_prob);
std::string shannon_encoder(const std::string& data, std::map<char, std::string>& table);
std::string shannon_decoder(const std::string& data, std::map<char, std::string>& table);

std::vector<uint8_t> binaryStringToBytes(const std::string& binaryStr);
void writeEncodedData(const std::string& filePath, const std::string& encodedData);
void writeDictionary(const std::string& filePath, const std::map<char, std::string>& dictionary);
std::map<char, std::string> readDictionary(const std::string& filePath);
std::string readEncodedData(const std::string& filePath);
std::string readFileToString(const std::string& filePath);
std::string escapeSpecialChars(char c);
char unescapeChar(const std::string& s);
#endif
