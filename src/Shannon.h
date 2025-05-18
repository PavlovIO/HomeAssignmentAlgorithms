#ifndef SHANNON_H
#define SHANNON_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>

std::map<char, double> calc_freq(const std::string& data, std::map<char, std::string>& table);
void create_table( std::map<char, double>& freq, std::map<char, std::string>& table, int length );
void shannon(std::vector<std::pair<char, double>>& symbols, std::map<char, std::string>& table, int start, int end, double total_prob);


#endif