
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int emp_id;

    enum { FULL_TIME, CONTRACT } type;

    union {
        float salary;

        struct {
            float hourly_rate;
            int hours_worked;
        } contract_info;

    } pay;

} Employee;

int main() {
    Employee *emp;
    int n, i;
    float total_bill = 0, pay;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }

    emp = (Employee *)malloc(n * sizeof(Employee));

    if (emp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter employee name and ID: ");
        scanf("%19s %d", (emp + i)->name,
              &(emp + i)->emp_id);

        printf("Enter type (0-Full-time, 1-Contract): ");
        scanf("%d", (int *)&(emp + i)->type);

        if ((emp + i)->type == FULL_TIME) {
            printf("Enter monthly salary: ");
            scanf("%f", &(emp + i)->pay.salary);
        }
        else if ((emp + i)->type == CONTRACT) {
            printf("Enter hourly rate and hours worked: ");
            scanf("%f %d",
                &(emp + i)->pay.contract_info.hourly_rate,
                &(emp + i)->pay.contract_info.hours_worked);
        }
        else {
            printf("Invalid employee type.\n");
            free(emp);
            return 1;
        }
    }

    printf("\n----- EMPLOYEE PAYSLIPS -----\n");

    for (i = 0; i < n; i++) {
        if ((emp + i)->type == FULL_TIME) {
            pay = (emp + i)->pay.salary;
            printf("\nName: %s\n", (emp + i)->name);
            printf("Employee ID: %d\n", (emp + i)->emp_id);
            printf("Type: Full-time\n");
            printf("Total Pay: %.2f\n", pay);
        }
        else {
            pay = (emp + i)->pay.contract_info.hourly_rate *
                  (emp + i)->pay.contract_info.hours_worked;

            printf("\nName: %s\n", (emp + i)->name);
            printf("Employee ID: %d\n", (emp + i)->emp_id);
            printf("Type: Contract\n");
            printf("Total Pay: %.2f\n", pay);
        }

        total_bill += pay;
    }

    printf("\nTotal Salary Bill: %.2f\n", total_bill);

    free(emp);
    return 0;
}

