/********************************************************************************
* @File name: Project2.c
* @Author: H9
* @Version: 1.1
* @Date: 2021-10.16
* @Description: Program for the project2
********************************************************************************/
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

/*The node struct */
typedef struct node
{
	char text[256];//a string with a maximum length of 255(no spaces)
	int index;//an integer specifying the index of this node
	struct node* next;//a pointer to the next node	
}Node;


Node *init();
int size(Node *);
int compare(Node* , char* );
void insertAfter(Node *, int, char*);
void insertBefore(Node *, int, char*);
void delete(Node*, int);
void replace(Node*, int, char*);
void printf_all(Node *);
void Exit();
void help();

int main()
{
	//Use help() to test commands
	//help();

	Node* head = init();
	char name[5];
        int index;
        char text[20];

	while(1)
	{
		printf("A. INSERT AFTER: enter in this format: ina index text (e.g.: ina 1 “HelloWorld”)\n");
		printf("B. INSERT BEFORE: enter in this format: inb index text (e.g.: inb 1 “HelloWorld”)\n");
		printf("C. DELETE: enter in this format: del index (e.g.: del 2)\n");
		printf("D. REPLACE: enter in this format: rep index text (e.g.: rep 1 “HelloWorld”)\n");
		printf("E. PRINT: enter in this format: prn (e.g.: prn)\n");
		printf("F. EXIT: enter in this format: exit (e.g.: exit)\n");
		scanf("%s", name);
		if(getchar() ==' ')
		{
			scanf("%d",&index);
			if(getchar() == ' ')
                	{
                        	scanf("%s",text);
                	}
		}
		if(!(strcmp(name,"inb")))
		{
			//scanf("%d%s",&index,text);
			insertBefore(head, index, text);
		}
		else if(!(strcmp(name,"ina")))
		{
			//scanf("%d%s",&index,text);
			insertAfter(head, index, text);
		}
		else if(!(strcmp(name, "del")))
		{
			delete(head, index);
		}
		else if(!(strcmp(name,"rep")))
		{
			//scanf("%d%s",&index,text);
			replace(head,index,text);
		}
		else if(!(strcmp(name,"prn")))
		{
			printf_all(head);
		}
		else if(!(strcmp(name,"exit")))
		{
			Exit();
		}
		else
		{
			printf("Wrong command!\n");
			fflush(stdout);
		}
		printf("\n");
		fflush(stdout);
	}
	return 0;
}


/********************************************************
* Function name ：init()
* Description : Initialize node
* Return : The head node
**********************************************************/
Node *init()
{
        Node *head;
        head=(Node*)malloc(sizeof(Node));
        head -> next == NULL;
        return head;

}


/********************************************************
* Function name ：size
* Description : Calculates the size of the linked list
* Parameter ：
* @head : The head node of list
* Return : The size of list
**********************************************************/
int size(Node *head)
{
        int length=0;
        Node *temp=head;
        while(temp->next)
        {
                temp=temp->next;
                length++;
        }
        return length;
}


/********************************************************
* Function name ：compare
* Description : Check whether the text is repeated
* Parameter ：
* @head : The head node of list
* @text : The inserted text
* Return : 1--the text is reapted 0-- the text is not reapted
**********************************************************/
int compare(Node* head, char* text)
{
        Node *ptr = head;
        for(int i = 0; i <= size(head); i++)
        {
                if(!(strcmp(ptr->text,text)))
                {
                        //printf("YES\n");
                        return 1;
                }
                ptr = ptr->next;
        }
        //printf("NO\n");
        return 0;
}


/********************************************************
* Function name ：insertAfter
* Description : A new node containing text will be inserted after the node at position index
* Parameter ：
* @head : The head node of list
* @index : The position index after which the new node will be inserted
* @text : the text of the new node
**********************************************************/
void insertAfter(Node *head, int index, char* text)
{
  //check if text is reapted
  if(compare(head, text))
  {
          printf("Insertion of a duplicate failed\n");
          fflush(stdout);
  }
  else
  {
        //index is larger than the last index of the list
        if(index > size(head))
        {
                printf("Inserted at the end!\n");
                fflush(stdout);
                index = size(head);
        }

        Node *ptr = head;
        int i = 0;
        while(i < index)
        {
                ptr = ptr->next;
                i++;
        }
        Node *current = (Node*)malloc(sizeof(struct node));
        current->index = index+1;
	strcpy(current->text,text);
        current->next=ptr->next;
        ptr->next=current;

        //the indexes of all nodes after the new node be adjusted accordingly
        int j = current->index + 1;
        while(j <= size(head))
        {
                current = current->next;
                current->index = current->index + 1;
                j++;
        }
        printf("Insertion After Ok!\n");
        fflush(stdout);
  }
}


