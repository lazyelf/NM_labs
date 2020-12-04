#include <iostream>
#include <cmath>
using namespace std;

#define BEGIN 2
#define END 4
#define ITERATION 10

class Main
{
public:
    int chord_iterator;
    int tangents_iterator;
    int cutting_iterator;

    double chord_method(double begin, double end, double epsilon)
    {
        chord_iterator = 0;
        while (abs(end - begin) > epsilon)
        {
            end = begin - (begin - end) * func(begin) / (func(begin) - func(end));
            begin = end - (end - begin) * func(end) / (func(end) - func(begin));
            ++chord_iterator;
        }

        return end;
    }

    double tangents_method(double begin, double end, double epsilon)
    {
        tangents_iterator = 0;
        double x;
        if (func(begin) * diff_func(begin) > 0)
            x = begin;
        else
            x = end;
        do
        {
            x = x - func(x) / diff_func(x);
            ++tangents_iterator;
        } while (abs(func(x)) >= epsilon);
        return x;
    }

    double cutting_method(double x, double epsilon)
    {
        cutting_iterator = 0;
        double tmp = x + 2 * epsilon;
        while (abs(x - tmp) > epsilon)
        { //|x[n]-x[n+1]|<eps
            tmp = x;
            x = x - func(x) / diff_func(x);
            ++cutting_iterator;
        }
        return x;
    }

    double func(double x)
    {
        return log10(x) - tan(x);
    }

    double diff_func(double x)
    {
        return 1 / (log(10) * x) - 1 / (cos(x) * cos(x));
    }

    void print_func()
    {
        cout << "\tlg(x) - tg(x) = 0\n";
    }
};

int main()
{
    cout << "Михайлова Вікторія КН-201\nЛабораторна робота №4\n\n";
    double elipson = 0.1;
    for (int i = 0; i < ITERATION; ++i)
    {
        Main m;
        m.print_func();
        cout << "\n\tEpsilon е = " << elipson << '\n';
        cout << "\t__________________________\n";
        cout << "\t| Метод хорд\t\t |\n";
        cout << "\t| x = " << m.chord_method(BEGIN, END, elipson) << "\t\t |\n";
        cout << "\t| Кількість ітерацій = " << m.chord_iterator << " |\n";
        cout << "\t__________________________\n";
        cout << "\t| Метод дотичних\t |\n";
        cout << "\t| x = " << m.tangents_method(BEGIN, END, elipson) << "\t\t |\n";
        cout << "\t| Кількість ітерацій = " << m.tangents_iterator << " |\n";
        cout << "\t__________________________\n";
        cout << "\t| Метод січних\t\t |\n";
        cout << "\t| x = " << m.cutting_method(BEGIN, elipson) << "\t\t |\n";
        cout << "\t| Кількість ітерацій = " << m.cutting_iterator << " |\n";
        cout << "\t__________________________\n\n\n\n";
        elipson /= 10;
    }
}