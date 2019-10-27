#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct node
{
    int data,height;
    struct node *left;
    struct node *right;
};
struct node *root = NULL;

int max(int a,int b)
{
    return (a>b) ? a : b;
}

int Height(struct node *root)
{
    if (root == NULL)
        return 0;
    return
        root->height;
}

int BalanceFactor(struct node *root)
{
    if(root == NULL)
        return 0;
    else
        return Height(root->left) - Height(root->right);
}

struct node *RightRotate(struct node *root) //LeftLeft
{
    struct node *temp1 = root -> left; //New Root
    struct node *temp2 = temp1 -> right;
    //perform right rotation
    temp1 -> right = root;
    root -> left = temp2;
    //update heights
    root -> height = 1 + max(Height(root->left), Height(root->right));
    temp1 -> height = 1 + max(Height(temp1->left), Height(temp1->right));
    //return New Root
    return temp1;
}

struct node *LeftRotate(struct node *root) //RightRight
{
    struct node *temp1 = root -> right; //New Root
    struct node *temp2 = temp1 -> left;
    //perform left rotation
    temp1 -> left = root;
    root -> right = temp2;
    //update heights
    root -> height = 1 + max(Height(root->left), Height(root->right));
    temp1 -> height = 1 + max(Height(temp1->left), Height(temp1->right));
    //return New Root
    return temp1;
}

struct node *Insert(struct node *root,int data)
{
    //STEP 1: PERFORM STANDARD BST INSERTION
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
        root -> left = Insert(root -> left,data);
    }
    else
    {
        root -> right = Insert(root -> right,data);
    }

    //STEP 3 & 4: AFTER INSERTION FOLLOWING FUNCTIONS ARE PERFORMED TO CONVERT BST INTO AVL

    root -> height = 1 + max(Height(root->left),Height(root->right)); //update the height of this ancestor

    int bf = BalanceFactor(root); //check the balance factor of this ancestor node whether this node became unbalanced or not

    //If this node becomes unbalanced, then there are 4 cases
    if(bf > 1 && data < root->left->data) //LeftLeft
    {
        return RightRotate(root);
    }

    if(bf < -1 && data > root->right->data) //RightRight
    {
        return LeftRotate(root);
    }

    if(bf > 1 && data > root->left->data) //LeftRight
    {
        root -> left = LeftRotate(root -> left); //converts into LeftLeft
        return RightRotate(root);
    }

    if(bf < -1 && data < root->right->data) //RightLeft
    {
        root -> right = RightRotate(root -> right); //converts into RightRight
        return LeftRotate(root);
    }

    return root;
}

struct node *Min(struct node *root)
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
    //STEP 1: PERFORM STANDARD BST DELETE
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
            struct node *temp = Min(root -> right); //smallest element of the Right Subtree
            root -> data = temp -> data;
            root -> right = Delete(root -> right,temp -> data);
        }

    }
    //If tree had only one node
    if(root == NULL)
        return root;

    //STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root -> height = 1 + max(Height(root->left),Height(root->right));

    //STEP 3: GET THE BALANCE FACTOR OF THIS NODE
    int bf = BalanceFactor(root);

    //If this node becomes unbalanced, then there are 4 cases
    if(bf > 1 && BalanceFactor(root -> left) >= 0)
    {
        return RightRotate(root);
    }

    if(bf < -1 && BalanceFactor(root -> right) <= 0)
    {
        return LeftRotate(root);
    }

    if(bf > 1 && BalanceFactor(root -> left) < 0)
    {
        root -> left = LeftRotate(root -> left);
        return RightRotate(root);
    }

    if(bf < -1 && BalanceFactor(root -> right) > 0)
    {
        root -> right = RightRotate(root -> right);
        return LeftRotate(root);
    }

    return root;
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

int main()
{
    int x,n,y,data,Height;
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
        printf("\n3. In Order");
        printf("\n4. Pre Order");
        printf("\n5. Post Order");
        printf("\n6. Binary Search Tree Check");
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
                printf("Tree is ");
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
        case 4:
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
        case 5:
            {
                printf("Post Order: ");
                PostOrder(root);
                printf("\n");
            }
            break;
        case 6:
            {
                if(IsBst(root)==true)
                    printf("\nGiven Tree is a Binary Search Tree\n");
                else
                    printf("\nGiven Tree is not a Binary Search Tree\n");
                if(root == NULL)
                {
                    printf("Tree is empty\n");
                    break;
                }
            }
            break;
        case 0:
            break;
        }
    }while(x>0);
}
