#include <bits/stdc++.h> 
using namespace std; 

struct node { 							     //creating struct
	int time; 
	int job;
	node* next; 
	node(int t,int j) 						//for new node
	{ 
		job = j;
		time = t; 
		next = NULL; 
	} 
}; 

int j_count = 0;						//it keeps the count of new job numbers
node *front=NULL, *rear=NULL; 			//initializing the front and rear of queue
	

void enQueue(int x,int j)				//adds the element at the end
{ 
	node* temp = new node(x,j); 

	if (rear == NULL) { 				//if the queue is eempty
		front = rear = temp; 
		return; 
	} 

	rear->next = temp; 
	rear = temp; 

} 

void deQueue() 							//removes the element from the queue
{ 
	
	if (front == NULL) 					//for empty queue
		return; 


	node* temp = front; 
	front = front->next; 


	if (front == NULL) 
		rear = NULL; 

	delete (temp); 
} 


void new_queue(int n)				//generate new queue
{
	
	
	for(int i=0;i<n;i++)
	{
		j_count++;
		int r_time =rand()%300;
		enQueue(r_time,j_count);

	}
}

void print_queue(){					//prints the queue
	node*temp = front;
	while(temp!=NULL)
	{
		cout<<"J"<<temp->job<<":"<<temp->time<<" ";
		temp = temp->next;
	}
	cout<<";"<<endl;
}

void roundRobin(){

	int n = 100; 					//initial number of jobs
	int u=0,x=128;					//u is the time in us
	new_queue(n);					//generate initial queue
	cout<<"Initial Queue: ";
	print_queue();
	cout<<"\n";

	while(true)
	{
		
		u = u+50;

		if(front== NULL)
		{
			cout<<"At t="<<u<<"us:Empt"<<endl;
			return;
		}
		int y = front->time;
		int j = front->job;	
		
		if(y<50){						//if the time of job is <50 it will dequeue
			deQueue();
		}
		else{							
			y = y-50;
			deQueue();
			enQueue(y,j);
			
		}
		cout<<"At t="<<u<<"us:";
		print_queue();
		int c = u%200;
		if(c == 0 && x>1)				//after every 200us it will gereate new queuse adding x elements
		{
			x = x/2;
			new_queue(x);
			cout<<"\n*********"<<u<<"us passed added "<<x<<" new jobs at the end of the queue"<<endl;
			cout<<"After addition: ";
			print_queue();		
			cout<<"\n";
		}
	}


}
 
int main() 
{ 
 	srand(time(0));
	roundRobin();
	return 0; 
} 
 
