/* Ilya Pavlov st129535@student.spbu.ru
	02.Gauss_Task
*/
#include "libraries.h"
#include "gauss_solver.h"

Eigen::MatrixXd csvToEigen(const std::string& filename, char delimiter)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::vector<std::vector<double>> data;
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, delimiter))
        {
            try
            {
                row.push_back(std::stod(cell));
            }
            catch (const std::exception& e)
            {
                throw std::runtime_error("Error converting string to double: " + cell);
            }
        }

        if (!row.empty())
        {
            data.push_back(row);
        }
    }

    if (data.empty())
    {
        return Eigen::MatrixXd(0, 0);
    }

    // Проверка, что все строки имеют одинаковую длину
    size_t cols = data[0].size();
    for (size_t i = 1; i < data.size(); ++i)
    {
        if (data[i].size() != cols)
        {
            throw std::runtime_error("Inconsistent number of columns in CSV file");
        }
    }

    // Создание матрицы Eigen
    Eigen::MatrixXd mat(data.size(), cols);
    for (size_t i = 0; i < data.size(); ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            mat(i, j) = data[i][j];
        }
    }
    file.close();
    return mat;
}

void eigenToCSV(const std::string& filename, const Eigen::MatrixXd& mat, char delimiter)
{

    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not create file: " + filename);
    }

    for (int i = 0; i < mat.rows(); ++i)
    {
        for (int j = 0; j < mat.cols(); ++j)
        {
            file << mat(i, j);
            if (j < mat.cols() - 1)
            {
                file << delimiter;
            }
        }
        file << "\n";
    }
    file.close();
}


