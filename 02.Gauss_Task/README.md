# Gauss_Solver
## Author
Павлов Илья Олегович, группа 24.Б81-мм
## Contacts
st129535@student.spbu.ru
## Description
Solver of a sustem of linear equations
## Build
make run
## Run
csv file must include extended matrix - matrix of coefficients with column of answers
From terminal: enter filename then enter a separator
As a function: GaussSolver([filename], [separator](',' - default))
returns a csv file with extended matrix.In process the function turns given matrix 1)diagonal then to 2)as close as possible identity matrix.
Matrix is as close to identity matrix with answer in the right column.
## Clean
make clean
make cleanall
