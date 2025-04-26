/* Ilya Pavlov st129535@student.spbu.ru
	02.Gauss_Task
*/
#include "gauss_solver.h"
#include "libraries.h"

//for input you give matrix n*(n+1) - matrix n*n + column with answers
void TriangleForm(Eigen::MatrixXd& matrix)
{
    int row_count = matrix.rows();
    int col_count = matrix.cols();
    int k = 0;

    // We can only eliminate up to min(rows, cols-1) columns
    int max_pivots = std::min(row_count, col_count-1);

    for (int i = 0; i < max_pivots; ++i)
    {
        Eigen::VectorXd coli = matrix.col(i);

        int max_row = i;
        for (int j = i + 1; j < row_count; ++j)
        {
            if (std::abs(coli(j)) > std::abs(coli(max_row)))
            {
                max_row = j;
            }
        }

        if ( coli(max_row) == 0 )
        {
            k+=1;
            continue;
        }

        if (max_row != i) //swaping rows so that matrix will become triangular
        {
            matrix.row(i).swap(matrix.row(max_row));
        }

        double ai = matrix(i,k);
        matrix.row(i)/=ai;
        for (int c = i+1; c < row_count; ++c)
        {
            matrix.row(c) -= matrix(c,i) * matrix.row(i);
        }
        k+=1;
    }
}

void BackAlgorithm(Eigen::MatrixXd &matrix)
{
    int row_count = matrix.rows();
    int col_count = matrix.cols();

    // Start from the last pivot row and work upwards
    for (int i = row_count-1; i >= 0; --i)
    {
        // Find the pivot column (first non-zero element in the row)
        int pivot_col = -1;
        for (int j = 0; j < col_count-1; ++j)
        {
            if (matrix(i, j) != 0)
            {
                pivot_col = j;
                break;
            }
        }

        if (pivot_col == -1) continue; // skip zero rows

        // Eliminate above the pivot
        for (int k = i-1; k >= 0; --k)
        {
            double factor = matrix(k, pivot_col);
            matrix.row(k) -= factor * matrix.row(i);
        }
    }
}

Eigen::MatrixXd Gauss(Eigen::MatrixXd &matrix)
{
    TriangleForm(matrix);
    BackAlgorithm(matrix);
    //checks for all coeficents = zeros
    bool finite = true;
    for (int i = 0; i < matrix.rows(); ++i)
    {
        if ((matrix.cols() - 1 - std::count(matrix.row(i).begin(), matrix.row(i).end()-1, 0) < 1) and (matrix(i,matrix.cols()-1) != 0))
        {
            std::cerr<<"No solutions, inconsistent system"<<std::endl;
            return matrix;
        }
        else if (matrix.cols() - 1 - std::count(matrix.row(i).begin(), matrix.row(i).end()-1, 0) > 1)
        {
            finite = false;
        }

    }
    if (finite)
    {
        std::cout<<"One solution"<<std::endl;
        return matrix;
    }
    else
    {
        std::cerr<<"Infinite solutions"<<std::endl;
        return matrix;
    }

}

int GaussSolver(const std::string& filename, char delimiter)
{
    try
    {
        Eigen::MatrixXd mat = csvToEigen(filename);
        std::cout<<mat<<std::endl;
        Gauss(mat);
        std::cout<<mat<<std::endl;
        eigenToCSV("GaussSolver.csv", mat, delimiter);
        return 0;

    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
};










