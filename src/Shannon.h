#ifndef SHANNON_H
#define SHANNON_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

std::map<char, double> calc_freq(const std::string& data, std::map<char, std::string>& table);
void create_table( std::map<char, double>& freq, std::map<char, std::string>& table, int length );
void shannon(std::vector<std::pair<char, double>>& symbols, std::map<char, std::string>& table, int start, int end, double total_prob);
std::string shannon_encoder(const std::string& data, std::map<char, std::string>& table);
std::string shannon_decoder(const std::string& data, std::map<char, std::string>& table);
#endif