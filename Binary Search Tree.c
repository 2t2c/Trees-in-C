#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};
struct node *root = NULL;

struct node *Insert(struct node *root,int data)
{
    if(root == NULL)
    {
        struct node *NewNode = (struct node*)malloc(sizeof(struct node));
        NewNode -> data = data;
        NewNode -> left = NULL;
        NewNode -> right = NULL;
        root = NewNode; //a new new node is created for insertion after first root
    }
    else if(data <= root -> data)
    {
        root -> left = Insert(root -> left, data);
    }
    else
    {
        root -> right = Insert(root -> right, data);
    }
    return root;
}

bool Search(struct node *root,int data) //using recursion
{
    if(root == NULL)
        return false;
    else if(root -> data == data)
        return true;
    else if(data <= root -> data)
        return Search(root -> left,data);
    else
        return Search(root -> right,data);
}

int FindMin(struct node *root) //using recursion
{
    if(root == NULL)
    {
        printf("\nTree is empty");
        return 0;
    }
    else if(root -> left == NULL)
    {
        printf("Smallest Element: %d",root -> data);
        printf("\n");
        return 0;
    }
    return FindMin(root -> left);
}

void FindMax(struct node *root)
{
    if(root == NULL)
    {
        printf("\nTree is empty");
    }
    while(root -> right!=NULL)
    {
        root = root -> right;
    }
    printf("Largest Element: %d",root -> data);
    printf("\n");
}

int FindHeight(struct node *root)
{
    if(root == NULL)
    {
        return -1;
    }
    else
    {
        int LeftHeight = FindHeight(root -> left);
        int RightHeight = FindHeight(root -> right);

        if(LeftHeight>RightHeight)
        {
            return LeftHeight + 1;
        }
        else
        {
            return RightHeight + 1;
        }
    }
}

void InOrder(struct node *root)
{
    if(root!=NULL)
    {
        InOrder(root->left);
		printf("%d ",root->data);
		InOrder(root->right);
    }
}

void PreOrder(struct node *root)
{
	if(root!=NULL)
    {
		printf("%d ",root->data);
        PreOrder(root->left);
		PreOrder(root->right);
    }
}

void PostOrder(struct node *root)
{
	if(root!=NULL)
    {
        PostOrder(root->left);
		PostOrder(root->right);
		printf("%d ",root->data);
    }
}

void PrintLevelOrder(struct node *root,int level)
{
    if(root == NULL)
        {
            return;
        }
    else
       {
            if(level == 1)
            {
                printf("%d ",root -> data);
            }
            else if(level > 1)
            {
                PrintLevelOrder(root->left, level-1);
                PrintLevelOrder(root->right, level-1);
            }
       }
}

void LevelOrder(struct node *root)
{
    int height = FindHeight(root);
    int i;
    for(i=1; i<=height+1; i++)
    {
        PrintLevelOrder(root,i);
    }
}

bool IsBstUtil(struct node *root,int min,int max)
{
    if(root == NULL)
        return true;
    if(min < root -> data && root -> data < max && IsBstUtil(root->left,min,root->data) && IsBstUtil(root->right,root->data,max))
        return true;
    else
        return false;
}

bool IsBst()
{
    return IsBstUtil(root,INT_MIN,INT_MAX);
}

struct node *Min(struct node*root)
{
    if(root == NULL)
        return root;
    while(root -> left!=NULL)
    {
        root = root -> left;
    }
    return root;
}

struct node *Delete(struct node *root,int data)
{
    if(root == NULL)
        return root;
    else if(data < root -> data)
        root -> left = Delete(root -> left,data);
    else if(data > root -> data)
        root -> right = Delete(root -> right,data);
    else
    {
        //CASE 1: No Child
        if(root -> left == NULL && root -> right == NULL)
        {
            free(root);
            root = NULL;
            return root; //when there is no child left to be deleted
        }
        //CASE 2: One Child,(right)
        else if(root -> left == NULL)
        {
            struct node *temp;
            temp = root;
            root = root -> right;
            free(temp);
        }
        //CASE 2: One Child,(left)
        else if(root -> right == NULL)
        {
            struct node *temp;
            temp = root;
            root = root -> left;
            free(temp);
        }
        //CASE 3: Two Children
        else
        {
            struct node *temp = Min(root -> right);
            root -> data = temp -> data; //setting the minimum of right subtree as the root,smallest element of the Right Subtree
            root -> right = Delete(root -> right,temp -> data);
        }
    }
    return root;
}

int main()
{
    int x,n,y,data,height;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
    {
        printf("Enter Data[%d]: ",i);
        scanf("%d", &data);
        root = Insert(root,data);
    }
    printf("\nTree is: ");
    InOrder(root);
    printf("\n");
    do
    {
        printf("\n1. Insert");
        printf("\n2. Delete");
        printf("\n3. Search");
        printf("\n4. In Order");
        printf("\n5. Pre Order");
        printf("\n6. Post Order");
        printf("\n7. Level Order");
        printf("\n8. Smallest Element");
        printf("\n9. Largest Element");
        printf("\n10. Height Of The Tree");
        printf("\n11. Binary Search Tree Check");
        printf("\n0. Exit");
        printf("\nEnter Choice: ");
        scanf("%d", &x);
        printf("\n");
        switch(x)
        {
        case 1:
            {
                printf("Enter Data: ");
                scanf("%d", &data);
                root = Insert(root,data);
                printf("\nTree is: ");
                InOrder(root);
                printf("\n");
            }
            break;
        case 2:
            {
                printf("Enter data to be deleted: ");
                scanf("%d", &y);
                root = Delete(root,y);
                printf("\nElement Deleted: %d\n",y);
                printf("Tree is: ");
                if(root == NULL)
                {
                    printf("empty\n");
                }
                InOrder(root);
                printf("\n");
            }
            break;
        case 3:
            {
                printf("Enter a number to search: ");
                scanf("%d", &x);

                if(Search(root,x)==true)
                {
                    printf("\nNumber Found\n");
                }
                else
                {
                    printf("\nNumber Not Found\n");
                }
            }
            break;
        case 4:
            {
                if(root == NULL)
                {
                    printf("Tree is empty\n");
                    break;
                }
                printf("In Order: ");
                InOrder(root);
                printf("\n");
            }
            break;
        case 5:
            {
                if(root == NULL)
                {
                    printf("Tree is empty\n");
                    break;
                }
                printf("Pre Order: ");
                PreOrder(root);
                printf("\n");
            }
            break;
        case 6:
            {
                if(root == NULL)
                {
                    printf("Tree is empty\n");
                    break;
                }
                printf("Post Order: ");
                PostOrder(root);
                printf("\n");
            }
            break;
        case 7:
            {
                if(root == NULL)
                {
                    printf("Tree is empty\n");
                    break;
                }
                printf("Level Order: ");
                LevelOrder(root);
                printf("\n");
            }
            break;
        case 8:
            {
                FindMin(root);
            }
            break;
        case 9:
            {
                FindMax(root);
            }
            break;
        case 10:
        {
                height = FindHeight(root);
                printf("Height: %d\n",height);
        }
        break;
        case 11:
            {
                if(IsBst(root)==true)
                    printf("\nGiven Tree is a Binary Search Tree\n");
                else
                    printf("\nGiven Tree is not a Binary Search Tree\n");
            }
            break;
        case 0:
            break;
        }
    }while(x>0);
}
