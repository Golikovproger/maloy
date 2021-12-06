// Practical_work_6_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Method.h"
#include "Options.h"
#include "Task.h"
#include "SLE.h"
#include <time.h>

//const Matrix get_L(const Matrix any);
//const Matrix get_U(const Matrix any);
//const double get_norm(const Matrix any);
//const Matrix yakobi(const Matrix A, const Matrix b, const double eps = 10e-60);
//const Matrix zeidel(const Matrix A, const Matrix b, const double eps = 10e-60);

enum class ERROR
{
    begin,
    EMPTY = begin,
    MAIN_CRITERION = 1,
    SIZE_CHECK = 2,

    end,
};

//ERROR& operator++(ERROR& e)
//{
//    e = ERROR(static_cast<int>(e) + 1);
//    return e;
//}

mtd& operator++(mtd& e)
{
    e = mtd(static_cast<int>(e) + 1);
    return e;
}

int main()
{
    std::string fullway2data = "E:\\input.txt";
    //const Matrix& A = read(fullway2data);
    Matrix A = read(fullway2data);

    double sum_diag = 0; 
    ERROR flag = ERROR::EMPTY;

    for (size_t i = 0; i < A.get_rSize(); i++)
        for (size_t j = 0; j < A.get_cSize(); j++)
            if (i != j)
                sum_diag += A(i, j);

    for (size_t i = 0; i < A.get_rSize(); i++)
        if (A(i, i) < sum_diag)
            flag = ERROR::MAIN_CRITERION;

    if (flag != ERROR::EMPTY)
    {
        std::string report;
        switch (flag) 
        {
            case(ERROR::MAIN_CRITERION):
                report = "ERROR. THE VALUE OF THE DIAGONAL ELEMENT OF THE MATRIX \nMUST BE GREATER THAN OR EQUAL TO \nTHE SUM OF THE NON-DIAGONAL ELEMENTS.";
                break;
            case(ERROR::SIZE_CHECK):
                break;
        }

        std::cout << report;
        return 0;
    }


    Matrix x_exist(A.get_cSize(), 1);

    // filling x_exist with values from 1 to the number of columns of matrix A
    unsigned int temp = 0;
    for (size_t i = 0; i < x_exist.get_rSize(); i++)
    {
        temp = i + 1;
        x_exist(i, 0) = temp;
    }

    // setting the values of the vector of the right part
    //const Matrix& b = A * x_exist;
    Matrix b = A * x_exist;



    tsk a = tsk::A;
    struct 
    Task task(A, b);
   
    /*mtd aboba = mtd::JACOBI;*/
    for (mtd i = mtd::begin; i != mtd::end; ++i)
    {
       
        SLE sle(task, Method(i));
        clock_t start = clock();
        print(sle.solution());
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        printf("The time: %f seconds\n", seconds);
    }

    return 0;
}

