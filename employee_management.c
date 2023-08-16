#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee
{
    int Employee_ID;
    char Employee_Name[50];
    int Salary;
    char Department[50];
};

void addEmployee()
{
    struct Employee new_employee;
    printf("Enter Employee ID: ");
   if(scanf("%d", &new_employee.Employee_ID) != 1){
    printf("Invalid Input\n");
    while(getchar()!='\n')
    return;

   }
    printf("Enter Employee Name: ");
    scanf("%s", new_employee.Employee_Name);
    printf("Enter Employee Salary: ");
    scanf("%d", &new_employee.Salary);
    printf("Enter Department Name: ");
    scanf("%s", new_employee.Department);

    FILE *file = fopen("Employee.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%d %s %d %s\n", new_employee.Employee_ID,
            new_employee.Employee_Name, new_employee.Salary,
            new_employee.Department);
    fclose(file);
}

void listEmployee()
{
    FILE *file = fopen("Employee.txt", "r");
    if (file == NULL)
    {
        printf("No Employee available.\n");
        return;
    }
    int count = 0;
    struct Employee Employee;
    while (fscanf(file, "%d %s %d %s", &Employee.Employee_ID,
                  Employee.Employee_Name, &Employee.Salary, Employee.Department) != EOF)
    {
        printf("ID: %d, Name: %s,Salary: %d, Dept: %s\n",
               Employee.Employee_ID, Employee.Employee_Name, Employee.Salary,
               Employee.Department);
        count++;
    }
    if (count == 0)
    {
        printf("No Employee available");
    }
    fclose(file);
}

void deleteEmployee(int id)
{
    FILE *file = fopen("Employee.txt", "r");
    if (file == NULL)
    {
        printf("No Employee available.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    struct Employee Employee;
    while (fscanf(file, "%d %s %d %s", &Employee.Employee_ID,
                  Employee.Employee_Name, &Employee.Salary, Employee.Department) != EOF)
    {
        if (Employee.Employee_ID != id)
        {
            fprintf(tempFile, "%d %s %d %s\n", Employee.Employee_ID,
                    Employee.Employee_Name, Employee.Salary, Employee.Department);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("Employee.txt");
    rename("temp.txt", "Employee.txt");
}

void updateEmployee(int id)
{
    FILE *file = fopen("Employee.txt", "r");
    if (file == NULL)
    {
        printf("No Employee available.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    struct Employee employee;
    while (fscanf(file, "%d %s %d %s", &employee.Employee_ID,
                  employee.Employee_Name, &employee.Salary, employee.Department) != EOF)
    {
        if (employee.Employee_ID == id)
        {
            printf("Enter new Employee Name: ");
            scanf("%s", employee.Employee_Name);

            printf("Enter new Salary Of Employee: ");
            scanf("%d", &employee.Salary);

            printf("Enter new Department of Employee: ");
            scanf("%s", employee.Department);
        }
        fprintf(tempFile, "%d %s %d %s\n", employee.Employee_ID,
                employee.Employee_Name, employee.Salary, employee.Department);
    }

    fclose(file);
    fclose(tempFile);

    remove("Employee.txt");
    rename("temp.txt", "Employee.txt");
    
}

int main()
{
    int choice, id;

    while (1)
    {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. List Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Update Employee Details\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addEmployee();
            break;
        case 2:
            listEmployee();
            break;
        case 3:
            printf("Enter Employee ID to delete: ");
            scanf("%d", &id);
            deleteEmployee(id);
            break;
        case 4:
            printf("Enter Employee ID to update: ");
            scanf("%d", &id);
            updateEmployee(id);
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
