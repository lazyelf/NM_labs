#include <iostream>
#include <cmath>

#define BEGIN 0.752
#define END 0.82
#define TASK 0.775
#define START_INTERVAL_AMOUNT 5
#define INTERVAL_STEP 5

double eitken_method(double *x, double *f, double X, int n)
{
    double **Y = new double *[n];
    for (int i = 0; i < n; ++i)
    {
        Y[i] = new double[n];
    }
    for (int j = 0; j < n; j++)
    {
        Y[j][j] = f[j];
        for (int i = j - 1; i >= 0; i--)
        {
            Y[i][j] = 1 / (x[j] - x[i]) * ((X - x[i]) * Y[i + 1][j] - (X - x[j]) * Y[i][j - 1]);
        }
    }
    double result = Y[0][n - 1];
    for (int i = 0; i < n; ++i)
    {
        delete[] Y[i];
    }
    delete[] Y;
    return result;
}

void print_task()
{
    using namespace std;
    cout << "Author: Mykhailova Viktoriia CS-201\n"
         << "Interval for Eitken method x ∈ [0.752; 0.820]\n"
         << "Task: find cos(" << TASK << ") using Eitken method\n";
}

void print_result(int interval_amount, double step, double eitken)
{
    using namespace std;
    cout << "\n---------------------------------"
         << "\n| Amount of intervals: " << interval_amount << "  \t|"
         << "\n| Step: h = " << step << "\t\t|"
         << "\n| Eitken method result:" << "\t\t|"
         << "\n|\tcos(" << TASK << ") = " << eitken << "\t|"
         << "\n| Elipson is: ε = " << fabs(cos(TASK) - eitken) << "\t|"
         << "\n---------------------------------\n";
}

int main()
{
    print_task();
    int interval_amount = START_INTERVAL_AMOUNT;
    for (int iterations = 0; iterations < 10; ++iterations)
    {
        double step = (END - BEGIN) / (interval_amount - 1);
        step = floor(step * 10000) / 10000;
        double *X = new double[interval_amount];
        double *F = new double[interval_amount];

        X[0] = BEGIN;
        F[0] = cos(BEGIN);
        for (int i = 1; i < interval_amount; ++i)
        {
            X[i] = X[i - 1] + step;
            X[i] = floor(X[i] * 10000) / 10000;
            F[i] = cos(X[i]);
            F[i] = floor(F[i] * 10000) / 10000;
        }

        print_result(interval_amount, step, eitken_method(X, F, TASK, interval_amount));

        delete[] X;
        delete[] F;
        interval_amount += INTERVAL_STEP;
    }
}