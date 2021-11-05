#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Required to use random number generator to simulate tossing a coin

int max_height;

typedef struct myNode
{
    // Nodes of the linked list at each level
    long long key;
    struct myNode *next, *prev, *up, *down;
    int height; // level of a node (randomly chosen)
    int curlevel;
} node;

node **levels;
node *infi , *pinf;

typedef struct Skip_list
{
    // The skip list and common attributes of all the skip list elements
    int maxlevel;
    int level;
    float fract; // fraction of pointers at level i that have pointers to level i+1
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
    node * temp = infi;
    int lvl = infi->curlevel;
    while (lvl--) {
        while (temp->next->key<x) {
            temp = temp->next;
        }
        if (temp->key == x) return 1;
        temp = temp->down;
    }
    return 0;    
}

int insert(int x, int level)
{
    //printf("111\n");
    node ** rem = malloc(infi->curlevel*sizeof(node *));
    node * temp = infi;
    int lvl = infi->curlevel;
    while (lvl--) {
        while (temp->next->key<x) {
            temp = temp->next;
        }
        rem[lvl]=temp;
        if (temp->down!=NULL) temp = temp->down;
    }
    // printf("222\n");
    // printf("%d\n",level);
    // printf("%d\n",infi->height);
    // printf("%lld\n",temp->key);
    if (temp->key==x) return -1;
    //printf("%d %d\n",level,infi->height);
    if (level>infi->height)
    {
        // printf("%d\n",level);
        // printf("555\n");
        rem=(node**)realloc(rem,level*sizeof(node *));
        for (int i =infi->height;i<level;i++)
        {
            node * newinfi=malloc(sizeof(node ));
            newinfi->key = infi->key;
            newinfi->height = level;newinfi->curlevel = i+1;
            newinfi->next = newinfi->prev = newinfi->up = newinfi->down = NULL;
            newinfi->down=infi;
            newinfi->next=pinf;
            infi=newinfi;
            rem[i]=infi;
        }
        //printf("444\n");
    }
    node *tmp=NULL;
    for (int i=0;i<level;i++)
    {
        node *newnode= malloc(sizeof(node));
        newnode->key=x;
        newnode->prev = rem[i];
        newnode->next=rem[i]->next;
        rem[i]->next=newnode;
        newnode->down=tmp;
        newnode->next->prev=newnode;
        tmp=newnode;
        newnode->curlevel=i+1;
        newnode->height=level;
    }
    //printf("333\n");
}

int delete (int x)
{
}

void print(node *ptr)
{
    // ptr = ptr->next;
    while (ptr != NULL)
    {
        printf("%lld ", ptr->key);
        ptr = ptr->next;
    }
    printf("\n");
}

void traverse()
{
    node *temp = infi;
    while (temp != NULL)
    {
        // printf("aaaaaa %lld\n",temp->key);
        // printf("%d\n",temp->curlevel);
        print(temp);
        temp = temp->down;
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
    infi->key = pinf->key*-1-1;
    //printf("%lld\n",infi->key);
    pinf->height= 1;
    pinf->curlevel=1;
    pinf->prev=infi;
    infi->next=pinf;
    pinf->down=NULL;
    pinf->next=NULL;
    pinf->up=NULL;


    srand((unsigned)time(0)); /* Used to see the random number generator
    Otherwise the sequence of random numbers generated will be the same every time the program is executed */

    int n=100;
    //printf("Max Height : ");
    //scanf(" %d", &n);
    //skip.maxlevel = n; // maximum height to which the skip tree will go

    printf("Command : ");
    while (1)
    {
        int x;
        scanf(" %d", &x);
        if (x == 1)
        {
            int in;
            scanf(" %d", &in);
            int level = 1;
            int p = rand();
            while (p % 2)
            {
                level++;
                p = rand();
                if (level==n) break;
            }
            //printf("%d\n", level);
            insert(in, level);
            //traverse();
        }
        else if (x == 2)
        {
            int in;
            scanf(" %d",&in);
            if (search(in)) printf("Present in the skip list\n");
            else printf("Not present in the skip list\n");
        }
        else if (x == 3)
        {
        }
        else if (x == -1)
            break;
        printf("Command : ");
    }
}