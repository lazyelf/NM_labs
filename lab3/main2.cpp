#include <cmath>
#include <iostream>
#include <fstream>

#define RANK 4
#define STEPS_AMOUNT 10
#define STEP 10
double matrix[RANK][RANK];
double vector[RANK];

void print_task()
{
    using namespace std;
    cout << "System of equations\n";
    for (int i = 0; i < RANK; ++i)
    {
        string iteration = " x₁ ";
        for (int j = 0; j < RANK; ++j)
        {
            cout.width(4);
            if (j)
                cout << showpos;
            cout << matrix[i][j] << iteration;
            ++(iteration[4]);
        }
        cout << noshowpos;
        cout << "= " << vector[i] << '\n';
    }
    cout << '\n';
}

void init_data(double eps)
{
    matrix[0][0] = 1.2;
    matrix[0][1] = 2;
    matrix[0][2] = 3;
    matrix[0][3] = -2;

    matrix[1][0] = 2;
    matrix[1][1] = -0.2;
    matrix[1][2] = -2;
    matrix[1][3] = -3;

    matrix[2][0] = 3;
    matrix[2][1] = 2;
    matrix[2][2] = -eps;
    matrix[2][3] = 1.8;

    matrix[3][0] = 2;
    matrix[3][1] = -3;
    matrix[3][2] = 2;
    matrix[3][3] = 1;

    vector[0] = 6;
    vector[1] = 6.4;
    vector[2] = 0.8;
    vector[3] = -12.8;
}

void allocate_memory(double ***entr_mtrx, double **b, double **solution)
{
    *entr_mtrx = new double *[RANK];
    for (int i = 0; i < RANK; ++i)
    {
        (*entr_mtrx)[i] = new double[RANK];
    }
    *b = new double[RANK];
    *solution = new double[RANK];
}

void translate_data(double **entr_mtrx, double *b, double *solution)
{
    for (int i = 0; i < RANK; ++i)
    {
        for (int j = 0; j < RANK; ++j)
            entr_mtrx[i][j] = matrix[i][j];
        b[i] = vector[i];
    }
}

void print_matrix(double **mtrx, double *vect, std::string message)
{
    using namespace std;
    cout << message;
    for (int i = 0; i < RANK; ++i)
    {
        for (int j = 0; j < RANK; ++j)
        {
            cout.width(10);
            cout.precision(3);
            cout << mtrx[i][j];
        }
        cout << " |";
        cout.width(8);
        cout << vect[i] << '\n';
    }
    cout << '\n';
}

void find_solution(double **entr_mtrx, double *b, double *solution)
{
    for (int k = 0; k < RANK; k++)
    {
        double lead = entr_mtrx[k][k];
        for (int j = k; j < RANK; j++)
            entr_mtrx[k][j] /= lead;
        b[k] /= lead; 

        for (int i = 0; i < RANK; i++)
        {
            double a_div_lead = entr_mtrx[i][k] / entr_mtrx[k][k];
            if (i != k)
            {
                for (int j = k; j < RANK; j++)
                    entr_mtrx[i][j] -= entr_mtrx[k][j] * a_div_lead;
                b[i] -= b[k] * a_div_lead;
            }
        }
        std::string message = "\t" + std::to_string(k + 1) + " column processing\n";
        message += k + 1;
        print_matrix(entr_mtrx, b, message);
    }

    for(int i = 0; i < RANK; ++i)
    {
        solution[i] = b[i];
    }
}

void print_solution(double *solution)
{
    std::cout << "System solutions: " << '\n';
    std::string iteration = "x₁";
    for (int i = 0; i < RANK; ++i)
    {
        std::cout << iteration << " = ";
        std::cout.width(5);
        std::cout.precision(3);
        std::cout << solution[i] << " " << '\n';
        ++(iteration[3]);
    }
}

double find_error(double *solution)
{
    double results[RANK] = {0};
    double errors[RANK];
    for (int i = 0; i < RANK; ++i)
    {
        for (int j = 0; j < RANK; ++j)
        {
            results[i] += matrix[i][j] * solution[j];
        }
        errors[i] = results[i] - vector[i];
        if (errors[i] < 0)
            errors[i] = -errors[i];
    }
    double error = 0;
    for (int i = 0; i < RANK; ++i)
    {
        error += errors[i];
    }
    return error / RANK;
}

void print_error(double error)
{
    std::cout << "Error is " << error << "\n"
              << "--------------------------------------------------------\n\n";
}

void delete_memory(double **entr_mtrx, double *b, double *solution)
{
    for (int i = 0; i < RANK; ++i)
        delete[] entr_mtrx[i];
    delete[] entr_mtrx;
    delete[] b;
    delete[] solution;
}

int main(int argc, char *argv[])
{
    std::cout << "Mихайлова Вікторія КН-201\n";
    if (argc < 2)
    {
        std::cout << "Enter result file name.\n";
        return 0;
    }
    std::string file_name = argv[1];
    std::ofstream file(file_name);

    double **entr_mtrx;
    double *b, *solution;
    double eps = 0.1;

    for (int i = 0; i < STEPS_AMOUNT; ++i)
    {
        allocate_memory(&entr_mtrx, &b, &solution);
        init_data(eps);
        print_task();
        translate_data(entr_mtrx, b, solution);

        find_solution(entr_mtrx, b, solution);
        print_solution(solution);

        double error = find_error(solution);
        print_error(error);

        delete_memory(entr_mtrx, b, solution);

        file << eps << ' ' << error << '\n';

        eps /= STEP;
    }
    return 0;
}