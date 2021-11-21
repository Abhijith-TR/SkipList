#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Required to use random number generator to simulate tossing a coin

// We define the maximum height of the levels in skip-list to be 100
#define max_height 100

/*
Print beautifully
Time to generate output
Insert location of input file
*/

typedef struct myNode
{
    // Nodes of the linked list at each level
    long long key;

    // Pointers to the next, prev, above and below nodes in the skip-list
    struct myNode *next, *prev, *up, *down;

    // Level of a node (randomly chosen)
    int height;

    // Variable to check the current level at which code is working
    int curlevel;
} node;

node *infi, *pinf;

/*
typedef struct Skip_list
{
    // The skip list and common attributes of all the skip list elements

    // Variable to store the maxlevel of skip list
    int maxlevel;

    // Variable to store level of a particular node
    int level;

    // Fraction of pointers at level i that have pointers to level i+1
    float fract;

    // Pointer to the head of the linked list at a particular level
    node *head;
} skip_list; // Renaming for simplicity

skip_list skip; // Variable to store the entire skip list
*/

/*
// Function to obtain the log
int logg(int n, int b)
{
    // If n == 0 return 0
    if (n == 0)
        return 0;

    // If n == b return 1
    if (n == b)
        return 1;

    // Otherwise call it again with changed parameters
    else
        return 1 + logg(n / b, b);
}
*/

// Function to search for any element inside the skip-list
int search(int x)
{
    // Variable to store the address of the Leftmost pointer of the skip-list
    node *temp = infi;

    // Variable to store the current level of the pointer infi
    int lvl = infi->curlevel;

    // While we don't reach the bottom most level of the skip-list
    while (lvl--)
    {
        // While we don't reach an element which is greater than x we continue the loop
        while (temp->next->key <= x)
        {
            // Printing the value of element smaller than or equals to x
            printf("Node: %lld\n", temp->next->key);

            // Moving onto the next element in linked list on a particular level
            temp = temp->next;
        }

        // If the element where above while loop broke is equal to x that means we've found x
        if (temp->key == x)
            return 1;

        // Otherwise go down by one level
        temp = temp->down;
    }

    // If not found return 0
    return 0;
}

// Function to insert any element inside the skip-list
int insert(int x, int level)
{
    node **rem = malloc(infi->curlevel * sizeof(node *));
    node *temp = infi;
    int lvl = infi->curlevel;

    while (lvl--)
    {
        while (temp->next->key < x)
        {
            temp = temp->next;
        }
        rem[lvl] = temp;
        if (temp->down != NULL)
            temp = temp->down;
    }

    if (temp->key == x)
        return -1;

    if (level > infi->height)
    {
        rem = (node **)realloc(rem, level * sizeof(node *));

        for (int i = infi->height; i < level; i++)
        {
            node *newinfi = malloc(sizeof(node));
            newinfi->key = infi->key;
            newinfi->height = level;
            newinfi->curlevel = i + 1;
            newinfi->next = newinfi->prev = newinfi->up = newinfi->down = NULL;
            newinfi->down = infi;
            newinfi->next = pinf;
            infi = newinfi;
            rem[i] = infi;
        }
    }

    node *tmp = NULL;

    for (int i = 0; i < level; i++)
    {
        node *newnode = malloc(sizeof(node));
        newnode->key = x;
        newnode->prev = rem[i];
        newnode->next = rem[i]->next;
        rem[i]->next = newnode;
        newnode->down = tmp;
        newnode->next->prev = newnode;
        tmp = newnode;
        newnode->curlevel = i + 1;
        newnode->height = level;
    }
}

// Function to delete any element from the skip-list
int delete (int x)
{
    node **rem = malloc(infi->curlevel * sizeof(node *));
    node *temp = infi;
    int lvl = infi->curlevel;
    while (lvl--)
    {
        while (temp->next->key <= x)
        {
            temp = temp->next;
        }
        rem[lvl] = temp;
        if (temp->key == x && (temp->next != pinf || temp->prev->key != infi->key || temp->prev->down == NULL))
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        else if (temp->key == x && temp->next == pinf && temp->prev->key == infi->key)
        {
            node *ptr = infi;
            infi = infi->down;
            free(ptr);
        }
        if (temp->down != NULL)
        {
            node *ptr = temp;
            temp = temp->down;
            if (temp->key == x)
                free(ptr);
        }
    }
}

// Function to return the minimum value among the elements in the skip-list
long long min()
{
    node *ptr = infi;
    while (ptr->down != NULL)
        ptr = ptr->down;
    return ptr->next->key;
}

// Function to print one level of skip-list
void print(node *ptr)
{
    printf("Level %d - ", ptr->curlevel);
    ptr = ptr->next;
    while (ptr->next != NULL)
    {
        if (ptr->next != pinf)
            printf("%lld -> ", ptr->key);
        else
            printf("%lld", ptr->key);
        ptr = ptr->next;
    }
    printf("\n");
}

