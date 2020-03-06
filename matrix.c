#include<stdio.h>
#include<stdlib.h>

int col_count = 0;
int row_count = 0;

struct Node
{
	int val;
	struct Node *next_row;
	struct Node *next_col;
};


struct Node* create_node(void){
	struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
	if(temp==NULL)
	{
		printf("Error allocating memory");
		exit(1);
	}
	return temp;
}

void linked_list(struct Node **head){
	struct Node *new_node;
	int value;
   FILE *file;
   file = fopen("1234.txt", "r");
   int j=0;
   int i=0;
   if (file != NULL) {
      char buf[BUFSIZ] = {'\0'}; 
       while (fgets(buf, BUFSIZ, file) != NULL) {
  
       	size_t n = sizeof(buf) / sizeof(char);
       
       	while(j<n){
  
  		char ch[n];
       	int k=0;
       	int c=-1;
  

       		while(i<n){
       			if (buf[i]==',')
       			{
       				c=0;
       				col_count++;
       				break;
       			}
       			if(buf[i] == ';')
       			{
       				row_count++;
       				col_count =0;
       				c=1;
       				break;
       			}
       			ch[k] = buf[i];
       			k++;
       			i++;

       		}       
       				
       		int pos;
       		sscanf(ch,"%d",&pos);

       		struct Node *temp = NULL;
       		struct Node *temp1 = NULL;
       		temp1=*head;
       		temp = (struct Node *)malloc(sizeof(struct Node));
       		if(c=0)
       		{
       			temp->next_col =NULL;
       			while(temp1->next_col!=NULL)
       			{
       				temp1= temp1->next_col;
       			}

       			temp->val = pos;
       			temp->next_col =NULL;
       			temp->next_row = NULL;
       			temp1->next_col = temp;
       		}
       		if(c=1)
       		{
       			
       			while(temp1->next_row!=NULL)
       			{
       				temp1= temp1->next_row;
       			}

       			temp->val = pos;
       			temp->next_col =NULL;
       			temp->next_row = NULL;
       			temp1->next_row = temp;
       		}
       		i++;
       		j=i;

       	}

      }
   } else {
      perror("fopen");
   }
 
fclose(file);
}

int main()
{
	struct Node* head =NULL;
	head = (struct Node *)malloc(sizeof(struct Node));
	linked_list(&head);
}