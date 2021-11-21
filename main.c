// Group 1

// Implementation of Skip Lists

// Prashant Mittal 2020CSB1113
// Abhijith
// Shahnawaz
// Vinit

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
            //printf("Node: %lld\n", temp->next->key);

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
    //Creating temporary storage for the pointers at each level at which we go down
    node **rem = malloc(infi->curlevel * sizeof(node *));

    //Creating a temporary node for traversal
    node *temp = infi;

    //Initialising the height to move down
    int lvl = infi->curlevel;

    //Until you are at the lowermost level
    while (lvl--)
    {
        //Move forward until you find the element greater than the element x
        while (temp->next->key < x)
        {
            temp = temp->next;
        }
        //Whenever you have to move down store the address of the node to be used
        rem[lvl] = temp;

        //If you are not at the lowermost level, go down
        if (temp->down != NULL)
            temp = temp->down;
    }

    // if (temp->key == x)
    //     return -1;

    //If the height is greater than the current height of the skip list
    if (level > infi->height)
    {   
        //Allocate more memory to store the new infinity values required
        rem = (node **)realloc(rem, level * sizeof(node *));

        //Allocate as many more infinities as required
        for (int i = infi->height; i < level; i++)
        {
            //Allocate memory for the new infinity
            node *newinfi = malloc(sizeof(node));

            //Copy the contents of infinity to the new infinity
            newinfi->key = infi->key;
            newinfi->height = level;
            newinfi->curlevel = i + 1;
            newinfi->next = newinfi->prev = newinfi->up = newinfi->down = NULL;
            newinfi->down = infi;
            newinfi->next = pinf;
            infi = newinfi;

            //Set the previous of the new level to the new infinity
            rem[i] = infi;
        }
    }

    //Give some memory for the new temporary node
    node *tmp = NULL;

    //Go from the lowermost to the highest level
    for (int i = 0; i < level; i++)
    {   
        //Allocate memory for the new node
        node *newnode = malloc(sizeof(node));

        //Store the new values in the new node to be made
        newnode->key = x;
        newnode->prev = rem[i];
        newnode->next = rem[i]->next;

        //Set the next of the new node to the newly created pointer
        rem[i]->next = newnode;
        newnode->down = tmp;
        newnode->next->prev = newnode;

        //Set the heights of the newly created nodes
        tmp = newnode;
        newnode->curlevel = i + 1;
        newnode->height = level;
    }
}

// Function to delete any element from the skip-list
int delete (int x)
{
    // Allocating memory to pointer rem
    node **rem = malloc(infi->curlevel * sizeof(node *));

    // Temp pointing to infi
    node *temp = infi;

    // lvl stores the curlevel of infi
    int lvl = infi->curlevel;

    // While we don't reach bottom most level keep going down
    while (lvl--)
    {
        // While value in temp->next node is less than or equal to x keep moving to next node
        while (temp->next->key <= x)
        {
            // Moving to next node
            temp = temp->next;
        }

        // rem[lvl] points to the temp at this point
        rem[lvl] = temp;

        // If temp->key equals x and temp is not a corner element or bottommost element then delete the element from linked list
        // Change the next of prev and prev of next
        if (temp->key == x && (temp->next != pinf || temp->prev->key != infi->key || temp->prev->down == NULL))
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        // If key in temp is x and it is a corner element free the pointer infi after moving one level down
        else if (temp->key == x && temp->next == pinf && temp->prev->key == infi->key)
        {
            node *ptr = infi;
            infi = infi->down;
            free(ptr);
        }

        // If temp->down is not NULL then make temp equals temp->down
        if (temp->down != NULL)
        {
            // ptr points to temp
            node *ptr = temp;

            // Move one level down
            temp = temp->down;

            // If value in temp is equal to x free pointer ptr
            if (temp->key == x)
                free(ptr);
        }
    }
}

// Function to return the minimum value among the elements in the skip-list
long long min()
{
    // Storing the address of infi in variable ptr
    node *ptr = infi;

    // While we don't read the lowest level we move down by one level
    while (ptr->down != NULL)
        ptr = ptr->down;

    // Return the value inside the ptr->next pointer in the bottommost level of skip-list
    return ptr->next->key;
}