// Function to print the entire skip-list
void traverse()
{
    node *ptr = infi;
    while (ptr != NULL)
    {
        print(ptr);
        ptr = ptr->down;
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    printf("Should the times for each operation be displayed? (Y/N) : ");
    char t;
    scanf(" %c", &t);

    infi = malloc(sizeof(node));
    infi->key = -1;
    for (int i = 0; i < 63; i++)
        infi->key *= 2;

    infi->height = 1;
    infi->curlevel = 1;
    infi->next = infi->prev = infi->up = infi->down = NULL;

    pinf = malloc(sizeof(node));
    pinf->key = 9223372036854775807;
    infi->key = pinf->key * -1 - 1;
    pinf->height = 1;
    pinf->curlevel = 1;
    pinf->prev = infi;
    infi->next = pinf;
    pinf->down = NULL;
    pinf->next = NULL;
    pinf->up = NULL;

    // Printing the menu of operations
    printf("1. Insert\n2. Search\n3. Delete\n4. Minimum\n5. Traverse\n-1 To EXIT\n");

    srand((unsigned)time(0)); /* Used to see the random number generator
    Otherwise the sequence of random numbers generated will be the same every time the program is executed */

    // Asking the user for command
    printf("Command : ");

    // s is the start time of while loop
    // f would be the finish time of while loop
    // And f-s would be total time taken for execution
    time_t s, f;

    // s takes the current time value
    s = clock();

    // Running the loop as many times as you want and break when command is -1
    while (1)
    {
        // x is to store the command number
        int x;

        // Taking input of command number
        scanf(" %d", &x);

        if (x == 1)
        {
            // If command is 1 that means we have to insert a value in the skip-list

            // start is the start time of insert function
            // finish is the finish time of insert function
            time_t start, finish;

            // Asking the user for number to be inserted
            printf("Enter the number to be inserted in the skip list : ");

            // variable to store the input number or integer
            int in;

            // Taking input of the number to be inserted
            scanf(" %d", &in);

            // Setting the current level to be 1
            int level = 1;

            // choosing a random number and storing in p
            int p = rand();

            // Starting the clock for calculating insertion time
            start = clock();

            while (p % 2)
            {
                // If p is odd then we would increase the level by 1
                level++;

                // Again at this level again toss the coin ( select a random number )
                p = rand();

                // If level reaches the maximum level that is supported break out of the while loop
                if (level == max_height)
                    break;
            }
            // level = 30;

            // Calling the insert function with parameters in and level of in
            insert(in, level);

            // Finishing time of the clock
            finish = clock();

            if (t == 'Y')
            {
                // If we're asked the total insertion time then we would print the below line
                printf("The time taken to perform the insert operation is %lfs\n", (double)(finish - start) / CLOCKS_PER_SEC);
            }
            // traverse();
        }

        else if (x == 2)
        {
            // If command is 2 that means we have to search for a value in the skip-list

            // start is the start time of search function
            // finish is the finish time of search function
            time_t start, finish;

            // Asking the user to enter the number to be searched for
            printf("Enter the number to be searched in the skip list : ");

            // Variable in to store the number that has to be search for
            int in;

            // Taking input of the value to be searched for
            scanf(" %d", &in);

            // Starting the clock for calculating searching time
            start = clock();

            // If search(in) is 1 that means the element is present inside the skip-list
            if (search(in))
                printf("Present in the skip list\n");

            // Else the element is not present
            else
                printf("Not present in the skip list\n");

            // Finishing time of the clock
            finish = clock();

            if (t == 'Y')
            {
                // If we're asked the total searching time then we would print the below line
                printf("The time taken to perform the search operation is %lfs\n", (double)(finish - start) / CLOCKS_PER_SEC);
            }
            // traverse();
        }

        else if (x == 3)
        {
            // If command is 3 that means we have to delete a value from the skip-list

            // start is the start time of delete function
            // finish is the finish time of delete function
            time_t start, finish;

            // Asking the user to input the value that has to be deleted from the skip-list
            printf("Enter the number to be delete from the skip list : ");

            // Variable to store the number that has to be deleted
            int in;

            // Taking input of the value to be deleted from the skip-list
            scanf(" %d", &in);

            // Starting the clock for calculating searching time
            start = clock();

            // Calling delete function passing the vale that has to be deleted
            delete (in);

            // Uncomment below 4 lines if duplicates to be deleted when command 2 is selected
            // while (search(in))
            // {
            //     delete (in);
            // }

            // Finishing time of the clock
            finish = clock();

            if (t == 'Y')
            {
                // If we're asked the total deletion time then we would print the below line
                printf("The time taken to perform the delete operation is %lfs\n", (double)(finish - start) / CLOCKS_PER_SEC);
            }

            // traverse();
        }

        else if (x == 4)
        {
            // If command is 4 that means we have to find the minimum element in the skip-list

            // Calling the min function and storing the minimum value in m
            long long m = min();

            // If the m is not equals to -2^63 that means there is an element inside the skip-list and minimum value is m
            if (m != pinf->key)
                printf("The minimum element is : %lld\n", m);

            // If m is equal to -2^63 that means no element inside the skip-list
            else
                printf("No element has been inserted in the skip list \n");

            // traverse();
        }

        else if (x == 5)
        {
            // If command is 5 that means we have to traverse the entire skip-list and print it

            // Calling traverse function which will print the entire skip-list level wise
            traverse();
        }

        // If the command is -1 that means break the while loop and no more functions are to be performed on the skip-list
        else if (x == -1)
        {
            break;
        }

        // If command is none of the one inside Menu then print the menu again and show an error
        else
        {
            printf("Error! Unknown Command\n\n");
            printf("1. Insert\n2. Search\n3. Delete\n4. Minimum\n5. Traverse\n-1 To EXIT\n");
        }

        // Printing a new line
        printf("\n");

        // Asking again for the command
        printf("Command : ");
    }

    // Finishing the clock after all the functions performed
    f = clock();

    // Printing the total execution time by taking difference of f ans s
    printf("%lf\n", (double)(f - s) / CLOCKS_PER_SEC);

    // Freeing the pointer infi
    free(infi);

    // Freeing the pointer pinf
    free(pinf);
    return 0;
}