/********************************************************
* Function name ：insertBefore
* Description : A new node containing text will be inserted before the node at position index
* Parameter ：
* @head : The head node of list
* @index : The position index after which the new node will be inserted
* @text : the text of the new node
**********************************************************/
void insertBefore(Node *head, int index, char* text)
{
  //check if text is reapted
  if(compare(head, text))
  {
        printf("Insertion of a duplicate failed\n");
        fflush(stdout);
  }
  else
  {
          // index is larger than the last index of the list
        if(index > size(head))
        {
                printf("Inserted at the front!\n");
                fflush(stdout);
                index = 1;
        }

        Node *ptr = head;
        int i = 0;
        while(i < index-1)
        {
                ptr = ptr->next;
                i++;
        }
        Node *current = (Node*)malloc(sizeof(struct node));
        current->index = index;
        strcpy(current->text,text);
        current->next = ptr->next;
        ptr->next = current;

 	//the indexes of all nodes after the new node be adjusted accordingly
        int j = current->index + 1;
        ptr = current->next;
        while(j <= size(head))
        {
                ptr->index = ptr->index + 1;
                ptr = ptr->next;
                j++;
        }

        printf("Insertion Before Ok!\n");
        fflush(stdout);
  }
}


/********************************************************
* Function name ：delete
* Description : The node at position index will be removed
* Parameter ：
* @head : The head node of list
* @index : The position index after which the new node will be inserted
**********************************************************/
void delete(Node* head, int index)
{
        //  index is larger than the last index of the list
        if(index > size(head))
        {
                printf("No changes!\n");
                fflush(stdout);
        }
        else
        {
                Node *ptr = head;
                Node *pre;
                int i = 0;
                while(i < index)
                {
                        if(i == index -1)
                        {
                                pre = ptr;
                        }
                        ptr = ptr->next;
                        i++;
                }
                pre->next = ptr->next;
                ptr->next = NULL;

                // the indexes of all nodes after the new node be adjusted accordingly
                ptr = pre->next;
                while(i <= size(head))
                {
                        ptr->index = ptr->index - 1;
                        ptr = ptr->next;
                        i++;
                }
                printf("Deletion OK!\n");
                fflush(stdout);
        }
}


/********************************************************
* Function name ：replace
* Description : The text of the node at position index will be replaced with a new text
* Parameter ：
* @head : The head node of list
* @index : The position index after which the new node will be inserted
* @text : The new text
**********************************************************/
void replace(Node* head, int index, char* text)
{
   //The text is reapted
   if(compare(head, text))
   {
        printf("No changes!\n");
        fflush(stdout);
   }
   //Index is larger than the last index of the list,
   else
   {
        if(index > size(head))
        {
                printf("No changes!\n");
                fflush(stdout);
        }
        else
        {
                Node *ptr = head;
                int i = 0;
                while(i < index)
                {
                        ptr = ptr->next;
                        i++;
                }
                strcpy(ptr->text,text);
                printf("Replacement OK!\n");
                fflush(stdout);
        }
  }
}


/********************************************************
* Function name ：printf_all
* Description : The entire list of nodes are oriented in order
* Parameter ：
* @head : The head node of list
**********************************************************/
void printf_all(Node *head)
{
        if(size(head) == 0)
        {
                printf("Empty list!\n");
                fflush(stdout);
        }
        else
        {
                Node *ptr = head;
                while(ptr->next)
                {
                        ptr = ptr->next;
                        printf("%d. %s\n", ptr->index, ptr->text);
                        fflush(stdout);
                }
        }
}


/********************************************************
* Function name ：Exit
* Description : Exit the program
**********************************************************/
void Exit()
{
        exit(0);
}


/********************************************************
* Function name ：help
* Description : Test commands
**********************************************************/
void help()
{
	Node* headTest = init();
	printf("Help function to test command:\n");

	printf("\nTest insertAfter() and print_all()......\n");
	printf("ina 1 ABC,ina 1 DEF, ina 2 ABC:\n");
	insertAfter(headTest, 1, "ABC");
	insertAfter(headTest, 1, "DEF");
	insertAfter(headTest, 2, "ABC");
	printf_all(headTest);

	printf("\nTest insertBefore()......\n");
	printf("inb 2 GHI,inb 1 ABC:\n");
	insertBefore(headTest, 2, "GHI");
	insertBefore(headTest, 1, "ABC");
	printf_all(headTest);

	printf("\nTest delete()......\n");
	printf("del 2:\n");
	delete(headTest, 2);
	printf_all(headTest);

	printf("\nTest rep()......\n");
	printf("rep 1 DEF, rep 2 CBA:\n");
	replace(headTest, 1, "DEF");
	replace(headTest, 2, "CBA");
	printf_all(headTest);

	printf("\nTest exit()\n");
	Exit();
}
