/* Ilya Pavlov st129535@student.spbu.ru
	02.Gauss_Task
*/
#ifndef GAUSS_SOLVER_H
#define GAUSS_SOLVER_H
#include "libraries.h"


void TriangleForm(Eigen::MatrixXd& matrix);
void BackAlgorithm(Eigen::MatrixXd &matrix);
Eigen::MatrixXd Gauss(Eigen::MatrixXd &matrix);
Eigen::MatrixXd csvToEigen(const std::string& filename, char delimiter = ',');
void eigenToCSV(const std::string& filename, const Eigen::MatrixXd& mat, char delimiter = ',');
int GaussSolver(const std::string& filename, char delimiter= ',');

#endif
