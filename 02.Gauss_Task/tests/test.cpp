/* Ilya Pavlov st129535@student.spbu.ru
   02.Gauss_Task - Google Tests
*/
#include "gauss_solver.h"
#include "libraries.h"
#include <gtest/gtest.h>
#include <random>

// Тест для проверки чтения и записи CSV
TEST(CSVTest, ReadWrite)
{
    // Создаем тестовую матрицу
    Eigen::MatrixXd test_mat(3, 4);
    test_mat << 1, 2, 3, 4,
             5, 6, 7, 8,
             9, 10, 11, 12;

    // Записываем в файл
    eigenToCSV("test_csv.csv", test_mat, ',');

    // Читаем обратно
    Eigen::MatrixXd read_mat = csvToEigen("test_csv.csv", ',');

    // Проверяем совпадение
    EXPECT_EQ(test_mat.rows(), read_mat.rows());
    EXPECT_EQ(test_mat.cols(), read_mat.cols());
    EXPECT_TRUE(test_mat.isApprox(read_mat));
}

// Тест для проверки решения простой СЛАУ с одним решением
TEST(GaussTest, SingleSolution)
{
    Eigen::MatrixXd mat(3, 4);
    mat << 1, 2, 3, 6,
        0, 1, 2, 4,
        0, 0, 1, 1;

    Eigen::MatrixXd result = Gauss(mat);

    // Проверяем, что последний столбец содержит решение [1, 2, 1]
    EXPECT_NEAR(result(0, 3), -1.0, 1e-9);
    EXPECT_NEAR(result(1, 3), 2.0, 1e-9);
    EXPECT_NEAR(result(2, 3), 1.0, 1e-9);
}

// Тест для проверки случая бесконечного множества решений
TEST(GaussTest, InfiniteSolutions)
{
    Eigen::MatrixXd mat(3, 4);
    mat << 1, 2, 3, 6,
        0, 1, 2, 4,
        0, 0, 0, 0;

    Eigen::MatrixXd result = Gauss(mat);

    // Проверяем наличие нулевой строки
    bool has_zero_row = false;
    for (int i = 0; i < result.rows(); ++i)
    {
        if (result.row(i).head(result.cols()-1).isZero() &&
                std::abs(result(i, result.cols()-1)) < 1e-9)
        {
            has_zero_row = true;
            break;
        }
    }
    EXPECT_TRUE(has_zero_row);
}

// Тест для проверки случая отсутствия решений
TEST(GaussTest, NoSolution)
{
    Eigen::MatrixXd mat(3, 4);
    mat << 1, 2, 3, 6,
        0, 1, 2, 4,
        0, 0, 0, 1;

    Eigen::MatrixXd result = Gauss(mat);

    // Проверяем наличие строки вида [0 ... 0 | b], где b != 0
    bool has_inconsistent_row = false;
    for (int i = 0; i < result.rows(); ++i)
    {
        if (result.row(i).head(result.cols()-1).isZero() &&
                std::abs(result(i, result.cols()-1)) > 1e-9)
        {
            has_inconsistent_row = true;
            break;
        }
    }
    EXPECT_TRUE(has_inconsistent_row);
}

// Фикстура для тестов со случайными матрицами
class RandomMatrixTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Инициализация генератора случайных чисел
        gen.seed(42);
    }

    Eigen::MatrixXd generate_random_matrix(int size)
    {
        std::uniform_real_distribution<double> dist(-10.0, 10.0);

        Eigen::MatrixXd mat(size, size + 1);
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size + 1; ++j)
            {
                mat(i, j) = dist(gen);
            }
        }
        return mat;
    }

    std::mt19937 gen;
};

// Тест для проверки решения случайных СЛАУ
TEST_F(RandomMatrixTest, RandomSystems)
{
    const int num_tests = 5;
    const int min_size = 3;

    for (int test = 0; test < num_tests; ++test)
    {
        int size = min_size + test;
        Eigen::MatrixXd mat = generate_random_matrix(size);

        // Сохраняем копию исходной системы
        Eigen::MatrixXd original = mat;

        // Решаем систему
        Eigen::MatrixXd result = Gauss(mat);

        // Проверяем, что решение удовлетворяет исходной системе (если оно существует)
        bool has_solution = true;
        for (int i = 0; i < result.rows(); ++i)
        {
            if (result.row(i).head(result.cols()-1).isZero() &&
                    std::abs(result(i, result.cols()-1)) > 1e-9)
            {
                has_solution = false;
                break;
            }
        }

        if (has_solution)
        {
            Eigen::VectorXd solution = result.col(result.cols()-1);

            // Проверяем, что Ax ≈ b
            Eigen::VectorXd b = original.leftCols(original.cols()-1) * solution;
            Eigen::VectorXd original_b = original.col(original.cols()-1);

            EXPECT_LT((b - original_b).norm(), 1e-6);
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
