#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //Required to use random number generator to simulate tossing a coin

int max_height;

typedef struct myNode {  //Nodes of the linked list at each level
    int key;
    struct myNode ** next;
    int height; //level of a node (randomly chosen)
}node;

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

void insert(int x) {

}

int delete(int x) {

}

int main() {
    srand((unsigned)time(0)); //Used to see the random number generator 
    // Otherwise the sequence of random numbers generated will be the same 
    //every time the program is executed 

    float x;
    scanf(" %f", &x);
    skip.fract = x; //fraction of pointers at level i which are contained in level i+1
    
    int n;
    scanf(" %d",&n);
    skip.maxlevel = n; //maximum height to which the skip tree will go

}