#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Required to use random number generator to simulate tossing a coin

#define max_height 100

typedef struct myNode
{
    // Nodes of the linked list at each level
    long long key;
    struct myNode *next, *prev, *up, *down;
    int height; // Level of a node (randomly chosen)
    int curlevel;
} node;

node *infi, *pinf;

typedef struct Skip_list
{
    // The skip list and common attributes of all the skip list elements
    int maxlevel;
    int level;
    float fract; // Fraction of pointers at level i that have pointers to level i+1
    node *head;
} skip_list;

skip_list skip;

int logg(int n, int b)
{
    if (n == 0)
        return 0;
    if (n == b)
        return 1;
    else
        return 1 + logg(n / b, b);
}

int search(int x)
{
    node *temp = infi;
    int lvl = infi->curlevel;
    while (lvl--)
    {
        while (temp->next->key <= x)
        {
            printf("Node: %lld\n", temp->next->key);
            temp = temp->next;
        }
        if (temp->key == x)
            return 1;
        temp = temp->down;
    }
    return 0;
}

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

long long min()
{
    node *ptr = infi;
    while (ptr->down != NULL)
        ptr = ptr->down;
    return ptr->next->key;
}

void print(node *ptr)
{
    while (ptr != NULL)
    {
        printf("%lld ", ptr->key);
        ptr = ptr->next;
    }
    printf("\n");
}

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

    printf("1. Insert\n2. Search\n3. Delete\n4. Minimum\n-1 To EXIT\n");

    srand((unsigned)time(0)); /* Used to see the random number generator
    Otherwise the sequence of random numbers generated will be the same every time the program is executed */

    printf("Command : ");
    while (1)
    {
        int x;
        scanf(" %d", &x);
        if (x == 1)
        {
            printf("Enter the number to be inserted in the skip list : ");
            int in;
            scanf(" %d", &in);
            int level = 1;
            int p = rand();
            while (p % 2)
            {
                level++;
                p = rand();
                if (level == max_height)
                    break;
            }
            insert(in, level);
            traverse();
        }
        else if (x == 2)
        {
            printf("Enter the number to be searched in the skip list : ");
            int in;
            scanf(" %d", &in);
            if (search(in))
                printf("Present in the skip list\n");
            else
                printf("Not present in the skip list\n");
        }
        else if (x == 3)
        {
            printf("Enter the number to be delete from the skip list : ");
            int in;
            scanf(" %d", &in);
            delete (in);
            traverse();
        }
        else if (x == 4)
        {
            long long m = min();
            if (m != pinf->key)
                printf("The minimum element is : %lld\n", m);
            else
                printf("No element has been inserted in the skip list \n");
        }
        else if (x == -1)
            break;
        printf("Command : ");
    }
    free(infi);
    free(pinf);
    return 0;
}