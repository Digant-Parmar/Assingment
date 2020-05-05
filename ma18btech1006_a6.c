// C program to convert infix expression to postfix 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <math.h>

int t=0;
FILE *fi;								//input file
FILE *fo;								//output file

struct node
{
	int key;
	struct node *left;
	struct node *right;
	struct node *parent;
};

struct node *newNode(int x){							//function for creating new node
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->key = x;
	temp->left = temp->right = NULL;
	return temp;
}

struct node* insert(struct node* node, int key)			//for inserting new node
{
	if(node == NULL)
	{
		return newNode(key);
	}
	if(key< node->key)
	{
		node->left = insert(node->left,key);
	}
	else if(key>node->key)
	{
		node->right = insert(node->right,key);
	}

	return node;
}	

struct node *find(struct node * node, int key)			//for finding a given node and its level
{
	if(node == NULL)
	{
		t=0;
		return node;
	}
	if(node->key == key)
	{
		return node;
	}
	if(node->key >key)
	{
		t++;
		return find(node->left,key);
	}
	else
	{
		t++;
		return find(node->right,key);
	}
}

struct node * minNode(struct node* node) 			//calculates the minnode for the deletion
{ 
    struct node* current = node; 

    while (current && current->left != NULL) 
     {
		 current = current->left; 
  	 }

    return current; 
} 

struct node* delete(struct node* root, int key)				//for deleting a node
{															//a recursive function that recurse until a given node is found and deletes it
	if(root = NULL)
	{
		return root;
	}

	if(key<root->key)
	{
		root->left = delete(root->left,key);
	}
	else if(key>root->key)
	{
		root->right = delete(root->right,key);
	}
	else
	{
		if(root->left ==NULL)
		{
			struct node *temp = root->right;
			free(root);
			return temp;
		}
		else if(root->right==NULL)
		{
			struct node *temp = root->left;
			free(root);
			return temp;
		}

		struct node *temp = minNode(root->right);		//finding the minNode for the given root
		root->key = temp->key;
		root->right = delete(root->right,temp->key);
	}
	return root;
}
void inorder(struct node *root){			//recussive funcion for printing the inorder
	if(root!= NULL)
	{
		inorder(root->left);
		fprintf(fo,"%d ",root->key );
		fprintf(fo," ");
		inorder(root->right);
	}
}

void postorder(struct node *root)
{
	if(root!= NULL)
	{
		postorder(root->left);
	    postorder(root->right);

		fprintf(fo,"%d ",root->key );
		fprintf(fo," ");
	}
}
void preorder(struct node *root){
	if(root!= NULL)
	{

		fprintf(fo,"%d ",root->key );
		fprintf(fo," ");
		preorder(root->left);
	    preorder(root->right);

	}
}

void printTree(struct node* node)
{
	 fprintf(fo,"inoder:");
     inorder(node);
     fprintf(fo,"\npostorder:");
     postorder(node);
     fprintf(fo,"\npreorder:");
     preorder(node);
     fprintf(fo,"\n");
}

void printSubTree(struct node *node, int key)
{
	struct node *temp;
	temp = find(node, key);
	printTree(temp);
}

int leftNode(struct node *root)          //calculates the number of left nodes
{
	int count = 1;
	if(root->right != NULL)
	{
		count = count + leftNode(root->right);
	}
	if(root->left != NULL)
	{
		count - count +leftNode(root->left);
	}
	return count;
}
	
int rightNode(struct node *root)		//calculates number of rigth nodes
{
	int count = 1;
	if(root->right!=NULL)
	{
		count = count + rightNode(root->right);
	}
	if(root->left != NULL)
	{
		count - count +rightNode(root->left);
	}
	return count;
}

void CalculateImbalance(struct node *root, int key)
{
	while(root->key != key)
	{
		if(root->key >key)
		{
			root = root->left;
		}
		else if(root->key <key)
		{
			root = root->right;
		}
	}

	int left_count=0;
	int right_count = 0;

	if(root->left!=NULL)
	{
		left_count = leftNode(root->left);
	}
	if(root->right!=NULL)
	{
		right_count = rightNode(root->right);
	}

	fprintf(fo,"%d\n",abs(left_count - right_count));
}

int main()
{
	struct node *root = NULL;
	fi = fopen("input.txt","r");
	fo = fopen("output.txt","w");
	char finput[100],foutput[100];

	fgets(finput,100,fi);
	
	int temp,temp1,temp2;
	struct node *c;
	
	sscanf(finput,"%d",&temp);
	
	int i=0;
	while(i<temp){
    	fscanf(fi,"%s",finput);
    	sscanf(finput,"%d",&temp1);
    	if(temp1==4){
    		printTree(root);
    	}
    	else{
	    	fscanf(fi,"%s",foutput);
	    	sscanf(foutput,"%d",&temp2);
	    	if(temp1==1){
	    		root=insert(root,temp2);
	    		fprintf(fo,"true\n");
	    	}
	    	if(temp1==2){
	            root=delete(root,temp2);
	            fprintf(fo,"true\n");
	    	}
	    	if(temp1==3){
			    c=find(root,temp2);
			    if(c!=NULL){
			   	if(c->left==NULL&&c->right==NULL){
						t++;
					}	
			    	fprintf(fo,"true %d\n",t);
			    }
			    else{
			    	fprintf(fo,"false\n");
			    }
	    		
	    	}
	    	if(temp1==5){
	    		printSubTree(root,temp2);
	    	}
	    	if(temp1==6){
	    		CalculateImbalance(root,temp2);
    		}

    	}
    	i++;
    }
    fclose(fi);
    fclose(fo);

 }