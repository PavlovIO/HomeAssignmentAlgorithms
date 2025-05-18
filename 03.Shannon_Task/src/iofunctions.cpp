/* Ilya Pavlov st129535@student.spbu.ru

*/
#include "Shannon.h"

std::string escapeSpecialChars(char c)
{
    switch (c)
    {
    case '\n':
        return "\\n";
    case '\r':
        return "\\r";
    case '\t':
        return "\\t";
    case '\\':
        return "\\\\";
    case ':':
        return "\\:"; // Чтобы двоеточие не ломало парсинг
    default:
        return std::string(1, c);
    }
}

char unescapeChar(const std::string& s)
{
    if (s == "\\n") return '\n';
    if (s == "\\r") return '\r';
    if (s == "\\t") return '\t';
    if (s == "\\\\") return '\\';
    if (s == "\\:") return ':';
    return s[0]; // Обычный символ
}

std::string readFileToString(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::binary); // Open in binary mode to avoid any transformations
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::ostringstream oss;
    oss << file.rdbuf(); // Read entire file into the string stream
    return oss.str();    // Return as string
}

std::vector<uint8_t> binaryStringToBytes(const std::string& binaryStr)
{
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < binaryStr.size(); i += 8)
    {
        std::string byteStr = binaryStr.substr(i, 8);
        byteStr.resize(8, '0'); // Pad with '0's if needed
        bytes.push_back(static_cast<uint8_t>(std::bitset<8>(byteStr).to_ulong()));
    }
    return bytes;
}

void writeEncodedData(const std::string& filePath, const std::string& encodedData)
{
    std::ofstream file(filePath, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to open file: " + filePath);

    std::vector<uint8_t> bytes = binaryStringToBytes(encodedData);
    file.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
}

void writeDictionary(const std::string& filePath, const std::map<char, std::string>& dictionary)
{
    std::ofstream file(filePath);
    if (!file) throw std::runtime_error("Failed to open file: " + filePath);

    for (const auto& [symbol, code] : dictionary)
    {
        file << escapeSpecialChars(symbol) << ":" << code << "\n";
    }
}

std::map<char, std::string> readDictionary(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file) throw std::runtime_error("Failed to open file: " + filePath);

    std::map<char, std::string> dictionary;
    std::string line;
    while (std::getline(file, line))
    {
        size_t colonPos = line.rfind(':');
        if (colonPos == std::string::npos) continue;

        std::string escapedSymbol = line.substr(0, colonPos);
        std::string code = line.substr(colonPos + 1);

        // Обрабатываем escape-последовательности
        char symbol;
        if (escapedSymbol.size() >= 2 && escapedSymbol[0] == '\\')
        {
            symbol = unescapeChar(escapedSymbol.substr(0, 2));
        }
        else
        {
            symbol = escapedSymbol[0];
        }

        dictionary[symbol] = code;
    }
    return dictionary;
}


std::string readEncodedData(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to open file: " + filePath);

    std::ostringstream binaryStream;
    char byte;
    while (file.read(&byte, 1))
    {
        binaryStream << std::bitset<8>(byte).to_string();
    }
    return binaryStream.str();
}


