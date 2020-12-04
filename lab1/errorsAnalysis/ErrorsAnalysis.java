package com.lazyelf.errorsAnalysis;

public class ErrorsAnalysis {
    private final double x1;
    private final double x2;
    private final double x3;
    private double dx1, dx2, dx3;
    private double fValue;
    private double absolute, relate;

    /**Constructor that generates results for entered accuracy (Task a)*/
    public ErrorsAnalysis(double x1, int amount1, double x2, int amount2, double x3, int amount3) {
        this.x1 = x1;
        this.x2 = x2;
        this.x3 = x3;

        calculateErrors(amount1, amount2, amount3);
    }

    /**Constructor that generates results for Δ = 20∙10^(-3)  (Task b)*/
    public ErrorsAnalysis(double x1, double x2, double x3, double dx) {
        this.x1 = x1;
        this.x2 = x2;
        this.x3 = x3;
        this.dx1 = this.dx2 = this.dx3 = dx;

        calculateErrors();
    }

    public void calculateFValue() {
        //11x^2 + 9y^2 + 9z^2 + 9*x*y - 7y - 10atan(z - y);
        fValue = 11 * x1 * x1 + 9 * x2 * x2 + 9 * x3 * x3 + 9 * x1 * x3 - 7 * x2 - 10 * Math.atan(x3 - x2);
    }

    /**Method that returns absolute error of argument with entered number of exact digits*/
    private double calculateD(double x, int amount) {
        int senior = 0;
        double cpy = x;

        //Make positive
        if (cpy < 0) cpy = -cpy;

        //Different ways to sear senior digit for numbers > 1 and numbers < 1
        if (cpy > 1) {
            while ((int) cpy > 0) {
                senior = (int) cpy;
                cpy /= 10;
            }
        } else {
            while ((int) cpy == 0) {
                cpy *= 10;
                senior = (int) cpy;
            }
        }
        double multiplier = 1;
        if (amount != 1)
            multiplier = 0.1;
        for (int i = 1; i < amount; ++i) {
            multiplier *= multiplier;
        }

        //Make positive
        if (cpy < 0) cpy = -cpy;
        return (1 / (double) senior) * multiplier * cpy;
    }

    private void calculateAbsolute() {
        //22x + 9y - derivative of x
        absolute = (22 * x1 + 9 * x3) * dx1;
        double optimisation = 10 / ((-x2 + x3) * (-x2 + x3) + 1);
        //9x + 18y - 7 + 10 / ((-y + z)^2 + 1) - derivative of y
        absolute += (18 * x2 - 7 + optimisation) * dx2;
        //18z - 10 / ((-y + z)^2 + 1) - derivative of z
        absolute += (18 * x3 + 9 * x1 - optimisation) * dx3;

        //return positive value
        if (absolute < 0) {
            absolute = -absolute;
        }
    }

    private void calculateRelate() {
        relate = Math.abs(absolute) / fValue;
    }

    private void calculateErrors() {
        calculateFValue();
        calculateAbsolute();
        calculateRelate();
    }

    private void calculateErrors(int amount1, int amount2, int amount3) {
        dx1 = calculateD(x1, amount1);
        dx2 = calculateD(x2, amount2);
        dx3 = calculateD(x3, amount3);

        calculateErrors();
    }

    public double getFValue() {
        return fValue;
    }

    public double getAbsolute() {
        return absolute;
    }

    public double getRelate() {
        return relate;
    }
}
