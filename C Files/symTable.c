#include "driver.h"
#include <stdlib.h>

node * createTable(node * top)
{
    top = NULL;
    return top;
    
}

node * pushLevel(node * top, int data)
{
    
    if (top == NULL)
    {
      
        top =(struct node *)malloc(1*sizeof(struct node));
        top->ptr = NULL;
        top->level = data;
        top->treePtr = NULL;
        top->size = 0;
    }
    else
    {
        node * temp;
        temp =(struct node *)malloc(1*sizeof(struct node));
        temp->ptr = top;
        temp->level = data;
        top = temp;
    }
    top->size++;
    
    return top;
    
    
}

node * popLevel(node * top)
{
    node * cursor;
    cursor = top;
 
    if (cursor == NULL)
    {
        
    }
    else
    {
    cursor = cursor->ptr;
    free(top);
    top = cursor;
    top->size--;
    
    }
    
    return top;
}

 
node * destroy(node * top)
{
    node * cursor;
    if(top != NULL)
    {
        
        cursor = top;
        
        while (cursor != NULL)
        {
            cursor = top->ptr;
            free(top);
            top = cursor;
            cursor = cursor->ptr;
        }
        free(cursor);
        top = NULL; 
        top->size = 0;
        return top;
    }
}
/***************************************/

void printIdentifiers(treeNode *leaf)
{
        if(leaf==NULL)
        {
                return;
        }
        

    
        //Check Flags 
        printIdentifiers(leaf->left);
        if(leaf->flags.const_flag){fprintf(symbolTableFile,"const ");}
        if(leaf->flags.static_flag){fprintf(symbolTableFile,"static ");}
        if(leaf->flags.short_flag){fprintf(symbolTableFile,"short ");}
        if(leaf->flags.long_flag){fprintf(symbolTableFile,"long ");}
        if(leaf->flags.float_flag){fprintf(symbolTableFile,"float ");}
        if(leaf->flags.double_flag){fprintf(symbolTableFile,"double ");}
        if(leaf->flags.signed_flag){fprintf(symbolTableFile,"signed ");}
        if(leaf->flags.unsigned_flag){fprintf(symbolTableFile,"unsigned ");}
        if(leaf->flags.struct_flag){fprintf(symbolTableFile,"struct ");}
        if(leaf->flags.enum_flag){fprintf(symbolTableFile,"enum ");}
        if(leaf->flags.typedef_flag){fprintf(symbolTableFile,"typedef ");}
        if(leaf->flags.char_flag){fprintf(symbolTableFile,"char ");}
        if(leaf->flags.int_flag){fprintf(symbolTableFile,"int ");}
        if(leaf->flags.volatile_flag){fprintf(symbolTableFile,"volatile ");}
        if(leaf->flags.void_flag){fprintf(symbolTableFile,"void ");}
        
        fprintf(symbolTableFile,"%s    ",leaf->name);
        if(leaf->dataC != NULL){
        
            fprintf(symbolTableFile,"Value: %s\n",leaf->dataC);
        }
        
        else if(leaf->dataI != NULL){
            fprintf(symbolTableFile,"Value: %d\n",leaf->dataI);
            
        }
        
        else if(leaf->flags.float_flag){
                 fprintf(symbolTableFile,"Value: %f\n",leaf->dataD);
        
        }
        else{
            fprintf(symbolTableFile,"Value: None \n");
        
        
        }
        printIdentifiers(leaf->right);
}

treeNode * insertIdentifier(treeNode *leaf,int data, flagContainer flagInfo)
{
        if(leaf==NULL)
        {
              
                treeNode *temp;
                temp = (treeNode *)malloc(sizeof(treeNode));
                temp -> id = data;
                temp -> left = temp -> right = NULL;
                temp->flags.const_flag = flagInfo.const_flag;
                temp->flags.static_flag = flagInfo.static_flag;
                temp->flags.short_flag = flagInfo.short_flag;
                temp->flags.long_flag = flagInfo.long_flag;
                temp->flags.float_flag = flagInfo.float_flag;
                temp->flags.double_flag = flagInfo.double_flag;
                temp->flags.signed_flag = flagInfo.signed_flag;
                temp->flags.unsigned_flag = flagInfo.unsigned_flag;
                temp->flags.struct_flag = flagInfo.struct_flag;
                temp->flags.enum_flag = flagInfo.enum_flag;
                temp->flags.typedef_flag = flagInfo.typedef_flag;
                temp->flags.char_flag = flagInfo.char_flag;
                temp->flags.int_flag = flagInfo.int_flag;
                temp->flags.auto_flag = flagInfo.auto_flag;
                temp->flags.register_flag = flagInfo.register_flag;
                temp->flags.extern_flag = flagInfo.extern_flag;
                return temp;
        }

        if(data >(leaf->id))
        {
                leaf->right = insertIdentifier(leaf->right,data, flagInfo);
        }
        else if(data < (leaf->id))
        {
                leaf->left = insertIdentifier(leaf->left,data, flagInfo);
        }
        
          

        return leaf;

}

treeNode * deleteIdentifier(treeNode *leaf, int data)
{
        treeNode *temp;
        if(leaf==NULL)
        {
                printf("Element Not Found");
        }
        else if(data < leaf->id)
        {
                leaf->left = deleteIdentifier(leaf->left, data);
        }
        else if(data > leaf->id)
        {
                leaf->right = deleteIdentifier(leaf->right, data);
        }
        else
        {
                if(leaf->right && leaf->left)
                {
                        temp = leaf->right;
                        while(temp->left!= NULL){
                            temp = leaf->left;
                        }

                        leaf -> id = temp->id; 
                        leaf -> right = deleteIdentifier(leaf->right,temp->id);
                }
                else
                {
                        temp = leaf;
                        if(leaf->left == NULL)
                                leaf = leaf->right;
                        else if(leaf->right == NULL)
                                leaf = leaf->left;
                        free(temp); 
                }
        }
        return leaf;

}

treeNode * findIdentifier(treeNode *leaf, int data)
{
        if(leaf==NULL)
        {
               
                return NULL;
        }
        if(data > leaf->id)
        {
                
                return findIdentifier(leaf->right,data);
        }
        else if(data < leaf->id)
        {
                
                return findIdentifier(leaf->left,data);
        }
        else
        {

                return leaf;
        }
}


void printTable(node * top)
{
    node * cursor;
    cursor = top;
 
    if (cursor == NULL)
    {
        return;
        
    }
 
    while (cursor != NULL)
    {
        fprintf(symbolTableFile,"%s\n", "Level:");
        fprintf(symbolTableFile,"%d\n", cursor->level);
        fprintf(symbolTableFile,"%s\n", "IDS at that Level:");
        printIdentifiers(cursor->treePtr);
        cursor = cursor->ptr;
    }
    
    
 }
 

treeNode* shadows(int id, node * top){

    int i = 0;
    node * cursor;
    cursor = top->ptr;
     
    
    if(cursor == NULL)
    {
        return NULL; 
        
    }
    
   
     while (cursor != NULL)
    {
    
        if( findIdentifier(cursor->treePtr, id ) != NULL)
        {
            printf("but... it shadows a variable in level %d\n", cursor->level );
            return cursor->treePtr;
        }
        cursor = cursor->ptr;

    }

    return NULL;


}


/* LISTITEM */ 


treeNode * deleteTree(treeNode *leaf){

        if(leaf->left !=NULL)
        {
                return deleteTree(leaf->right);
        }
        if(leaf->right !=NULL)
        {
                return deleteTree(leaf->right);
        }

        free(leaf);
        leaf = NULL;


}