// Function to print one level of skip-list
void print(node *ptr)
{
    // Printing the current level number
    printf("Level %d - ", ptr->curlevel);

    // Moving on to the next node in this level
    ptr = ptr->next;

    // While next of ptr is not NULL move on to next node
    while (ptr->next != NULL)
    {
        // If next of ptr doesn't point to positive infinity then print value with ->
        if (ptr->next != pinf)
            printf("%lld -> ", ptr->key);

        // If it is the last node don't print ->
        else
            printf("%lld", ptr->key);

        // Move on to the next node on this level
        ptr = ptr->next;
    }

    // Print new line to end the level
    printf("\n");
}

// Function to print the entire skip-list
void traverse()
{
    // Storing the address of infi in ptr
    node *ptr = infi;

    // While we don't reach the bottom most level keep going down
    while (ptr != NULL)
    {
        // Calling print function to print current level of the skip-list
        print(ptr);

        // Move down by one level
        ptr = ptr->down;
    }
}

int main()
{
    // Taking input from file input.txt
    // freopen("input.txt", "r", stdin);

    // Writing the output in output.txt file
    // freopen("output.txt", "w", stdout);

    // Asking the user if he/she wants to see the time taken for every function
    printf("Should the times for each operation be displayed? (Y/N) : ");

    // Variable to store the input for Y/N
    char t;

    // Taking in the input for Y/N
    scanf(" %c", &t);

    // Allocating memeory to the pointer infi
    infi = malloc(sizeof(node));

    // Setting the value of key to -1
    infi->key = -1;

    // Making the value of infi->key equals -2^63
    for (int i = 0; i < 63; i++)
        infi->key *= 2;

    // Setting the initial height of infi as 1
    infi->height = 1;

    // Settinf the curlevel of infi as 1
    infi->curlevel = 1;

    // Making next, prev, up, down of infi as NULL
    infi->next = infi->prev = infi->up = infi->down = NULL;

    // Allocating memory to pinf
    pinf = malloc(sizeof(node));

    // Setting the key of pinf to 2^63 - 1
    pinf->key = 9223372036854775807;

    // infi->key = pinf->key * -1 - 1;

    // Setting the height of p to 1
    pinf->height = 1;

    // Setting current level of p to 1
    pinf->curlevel = 1;

    // Giving infi to the prev of pinf
    pinf->prev = infi;

    // Giving pinf to the next of infi
    infi->next = pinf;

    // Setting next, up, down of pinf to NULL
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

            // Starting the clock for calculating deletion time
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

            // start is the start time of min function
            // finish is the finish time of min function
            time_t start, finish;

            // Starting the clock for calculating finding minimum element time
            start = clock();

            // Calling the min function and storing the minimum value in m
            long long m = min();

            // Finishing time of the clock
            finish = clock();

            // If the m is not equals to -2^63 that means there is an element inside the skip-list and minimum value is m
            if (m != pinf->key)
                printf("The minimum element is : %lld\n", m);

            // If m is equal to -2^63 that means no element inside the skip-list
            else
                printf("No element has been inserted in the skip list \n");

            if (t == 'Y')
            {
                // If we're asked the total time for finding min element then we would print the below line
                printf("The time taken to perform the min operation is %lfs\n", (double)(finish - start) / CLOCKS_PER_SEC);
            }

            // traverse();
        }

        else if (x == 5)
        {
            // If command is 5 that means we have to traverse the entire skip-list and print it

            // start is the start time of traverse function
            // finish is the finish time of traverse function
            time_t start, finish;

            // Starting the clock for traversal time
            start = clock();

            // Calling traverse function which will print the entire skip-list level wise
            traverse();

            // Finishing time of the clock
            finish = clock();

            if (t == 'Y')
            {
                // If we're asked the total time for traversing skip-list then we would print the below line
                printf("The time taken to perform the traversal operation is %lfs\n", (double)(finish - start) / CLOCKS_PER_SEC);
            }
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

    // Printing the total execution time by taking difference of f and s
    if (t=='Y') printf("Total time taken for the execution of the program is %lf\n", (double)(f - s) / CLOCKS_PER_SEC);

    // Freeing the pointer infi
    free(infi);

    // Freeing the pointer pinf
    free(pinf);

    return 0;
}
