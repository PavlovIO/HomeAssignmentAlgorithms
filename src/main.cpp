/* Ilya Pavlov st129535@student.spbu.ru

*/
#include "Shannon.h"
/*Hi, my name is Ilya, this is my shannon encoder/decoder
 and if you can read this message then I succefully created it*/
int main()
{

    std::string ENCODED_FILE = "encoded.bin";
    std::string DECODED_FILE = "decoded.txt";
    std::string DICT = "dict.txt";

    std::cout<<"Encode or decode e/d:";
    std::string mode;
    std::cin>>mode;
    if (mode != "e" and mode != "d")
    {
        std::cerr<<"Wrong mode. e - encode, d - decode"<<std::endl;
        return 1;
    }

    if (mode == "e")
    {
        std::cout<<"Enter a file to encode:";
        std::string file;
        std::cin>>file;
        std::string data = readFileToString(file);
        std::map<char, std::string> table;
        std::string encoded_data = shannon_encoder(data, table);
        std::vector<uint8_t> biniry_data;
        biniry_data = binaryStringToBytes(encoded_data);
        writeEncodedData(ENCODED_FILE, encoded_data);
        writeDictionary(DICT, table);
    }
    else
    {
        std::cout<<"Enter a file to decode:";
        std::string file;
        std::cin>>file;
        std::cout<<"Enter a dict file:";
        std::string dict_file;
        std::cin>>dict_file;
        std::map<char, std::string> table;
        table = readDictionary(dict_file);
        std::string encoded_data = readEncodedData(file);
        std::string decoded_data = shannon_decoder(encoded_data, table);
        std::ofstream output(DECODED_FILE);
        output.write(decoded_data.data(), decoded_data.size());
    }

    return 0;
}

