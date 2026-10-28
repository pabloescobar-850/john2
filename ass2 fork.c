//ass2 fork
//2. Process Management (CO2)
//Process control system calls: The demonstration of FORK and WAIT system calls along with
//zombie and orphan states. Implement the C program in which main program accepts the integers
//to be sorted. Main program uses the FORK system call to create a new process called a child
//process. Parent process sorts the integers using sorting algorithm and waits for child process
//using WAIT system call to sort the integers using any sorting algorithm. Demonstrate zombie and


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Bubble Sort - Used by Parent
void bubbleSort(int a[], int n)
{
    int temp;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

// Selection Sort - Used by Child
void selectionSort(int a[], int n)
{
    int temp, min;

    for (int i = 0; i < n - 1; i++)
    {
        min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[min])
                min = j;
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

// Function to display array
void display(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main()
{
    int a[100], n, choice;
    pid_t pid;

    // Input integers
    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n < 1 || n > 100)
    {
        printf("Invalid number of elements.\n");
        return 1;
    }

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // Display menu
    printf("\n1. Fork and Wait");
    printf("\n2. Zombie Process");
    printf("\n3. Orphan Process");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }

    // METHOD 1: FORK AND WAIT
    if (choice == 1)
    {
        if (pid == 0)
        {
            // Child process sorts using Selection Sort
            printf("\nChild Process ID: %d\n", getpid());

            selectionSort(a, n);

            printf("Child Sorted Array: ");
            display(a, n);

            exit(0);
        }
        else
        {
            // Parent sorts using Bubble Sort
            printf("\nParent Process ID: %d\n", getpid());

            bubbleSort(a, n);

            printf("Parent Sorted Array: ");
            display(a, n);

            // Parent waits for child to finish
            wait(NULL);

            printf("Child process completed.\n");
        }
    }

    // METHOD 2: ZOMBIE PROCESS
    else if (choice == 2)
    {
        if (pid == 0)
        {
            // Child finishes immediately
            printf("\nChild Process ID: %d\n", getpid());
            printf("Child process completed.\n");

            exit(0);
        }
        else
        {
            // Parent does not call wait immediately
            printf("\nParent Process ID: %d\n", getpid());
            printf("Child becomes zombie for 15 seconds.\n");

            sleep(15);

            // Parent collects child's exit status
            wait(NULL);

            printf("Zombie process cleared.\n");
        }
    }

    // METHOD 3: ORPHAN PROCESS
    else if (choice == 3)
    {
        if (pid == 0)
        {
            // Child waits while parent exits
            sleep(5);

            printf("\nChild Process ID: %d\n", getpid());
            printf("New Parent Process ID: %d\n", getppid());

            printf("Child became orphan process.\n");

            exit(0);
        }
        else
        {
            // Parent exits before child
            printf("\nParent Process ID: %d\n", getpid());
            printf("Parent exiting before child.\n");

            exit(0);
        }
    }

    else
    {
        printf("Invalid choice!\n");

        if (pid == 0)
            exit(1);
        else
            wait(NULL);
    }

    return 0;
}


//in terminal
gcc assignment2.c -o assignment2
./assignment2


//During the 15 seconds, open another terminal and run:

ps -el | grep Z