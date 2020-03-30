#include<bits/stdc++.h>

using namespace std;

struct node {                                   //defining stack structure
  int high;
  int low;
  int line_num;
  node * next;
};
struct node * head;                             //declaring the head for stack
int keep = 0;                                   //keep will have the count of no. of element in stack

void push(int hi, int lo, int line_num) {       //push pushes the given node
  struct node * temp = new node();              //initializing temp

  temp -> high = hi;                            //initializing all the value of struct
  temp -> low = lo;
  temp -> line_num = line_num;
  temp -> next = head;
  head = temp;

  keep++;                                       //increasing the keep value as an element is pushed in stack
}

void pop() {                                    //pops out the element
  struct node * temp;
  temp = head;
  head = head -> next;
  temp -> next = NULL;
  free(temp);
  keep--;                                       //decreasing the value of keep as 1 element is poped out of stack
}

void print_stack() {                            //it prints the hole stack every time its called
  struct node * temp;
  temp = head;

  for (int i = 0; i < keep; i++) {
    cout << "   ";
  }
  cout << "{";
  if (keep > 0) {
    for (int i = 0; i < keep; i++) {
      cout << "(" << temp -> low;
      cout << "," << temp -> high;
      cout << "," << temp -> line_num;
      cout << ")";

      if (i < keep - 1) {
        cout << ",";
      }
      temp = temp -> next;
    }
  }

  cout << "}" << endl;
}

void print(int a[], int n) {                      //prints the array
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
}

int partition(int a[], int hi, int lo) {          //partition for the quicksort
  int pivot = a[hi];
  int i = lo - 1;

  for (int j = lo; j <= hi; j++) {
    if (a[j] < pivot) {
      i++;
      swap(a[i], a[j]);
    }
  }
  swap(a[i + 1], a[hi]);
  return (i + 1);
}
int rand_partition(int a[], int hi, int lo) {     //creating a random partition for quicksort
  srand(time(0));
  int temp = rand();
  temp = lo + temp % (hi - lo);                  
  swap(a[temp], a[hi]);
  return partition(a, hi, lo);
}

int quicksort(int a[], int hi, int lo) {          //quicksort function it prints and again call the quicksort
  if (lo < hi) {
    int pivot;
    pivot = rand_partition(a, hi, lo);
    push(pivot - 1, lo, __LINE__ + 3);            // here we are doing __LINE__+3 as another quicksort function is after 2 line of this
    print_stack();
    quicksort(a, pivot - 1, lo);
    push(hi, pivot + 1, __LINE__ + 3);            // the same thing is applied over here as above
    print_stack();
    quicksort(a, hi, pivot + 1);
  }
  pop();                                          
  print_stack();                                  //printing the stack
}

int main() {

  int n = 10;                                     //decraring the size of array
  int a[10];

  srand(0);
  for (int i = 0; i < 10; i++) {                  //giving random values to the element of the array
    a[i] = rand() % 100;
  }

  cout << "the unsorted array is:" << endl;       //printing unsorted array
  print(a, n);
  cout << endl;

  print_stack();
  push(n - 1, 0, __LINE__ + 3);

  print_stack();
  quicksort(a, n - 1, 0);
  cout << "Sorted array is : \n" << endl;         //printing sorted array
  print(a, n);
  cout<<endl;

}