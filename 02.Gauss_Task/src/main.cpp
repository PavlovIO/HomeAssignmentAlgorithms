/* Ilya Pavlov st129535@student.spbu.ru
	02.Gauss_Task
*/
#include "gauss_solver.h"
#include "libraries.h"


int main()
{
    std::string filename;
    char delimiter;
    std::cout<<"Enter a filename .csv: ";
    std::cin>>filename;
    std::cout<<"Enter a delimiter: ";
    std::cin>>delimiter;
    GaussSolver(filename, delimiter);
    return 0;
}
