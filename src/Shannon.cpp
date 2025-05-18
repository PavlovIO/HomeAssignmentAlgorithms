/* Ilya Pavlov st129535@student.spbu.ru

*/
#include "Shannon.h"
std::map<char, double> calc_freq(const std::string& data)
{
    std::map<char, double> freq;
    for (char c : data)
    {
        freq[c]++;
    }
    return freq;
}

void create_table( std::map<char, double>& freq, std::map<char, std::string>& table, int length )
{
    std::vector<std::pair<char, double>> calc_prob(freq.begin(),freq.end());
    std::sort(
        calc_prob.begin(),
        calc_prob.end(),
        [](const auto& a, const auto& b)
    {
        return a.second < b.second;
    }
    );
    for (auto& [symbol, frequency] : calc_prob)
    {
        frequency /= length;
    }

    double total_prob = 0.0;
    for (const auto& [symbol, prob] : calc_prob)
    {
        total_prob += prob;
    }
    shannon(calc_prob, table, 0, calc_prob.size(), total_prob);

}

void shannon(std::vector<std::pair<char, double>>& symbols, std::map<char, std::string>& table, int start, int end, double total_prob)
{
    if (start >= end) return;

    if (start == end - 1)
    {
        return;
    }

    double half = 0.0;
    int split = start;

    for (int i = start; i < end; ++i)
    {
        half += symbols[i].second;
        if (half >= total_prob / 2 - 1e-10)
        {
            if (std::abs(half - total_prob / 2) > std::abs((half - symbols[i].second) - total_prob / 2))
            {
                split = i;
                half -= symbols[i].second;
            }
            else
            {
                split = i + 1;
            }
            break;
        }
    }

    for (int i = start; i < split; ++i)
    {
        table[symbols[i].first] += "0";
    }
    for (int i = split; i < end; ++i)
    {
        table[symbols[i].first] += "1";
    }

    shannon(symbols, table, start, split, half);
    shannon(symbols, table, split, end, total_prob - half);
}

std::string shannon_encoder(const std::string& data, std::map<char, std::string>& table)
{
    std::map<char, double> freq = calc_freq(data);
    table.clear();
    
    if (freq.size() == 1) {
        table[data[0]] = "0";  // Assign simple code
        return std::string(data.size(), '0'); // Return all 0's
    }    
    
    create_table(freq, table, data.size());
    std::string encoded;
    encoded.reserve(data.size() * 5);
    for (char c : data)
    {
        encoded += table.at(c);
    }

    return encoded;
}

std::string shannon_decoder(const std::string& data, std::map<char, std::string>& table)
{
    std::map<std::string, char> reversed_table;
    for (const auto& [symbol, code] : table)
    {
        reversed_table[code] = symbol;
    }
    std::string decoded_data;
    std::string code;
    for (char c : data)
    {
        code += c;
        if (reversed_table.find(code) != reversed_table.end())
        {
            decoded_data += reversed_table[code];
            code.clear();
        }
    }
    if (!code.empty())
    {
        std::string repeated(code.size(), '0');
        if (code != repeated)
        {
            throw std::runtime_error("Invalid Shannon-Fano encoded data: leftover bits");
        }
    }
    return decoded_data;
}
