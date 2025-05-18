#include "Shannon.h"
int main()
{
    std::string data = "Hi, my name is Ilya, this is my shannon encoder/decoder and if you can read this message then I succefully created it";
    std::map<char, std::string> table;
    std::string encoded_data = shannon_encoder(data, table);
    std::string decoded_data = shannon_decoder(encoded_data, table);
    std::cout<<"Original message:"<<data<<std::endl;
    std::cout<<"Encoded message:"<<encoded_data<<std::endl;
    std::cout<<"Decoded message:"<<decoded_data<<std::endl; 
}
/*
std::string shannon_encode(const std::string& data, std::map<char, std::string>& table);
std::string shannon_decoder(const std::string& data, std::map<char, std::string>& table);
*/