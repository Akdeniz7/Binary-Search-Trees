/* Name: Ahmet Sezer Akdeniz Number: 190254006 COM_201_HW_2 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAX_FILE_NAME 100
struct treeNode {
       char *data[20];
       int count;
       struct treeNode *leftPtr, *rightPtr;
 };

int number;
typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

int countNodes(TreeNode *leaf)
{
    int count = 1;
    if (leaf == NULL)
        return 0;
    else
    {
        count = count + countNodes(leaf->leftPtr);
        count = count + countNodes(leaf->rightPtr);
        return count;
     }
}

//depth of tree
int depth(TreeNode *root) {
    if(root == NULL){
        return -1;
    }
    int sum=0;
    int rdepth = depth(root->rightPtr);
    int ldepth = depth(root->leftPtr);

    if(ldepth>rdepth){
        sum = ldepth +1;
    }
    if(rdepth > ldepth){
        sum = rdepth + 1;
    }
    return sum;
}

/*Inserting nodes to tree*/
void insertNode (TreeNodePtr *treePtr,char word[20]){
    TreeNode *temp = NULL;
    if(*treePtr == NULL)
    {
        temp = (TreeNode *)malloc(sizeof(TreeNode));
        temp->leftPtr = NULL;
        temp->rightPtr = NULL;
        temp->count=number;
        strcpy(temp->data, word);
        *treePtr = temp;

    }
    else if(strcmp(word,(*treePtr)->data)<0){


        insertNode(&((*treePtr)->leftPtr),word);
    }
    else if (strcmp(word,(*treePtr)->data)>0){


        insertNode(&((*treePtr)->rightPtr),word);
    }
    else{
        number++;
    }
}

/*for sorting alphabetically*/
void inOrder(TreeNodePtr treePtr){
    if(treePtr!=NULL){
        inOrder(treePtr->leftPtr);
        printf("%s \t %d Time \n", treePtr->data, treePtr->count+1);
        //printf("%d\n", treePtr->count);
        inOrder(treePtr->rightPtr);
    }
}

void randOrder(TreeNodePtr treePtr) {
   if (treePtr != NULL) {
      randOrder(treePtr->rightPtr);
      printf("%s \t %d Time \n", treePtr->data, treePtr->count+1);
      inOrder(treePtr->leftPtr);

   }
}

void search(char* data, TreeNode* leaf){
    int res;
    if( leaf != NULL ) {
        res = strcmp(data, leaf->data);
        if( res > 0)
            search( data, leaf->leftPtr);
        else if( res < 0)
            search( data, leaf->rightPtr);
        else
            printf("\n%s \t Depth -> %d \t %d Time\n", data, depth(leaf), number);
    }
    else
    	printf("\n The searched data is not in the tree\n");

    return;
}


int main(){

    TreeNodePtr rootPtr=NULL;
    int count = 0;  // Line counter (result)
    int choice;
    char val[50];
    char filename[MAX_FILE_NAME];
    char first[20], *karakter;
    FILE *fp;

    // Get file name from user.
    printf("Enter file name(Ex: input.txt): ");
    scanf("%s", filename);

    // Open the file
    fp = fopen(filename, "r");

    // Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }
    else{
        do{
            count++;
            karakter = fgets(first,20,fp);
            if(karakter !=NULL){
                 //insensitive to the capital word
                 for (int i = 0; i < strlen(first); i++) {
                     first[i] = tolower(first[i]);
                 }
                //printf("%s",first); //check file has been read or not
                insertNode(&rootPtr,first);
            }
        }while(karakter !=NULL);
    }
    printf("\nIn total %d the word was read from the file and saved in the binary search tree.\n", count-1);
    printf("Number of nodes of the binary search tree: %d \n", countNodes(rootPtr));
    printf("The depth of binary search tree: %d\n", depth(rootPtr) );
    fclose(fp);

    while(choice != 4){
        printf("1-) Print Different Words \n");
        printf("2-) Print Different Words in Alphabetical Order \n");
        printf("3-) Search word \n");
        printf("4-) Exit \nEnter your choice: ");
        scanf("%d",&choice);
        if(choice == 1){
            system("cls");
            randOrder(rootPtr);
        }
        else if (choice == 2){
            system("cls");
            inOrder(rootPtr);
        }
        else if (choice == 3){
            printf("\nEnter element to search :");
            scanf("%s", &val);
            if( rootPtr == NULL ) {
            printf("There is no data in the tree. Build a tree.\n");
            }
            search(val, rootPtr);
        }
        else if (choice == 4){
            return 0;
        }
        else{
            printf("ERROR");
            return 0;
        }
    }
   // system("PAUSE");
}
