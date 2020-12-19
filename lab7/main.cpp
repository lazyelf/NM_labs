#include <iostream>
#include <cmath>

#define AMOUNT 11
#define BEGIN 2.0
#define END 3.0
#define ITERATIONS 100
#define EPS 0.001

void init_F(double *x, double *y)
{
    double _x = BEGIN;
    for (int i = 0; i < AMOUNT; ++i)
    {
        x[i] = _x;
        _x += 0.1;
    }
    y[0] = 20.09;
    y[1] = 21.12;
    y[2] = 22.20;
    y[3] = 23.34;
    y[4] = 24.53;
    y[5] = 25.79;
    y[6] = 27.11;
    y[7] = 28.50;
    y[8] = 29.96;
    y[9] = 31.50;
    y[10] = 33.12;
}

/*double lagrange_methode(double *x, double *y, int n, double _x)
{
    double result = 0;
    for (int i = 0; i < n; ++i)
    {
        double P = 1.0;
        for (int j = 0; j < n; ++j)
            if (j != i)
                P *= (_x - x[j]) / (x[i] - x[j]);
        result += P * y[i];
    }
    return result;
}*/

double lagrange_methode(double *x, double *y, int n, double _x)
{
    double result = 0;
    double h = x[1] - x[0];
    for (int i = 0; i < n; ++i)
    {
        double P = 1;
        for (int j = 0; j < n; ++j)
            if (i != j)
                P *= (_x - x[0] - h * j) / h / (i - j);
        result += P * y[i];
    }

    return result;
}

double rectangle_methode_l(double *x, double *y, int stage, int n)
{
    double s = 0;
    double h = (END - BEGIN) / n;
    for (int i = 0; i <= n; ++i)
    {
        s += lagrange_methode(x, y, stage, BEGIN + i * h);
    }
    return h * s;
}

double rectangle_methode_r(double *x, double *y, int stage, int n)
{
    double s = 0;
    double h = (END - BEGIN) / n;
    for (int i = 1; i <= n + 1; ++i)
    {
        s += lagrange_methode(x, y, stage, BEGIN + i * h);
    }
    return h * s;
}

double trapeze_methode(double *x, double *y, int stage, int n)
{
    double s = (lagrange_methode(x, y, stage, BEGIN) + lagrange_methode(x, y, stage, END)) / 2;
    double h = (END - BEGIN) / n;

    for (int i = 1; i < n; ++i)
    {
        s += lagrange_methode(x, y, stage, BEGIN + h * i);
    }
    return h * s;
}

double parabola_methode(double *x, double *y, int stage, int n)
{
    double h = (END - BEGIN) / n;
    double k1 = 0, k2 = 0;
    for (int i = 1; i <= n; i += 2)
    {
        k1 += lagrange_methode(x, y, stage, BEGIN + i * h);
        k2 += lagrange_methode(x, y, stage, BEGIN + (i + 1) * h);
    }
    return h / 3 * (lagrange_methode(x, y, stage, BEGIN) + 4 * k1 + 2 * k2);
}

double three_eighths_methode(double *x, double *y, int stage, int n)
{
    double s = 0;
    double h = (END - BEGIN) / n;
    for (int i = 0; i < n; i++)
    {
        if (i % 3 == 0)
            s += 2 * lagrange_methode(x, y, stage, BEGIN + i * h);
        else
            s += 3 * lagrange_methode(x, y, stage, BEGIN + i * h);
    }
    return 3 * h / 8 * (lagrange_methode(x, y, stage, BEGIN) + lagrange_methode(x, y, stage, END) + s);
}

void print_task(double *x, double *y)
{
    std::cout << "Author: Viktoriia Mykailova CS-201\n"
              << "Define integral calculating\n"
              << "\nFunction\n";
    std::cout << "----------------------------------------------------"
              << "---------------------------------------------\n|X\t|";
    for (int i = 0; i < AMOUNT; ++i)
    {
        std::cout << x[i] << "\t|";
    }
    std::cout << "\n";
    std::cout << "----------------------------------------------------"
              << "---------------------------------------------\n|Y\t|";
    for (int i = 0; i < AMOUNT; ++i)
    {
        std::cout << y[i] << "\t|";
    }
    std::cout << "\n------------------------------------------------"
              << "-------------------------------------------------\n\n";
}

int main()
{
    using namespace std;
    double *x = new double[AMOUNT];
    double *y = new double[AMOUNT];
    init_F(x, y);
    print_task(x, y);
    double result, relative, absolute;

    for (int i = 2; i < 12; ++i)
    {
        std::cout << "\n\tStage of polinom - " << i << '\n';

        result = rectangle_methode_l(x, y, i, ITERATIONS);
        absolute = EPS + fabs(result - rectangle_methode_r(x, y, i, ITERATIONS));
        relative = absolute * 100 / result;

        std::cout << "\t---------------------------------------------------------\n";
        std::cout.precision(4);
        std::cout << "\t| Rectangle method:\t\t| ∫f(x)dx = " << result << "\t|\n"
                  << "\t| Absolute methode eliption\t| Δ = " << absolute << "\t\t|\n"
                  << "\t| Relative methode eliption\t| δ = " << relative << "%\t\t|\n";

        result = trapeze_methode(x, y, i, ITERATIONS);
        absolute = EPS + fabs((rectangle_methode_l(x, y, i, ITERATIONS) + rectangle_methode_r(x, y, i, ITERATIONS)) / 2 - result);
        relative = absolute * 100 / result;

        std::cout << "\t---------------------------------------------------------\n";
        std::cout.precision(4);
        std::cout << "\t| Trapeze method:\t\t| ∫f(x)dx = " << result << "\t|\n"
                  << "\t| Absolute methode eliption\t| Δ = " << absolute << "\t\t|\n"
                  << "\t| Relative methode eliption\t| δ = " << relative << "%\t\t|\n";

        result = parabola_methode(x, y, i, ITERATIONS);
        absolute = EPS + fabs(pow((END - BEGIN), 5) * lagrange_methode(x, y, i, (BEGIN + END) / 2) / (16 * 180));
        relative = absolute * 100 / result;

        std::cout << "\t---------------------------------------------------------\n";
        std::cout.precision(4);
        std::cout << "\t| Parabola methode:\t\t| ∫f(x)dx = " << result << "\t|\n"
                  << "\t| Absolute methode eliption\t| Δ = " << absolute << "\t\t|\n"
                  << "\t| Relative methode eliption\t| δ = " << relative << "%\t\t|\n";

        result = three_eighths_methode(x, y, i, ITERATIONS);
        absolute = EPS + fabs(pow((END - BEGIN) / 3, 5) * lagrange_methode(x, y, i, (BEGIN + END) / 2) / 80);
        relative = absolute * 100 / result;

        std::cout << "\t---------------------------------------------------------\n";
        std::cout.precision(4);
        std::cout << "\t| Three-poin methode:\t\t| ∫f(x)dx = " << result << "\t|\n"
                  << "\t| Absolute methode eliption\t| Δ = " << absolute << "\t\t|\n"
                  << "\t| Relative methode eliption\t| δ = " << relative << "%\t\t|\n";
        std::cout << "\t---------------------------------------------------------\n";
    }

    delete[] x;
    delete[] y;
    return 0;
}