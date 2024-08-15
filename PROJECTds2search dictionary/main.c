#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{

    char*data;
    struct node*left;
    struct node*right;
} node;


node * newNode (char*word)
{
    node *n=malloc(sizeof(node));
    n->data=malloc(strlen(word)+1);
    strcpy(n->data,word);
    n->right=n->left=NULL;
    return n;
}

node* insert(node*root,char*word)
{
    if(root==NULL)
        root=newNode(word);
    if(strcasecmp(word,root->data)<0)
        root->left=insert(root->left,word);
    else if(strcasecmp(word,root->data)>0)
        root->right=insert(root->right,word);
    return root;
}
int count(node*root)
{
    if (root==NULL)
        return 0;
    else
        return 1+count(root->left)+count(root->right);

}


int max(int a,int b)
{

    if (a>b)
        return a;
    else
        return b;
}


int height (node*root)
{

    if (!root)
        return -1;
    else
        return 1+max(height (root->left),height(root->right));


}

node*load_Dictionary()
{
    FILE* f;
    f = fopen("Dictionary.txt", "r");
    if (f == NULL)
    {
        printf("Error in opening file\n");
        return NULL;
    }
    printf("Dictionary is loaded succefully\n");
    node*root=NULL;
    char word[150];
    while(fgets(word,sizeof(word),f))
    {

        word[strcspn(word,"\n")]='\0';
        root=insert(root,word);
    }
    fclose(f);

    return root;
}
node*getlastvisited(node*root,char*token) {
    node*lastvisited=NULL;
    node*current=root;
    while (current!=NULL) {
        if (!(strcasecmp(token,current->data))) {
            lastvisited=current;
            break;
        } else if (strcasecmp(token,current->data)<0) {
            lastvisited=current;
            current=current->left;
        } else {
            lastvisited=current;
            current=current->right;
        }
    }
    return lastvisited;
}
node*search(node*root, char* word)
{

    node*temp=root;
    while(temp!=NULL)
    {
        if(!strcasecmp(word,temp->data))
            return temp;
        else if (strcasecmp(word,temp->data)<0)
            temp=temp->left;
        else
            temp=temp->right;
    }
    return NULL;
}
node*exists(node*root,char sent[])
{
  char*token= strtok(sent," \t") ;

  while(token!=NULL)
  {
      if(!search(root,token))
      { node*lastvisited=getlastvisited(root,token);
       printf("The last visited node is:%s\n",lastvisited->data);
       //call predecessor&successor
       token=strtok(NULL," \t");
      }
      else{
        printf("found in the dictionary:%s\n",token);
     token=strtok(NULL," \t");
      }
  }
}
int main()
{
    char sent[1000];
    char*filename="Dictionary.txt";
    node*root=load_Dictionary();
    printf("Size of file is : %d words.\n",count(root));
    printf("Height of tree is: %d\n",height(root));
    printf("enter a sentance:",sent);
    exists(root,gets(sent));


    return 0;
}
