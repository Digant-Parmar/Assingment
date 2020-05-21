#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <math.h>

int size_count=0;
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
void split(int key, struct node* node,struct node** L,struct node** R)    //split function 
{

	if(node == NULL)
	{
		*L = *R = NULL;
		return;
	}
// 	printf("inside\n");

	if(key<node->key){
		*R = node;
		split(key,node->left,L,&((*R)->left));
	}
	else{
		*L = node;
		split(key,node->right,&((*L)->right),R);
	}
	return;
}

struct node* insert_at_root(struct node* node,int key)
{
	struct node *L;
	struct node *R;

	split(key,node,&L,&R);

	node = newNode(key);

	node->key = key;
	node->left = L;
	node->right = R;

	return node;


}

struct node* insert(struct node* node, int key)			//for inserting new node
{
	int n,r;

	n = size_count;
	r = (rand() % (n+1));
	if( r == n)
	{
		return insert_at_root(node,key);
	}
	if(key< node->key)
	{
		node->left = insert(node->left,key);
	}
	else
	{
		node->right = insert(node->right,key);
	}

	return node;
}	
int size(struct node* node)  
{   
  if (node==NULL)  
    return 0; 
  else     
    return(size(node->left) + 1 + size(node->right));   
} 
  
struct node* join(struct node* l,struct node* r)		
{
	int m,n,t,total;

	m=size(l);
	n = size(r);
	total = m+n;
	if(total==0)
	{
		return NULL;
	}

	t =  (rand() % (total));

	if(t<m){
		l->right = join(l->right,r);
		return l;
	}
	else
	{
		r->left = join(l,r->left);
		return r;
	}
}

struct node* delete(struct node* root, int key)				//for deleting a node
{		

	struct node* temp;													//a recursive function that recurse until a given node is found and deletes it
	if(root == NULL)
	{
		return root;
	}

	if(key< root->key)
	{
		root->left = delete(root->left,key);
	}
	else if(key>root->key)
	{
		root->right = delete(root->right,key);
	}
	else
	{
		temp = join(root->left,root->right);
		free(root);
		root = temp;
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
	    		size_count++;
	    		fprintf(fo,"true\n");
	    	}
	    	if(temp1==2){
	            root=delete(root,temp2);
	            fprintf(fo,"true\n");
	    	}
    	}
    	i++;
    }
    fclose(fi);
    fclose(fo);

 }