#include<stdlib.h>
#include<stdio.h>
#include"IntegerQueue.h"
#include<assert.h>
#include<string.h>

typedef struct NodeObj{

   int val; 
   struct NodeObj* next;
   
   
} NodeObj;


typedef NodeObj* Node; 


typedef struct IntegerQueueObj {
 Node front;
 Node back;
 int numPairs;
 int size; 

} IntegerQueueObj;


// Constructors-Destructors ---------------------------------------------------

// newIntegerQueue()
// Constructor for the IntegerQueue ADT
IntegerQueue newIntegerQueue() {
    IntegerQueue Q = malloc(sizeof(IntegerQueueObj));
	Q->front = NULL;
	Q->back = NULL;
	Q->numPairs = 0; 
	Q->size = 0;
	return Q;

}



// freeIntegerQueue()
// Destructor for the Queue ADT
void freeIntegerQueue(IntegerQueue* pQ) {
if(pQ != NULL && *pQ != NULL){
	dequeueAll(*pQ);
	free(*pQ);
	*pQ = NULL;
}

}



Node newNode(int x) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->val = x;
   N->next = NULL;
   return N;
}

void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}


// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if Queue Q is empty, 0 (false) otherwise.
int isEmpty(IntegerQueue Q) {
	if(Q->numPairs == 0) {
		return 1;
	} else 
	return 0;

}

// length()
// Returns the number of elements in Q
int length(IntegerQueue Q) {

	return Q->numPairs; 


}

// enqueue()
// Inserts x at back of Q.
void enqueue(IntegerQueue Q, int x){
     
     if(x > 9 && x <= 99) //digit track
     {
         Q->size++; //if this number is a double digit, make extra space for IntegerQueueToString()
     }
	 Node N = newNode(x);
	 Q->numPairs++;
	 if(Q->front==NULL){ // Queue is empty
	 Q->front = Q->back = N;
	 }else{ // Queue is non-empty
	 Q->back->next = N;
	 Q->back = N;
 }
}

// dequeue()
// Deletes and returns the item at front of Q.
// Pre: !isEmpty()
int dequeue(IntegerQueue Q){
 	 int x;
	 Node N;
	 if(Q->front==NULL){
	 fprintf(stderr, "cannot dequeue() empty queue\n");
	 exit(EXIT_FAILURE);
	 }
	    x = Q->front->val;
	    N = Q->front;
	 if(Q->front==Q->back) {
	    Q->front = Q->back = NULL;
	 } else {
	    Q->front = Q->front->next;
	 }
	 Q->numPairs = Q->numPairs - 1; 
	 if(x > 9 && x < 100)
	 {
	     Q->size = Q->size - 1;
	 }
	 freeNode(&N);
	 return x;
}

// peek()
// Returns the item at front of Q.
// Pre: !isEmpty()

int peek(IntegerQueue Q) {
    if(Q->front != NULL) {
    return Q->front->val;
    } 

}

// dequeueAll()
// Resets Q to the empty state.
void dequeueAll(IntegerQueue Q)
{
    //free all nodes
    Node H = Q->front; 
    if(Q->front == NULL)
    {
        Q->front = NULL;
        Q->back = NULL;
    }
    Node T;
    while( H!=NULL )
    {
      T = H->next;
      freeNode(&H);
      H = T;
    }
   
    Q->front = NULL;
    Q->back = NULL;
    Q->numPairs = 0;


}


// Other Operations -----------------------------------------------------------
// equals()
// Returns true (1) if Q and R are matching sequences of integers, false (0) 
// otherwise.
int equals(IntegerQueue Q, IntegerQueue R) {
  if(Q->numPairs == R->numPairs)
  {
     if(Q->front == Q->back) { //means that there is only 1
         if(Q->front->val == R->front->val)
         {
             return 1; 
         } else return 0;
     }
     Node N = Q->front;
     Node L = R->front; 
     int sim = 0; 
     while(N != NULL)
     {
         if(N->val == L->val)
         {
             sim++;
             N = N->next;
             L = L->next; 
         }
     }
     
     if(sim == Q->numPairs)
     {
         return 1; 
     } else return 0; 
     
    
  } else return 0; 
    
}


// IntegerQueueToString()
// Determines a text representation of IntegerQueue Q. Returns a pointer to a 
// char array, allocated from heap memory, containing the integer sequence 
// represented by Q. The sequence is traversed from front to back, each integer
// is added to the string followed by a single space. The array is terminated 
// by a NUL '\n' character. It is the responsibility of the calling function to 
// free this heap memory.
char* IntegerQueueToString(IntegerQueue Q) {
    int nSize = Q->size + Q->numPairs; //this keeps track of any double digits
 // printf("Size: %d", Q->size);
   // printf("Num Pairs: %d", Q->numPairs);
    int size = (nSize*2);
    char* ans = calloc(size+1, sizeof(char));
    Node N = Q->front;
    int i = 0;
    
    
    while(N != NULL) {
       char* buff = calloc(3, sizeof(char));
       sprintf(buff, "%d", N->val);
     
       
       ans[i] = buff[0]; 
       i++;
       if(N->val > 9) // checks for double digit numbers. do i need to check for 3 digit numbers? 
       {
           ans[i] = buff[1];
           i++;
       }
       
       ans[i] = ' ';
       i++;
       N = N->next;
       free(buff);
    }

    ans[i++] = '\0';
    
    return ans; 
    
    
    
}


int getCharSize(IntegerQueue Q) //this returns nSize that i can use in my other methods 
{
    int nSize = Q->size + Q->numPairs; 
    int size = (nSize*2)-1;
    return size;
}




