#include <iostream>
#include <cmath>

#define STEP 10
#define ITERATION_AMOUNT 10

class Evaluation_system
{
    int count = 0;
    double e = 0;
    double x = 0, y = 0;

public:
    double F(double x, double y)
    {
        return sin(2 * x + y) - 1.3 * x - 0.2;
    }
    double dFdx(double x, double y)
    {
        return 2 * cos(2 * x + y) - 1.3;
    }
    double dFdy(double x, double y)
    {
        return cos(2 * x + y);
    }

    double G(double x, double y)
    {
        return x * x + 2 * y * y - 1;
    }
    double dGdx(double x)
    {
        return 2 * x;
    }
    double dGdy(double y)
    {
        return 4 * y;
    }

    void neutron_method(double eliption, double startX, double startY)
    {
        e = eliption;
        x = startX;
        y = startY;
        double xPrev, yPrev;
        do
        {
            xPrev = x;
            yPrev = y;
            x = xPrev - (F(xPrev, yPrev) * dGdy(yPrev) - dFdy(xPrev, yPrev) * G(xPrev, yPrev)) / (dFdx(xPrev, yPrev) * dGdy(yPrev) - dFdy(xPrev, yPrev) * dGdx(xPrev));
            y = yPrev - (dFdx(xPrev, yPrev) * G(xPrev, yPrev) - F(xPrev, yPrev) * dGdx(xPrev)) / (dFdx(xPrev, yPrev) * dGdy(yPrev) - dFdy(xPrev, yPrev) * dGdx(xPrev));
            count++;
        } while (fabs(x - xPrev) > e);
    }

    void print_result()
    {
        std::cout << "\n---------------------------------\n";
        std::cout << "|Result with elipson = " << e << ":\t|\n|x = " << x << "\t\t\t|\n|y = " << y << "\t\t\t|\n|Count of iterations: ";
        std::cout.width(3);
        std::cout << count << "\t|";
        std::cout << "\n---------------------------------\n\n";
    }

    std::string str_F()
    {
        return "F(x) = sin(2x + y) - 1.3x - 0.2\n";
    }
    std::string str_dFdx()
    {
        return "∂F(x)/∂x = 2cos(2x + y) - 1.3\n";
    }
    std::string str_dFdy()
    {
        return "∂F(x)/∂y = cos(2x + y)\n";
    }

    std::string str_G()
    {
        return "G(x) = x² + 2y² - 1\n";
    }
    std::string str_dGdx()
    {
        return "∂G(x)/∂x = 2x\n";
    }
    std::string str_dGdy()
    {
        return "∂G(x)/∂y = 4y\n";
    }

    void print_task()
    {
        std::cout << "\nNewton's method\n"
                  << "\tSystem of evaluation to solve:\n\t"
                  << str_F() << '\t' << str_G();
        std::cout << "\nCalculated partial derivatives:\n"
                  << str_dFdx()
                  << str_dFdy()
                  << str_dGdx()
                  << str_dGdy()
                  << '\n';
    }
};

void process(double elipson, double x, double y)
{
    Evaluation_system sys;
    sys.print_task();
    std::cout << "\nx₀ = " << x << "\ty₀ = " << y << "\n";
    double e = elipson;
    for (int i = 0; i < ITERATION_AMOUNT; ++i)
    {
        sys.neutron_method(e, x, y);
        sys.print_result();
        e /= STEP;
    }
}

int main()
{
    double e = 0.1;
    std::cout << "Author: Mykhailova Viktoriia CS-201\n\n";
    process(e, -1, 0.2);
    process(e, -1, -0.4);
    process(e, -0.5, 0.6);
    process(e, 0.5, 0.5);
}
