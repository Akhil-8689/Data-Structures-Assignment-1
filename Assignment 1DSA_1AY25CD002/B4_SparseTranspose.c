#include <stdio.h>

typedef struct {
    int row, col, value;
} term;

void fast_transpose(term a[], term b[]) {
    int row_terms[101] = {0};
    int starting_pos[101] = {0};
    int i, col, position;
    int cols = a[0].col;
    int terms = a[0].value;

    b[0].row = cols;
    b[0].col = a[0].row;
    b[0].value = terms;

    /* Count non-zero elements in each column */
    for (i = 1; i <= terms; i++)
        row_terms[a[i].col]++;

    /* Calculate starting positions */
    starting_pos[0] = 1;

    for (i = 1; i < cols; i++)
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];

    /* Print arrays before starting positions are updated */
    printf("\nrow_terms[]: ");
    for (i = 0; i < cols; i++)
        printf("%d ", row_terms[i]);

    printf("\nstarting_pos[]: ");
    for (i = 0; i < cols; i++)
        printf("%d ", starting_pos[i]);
    printf("\n");

    /* Perform fast transpose */
    for (i = 1; i <= terms; i++) {
        col = a[i].col;
        position = starting_pos[col]++;

        b[position].row = a[i].col;
        b[position].col = a[i].row;
        b[position].value = a[i].value;
    }
}

void display(term a[]) {
    int i;

    printf("Row\tColumn\tValue\n");

    for (i = 0; i <= a[0].value; i++)
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
}

int main() {
    term a[10001], b[10001];
    int matrix[100][100];
    int rows, cols, i, j, k = 1;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0 ||
        rows > 100 || cols > 100) {
        printf("Invalid matrix size.\n");
        return 1;
    }

    printf("Enter matrix elements:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++)
            scanf("%d", &matrix[i][j]);
    }

    /* Store header information */
    a[0].row = rows;
    a[0].col = cols;
    a[0].value = 0;

    /* Store only non-zero elements */
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                a[k].row = i;
                a[k].col = j;
                a[k].value = matrix[i][j];
                k++;
            }
        }
    }

    a[0].value = k - 1;

    printf("\nOriginal matrix triples:\n");
    display(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples:\n");
    display(b);

    printf("\nTransposed triples are in row-major order.\n");

    return 0;
}
			
