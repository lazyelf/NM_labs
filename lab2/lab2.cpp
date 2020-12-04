#include <iostream>

using namespace std;

#define LEFT -10
#define RIGHT 10
#define STEP 1

class Methode
{
    double x;
    double value[6];

public:
    Methode(double x)
    {
        this->x = x;
        Funk(x);
        F0(x);
        F1(x);
        F2(x);
        F3(x);
        F4(x);
    }
    void set_x(double x)
    {
        this->x = x;
        Funk(x);
        F0(x);
        F1(x);
        F2(x);
        F3(x);
        F4(x);
    }

    double Funk(double x)
    {
        value[0] = x * x * x * x * x - x * x * x - 3 * x + 10;
        return value[0];
    }
    double F0(double x)
    {
        value[1] = 5 * x * x * x * x - 3 * x * x - 3;
        return value[1];
    }
    double F1(double x)
    {
        value[2] = x * x * x + 6 * x - 25;
        return value[2];
    }
    double F2(double x)
    {
        value[3] = 11 * x * x - 25 * x + 1;
        return value[3];
    }
    double F3(double x)
    {
        value[4] = -1103 * x + 1380;
        return value[4];
    }
    double F4(double x)
    {
        value[5] = 1;
        return 1;
    }
    int calculate_minuses()
    {
        int acquaintance = 0;
        for (int i = 0; i < 5; ++i)
        {
            if ((value[i] > 0) ^ (value[i + 1] > 0))
            {
                ++acquaintance;
            }
        }
        return acquaintance;
    }
    double get_value(int i)
    {
        return value[i];
    }
    void print_table_part()
    {
        for (int i = 0; i < 6; ++i)
        {
            char c;
            if (value[i])
            {
                c = value[i] > 0 ? '+' : '-';
            }
            else
                c = '0';

            printf("\t%5c|", c);
        }
        printf("\t%5d|", calculate_minuses());
    }
    void print()
    {
        puts("----------------------------------------");
        printf("x = %.2lf\n", x);
        print_Funk();
        print_F0();
        print_F1();
        print_F2();
        print_F3();
        print_F4();
    }

private:
    void print_Funk()
    {
        printf("F (x) = x⁵ - x³ - 3x + 10 = %.2lf\n", value[0]);
    }
    void print_F0()
    {
        printf("f₀(x) = 5x⁴ - 3x² - 3 = %.2lf\n", value[1]);
    }
    void print_F1()
    {
        printf("f₁(x) = x³ + 6x - 25 = %.2lf\n", value[2]);
    }
    void print_F2()
    {
        printf("f₂(x) = 11x² - 25x + 1 = %.2lf\n", value[3]);
    }
    void print_F3()
    {
        printf("f₃(x) = -1103x + 1380 = %.2lf\n", value[4]);
    }
    void print_F4()
    {
        printf("f₄(x) = 1\n");
    }
};

class Interval
{
    double left;
    double right;

public:
    Interval(double left, double right)
    {
        this->left = left;
        this->right = right;
    }
    void set_next_forvard()
    {
        left = right;
        right += STEP;
    }
    void set_next_backvard()
    {
        right = left;
        left -= STEP;
    }
    double get_left()
    {
        return left;
    }
    double get_right()
    {
        return right;
    }
    void show_acquaintance_table(Methode *left, Methode *right)
    {
        puts("----------------------------------------------------------------------");
        printf("|%7c|\t F(x)|\tF₀(x)|\tF₁(x)|\tF₂(x)|\tF₃(x)|\tF₄(x)|\t    N|\n", 'x');
        printf("|%7.2lf|", this->left);
        left->print_table_part();
        printf("\n|%7.2lf|", this->right);
        right->print_table_part();
        puts("");
        puts("----------------------------------------------------------------------");
    }

private:
};

int main(void)
{
    Interval *interval = new Interval(LEFT, LEFT + 1);
    Methode *left = new Methode(interval->get_left());
    Methode *right = new Methode(interval->get_right());
    puts("Корінь/-ені рівняння x⁵ - x³ - 3x + 10 = 0"
         "\nзнаходяться у заданому інтервалі/-ах:");
    for (int i = 0; i < RIGHT - LEFT; ++i)
    {
        left->set_x(interval->get_left());
        right->set_x(interval->get_right());
        interval->show_acquaintance_table(left, right);
        if (right->calculate_minuses() - left->calculate_minuses())
        {
            printf("\n\tІнтервал: (%.2lf; %.2lf)\n", interval->get_left(), interval->get_right());
            left->print();
            right->print();
            //interval->show_acquaintance_table(left, right);
        }
        interval->set_next_forvard();
    }
    delete interval;
    delete left;
    delete right;
    return 0;
}