#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //Required to use random number generator to simulate tossing a coin

int max_height;

typedef struct myNode {  //Nodes of the linked list at each level
    long long key;
    struct myNode * next, *prev,*up, *down;
    int height; //level of a node (randomly chosen)
    int curlevel;
}node;

node ** levels;
node * infi;

typedef struct Skip_list { //The skip list and common attributes of all the skip list elements
    int maxlevel;
    int level;
    float fract; //fraction of pointers at level i that have pointers to level i+1
    node * head;
}skip_list;

skip_list skip;

int log(int n,int b) {
    if (n==0) return 0;
    if (n==b) return 1;
    else return 1+log(n/b,b);
}

int search(int x) {
    
}

void insert(int x,int level) {
    if (infi->prev == NULL) {
        node * temp = malloc(sizeof(node));
        temp ->height=level;
        temp->key = x;
        temp->curlevel = 1;
        temp->next = NULL;
        temp->prev = infi;
        infi->next = temp;
        for (int i=2;i<=level;i++) {
            node * ptr = malloc(sizeof(node));
            ptr->down = temp;
            ptr->curlevel = i;
            ptr->height = level;
            ptr->next = NULL;
            ptr->key = x;
            node * newinf = malloc(sizeof(node));
            newinf->key = infi->key;
            newinf->curlevel = i;
            newinf->down = infi;
            newinf->next = ptr;
            newinf->prev = NULL;
            newinf->height = level;
            ptr->prev = newinf;
            infi = newinf;
            printf("%d\n",infi->down->curlevel);
        }
    }
}

int delete(int x) {

}

void print(node * ptr) {
    //ptr = ptr->next;
    while (ptr!=NULL) {
        printf("%lld ",ptr->key);
        ptr = ptr->next;
    }
    printf("\n");
}

void traverse() {
    node * temp = infi;
    while (temp!=NULL) {
        // printf("aaaaaa %lld\n",temp->key);
       // printf("%d\n",temp->curlevel);
        print(temp);
        temp = temp->down;
    }
}

int main() {
    infi = malloc(sizeof(node));
    infi->key =  -1;
    for (int i=0;i<63;i++) infi->key*=2;
    infi->height = 1;
    infi->curlevel = 1;
    infi->next = infi->prev = infi->up = infi->down = NULL;

    srand((unsigned)time(0)); //Used to see the random number generator 
    // Otherwise the sequence of random numbers generated will be the same 
    //every time the program is executed 
    
    int n;
    scanf(" %d",&n);
    skip.maxlevel = n; //maximum height to which the skip tree will go

    while (1) {
        int x;
        scanf(" %d",&x);
        if (x==1) {
            int in;
            scanf(" %d",&in);
            int level = 1;
            int p = rand();
            while (p%2!=0) {
                level++;
                p = rand();
            }
            //printf("%d\n",level);
            insert(in,level);
            traverse();
        }
        else if (x==2) {}
        else if (x==3) {

        }
        else if (x==-1) break;
    }
}