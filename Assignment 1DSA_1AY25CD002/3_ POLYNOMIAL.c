#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];
} polynomial;

/* Function to add two polynomials */

polynomial add(polynomial a, polynomial b) {
    polynomial result;
    int exp, i;

    result.degree = (a.degree > b.degree) ?
                     a.degree : b.degree;
-
    for (i = 0; i <= result.degree; i++) {
        exp = result.degree - i;

        result.coef[i] = 0;

        if (exp <= a.degree)
            result.coef[i] += a.coef[a.degree - exp];

        if (exp <= b.degree)
            result.coef[i] += b.coef[b.degree - exp];
    }

    return result;
}

/* Function to display a polynomial */
void display(polynomial p) {
    int i, exp, printed = 0;
    float c;

    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];
        exp = p.degree - i;

        if (c == 0)
            continue;

        if (printed > 0) {
            if (c > 0)
                printf(" + ");
            else
                printf(" - ");
        } else if (c < 0) {
            printf("-");
        }

        if (c < 0)
            c = -c;

        if (exp == 0 || c != 1)
            printf("%.2g", c);

        if (exp > 0) {
            printf("x");
            if (exp > 1)
                printf("^%d", exp);
        }

        printed++;
    }

    if (printed == 0)
        printf("0");

    printf("\n");
}

/* Function to read a polynomial */
polynomial readPolynomial(void) {
    polynomial p;
    int i;

    printf("Enter degree: ");
    scanf("%d", &p.degree);

    if (p.degree < 0 || p.degree > 100) {
        printf("Invalid degree.\n");
        p.degree = -1;
        return p;
    }

    printf("Enter coefficients from highest degree to constant:\n");

    for (i = 0; i <= p.degree; i++) {
        scanf("%f", &p.coef[i]);
    }

    return p;
}

int main() {
    polynomial a, b, sum;

    printf("First polynomial\n");
    a = readPolynomial();

    if (a.degree == -1)
        return 1;

    printf("Second polynomial\n");
    b = readPolynomial();

    if (b.degree == -1)
        return 1;

    sum = add(a, b);

    printf("\nA(x) = ");
    display(a);

    printf("B(x) = ");
    display(b);

    printf("Sum = ");
    display(sum);

    return 0;
}

