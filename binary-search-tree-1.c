/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node { //노드 구성 구조체 
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h); // 바이너리 서치 트리 초기화 함수 

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
int cnt;


int main()
{
	char command; // 사용자에게 커맨드 입력 받을 변수 선언 
	int key; // 키값 변수 
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	
	printf("[------- [이상호] [2018038016] -------]");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자에게 커맨드 입력 받음 

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); // BST 초기화 
			break;
		case 'q': case 'Q':
			freeBST(head); // 동적할당 해제 
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); // 입력받은 키값의 노드를 삽입 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key); // 단말노드 삭제 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);  // 재귀호출 사용하지 않고 탐색 
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key); // 재귀호출을 통해 탐색 
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); //중위순회 
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); // 전위순회 
			break;
		case 't': case 'T':
			postorderTraversal(head->left); // 후위순회 
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr) //중위 순회 함수 
{
	   if(ptr) //ptr이 NULL이 아니면 
	   {
	   	    inorderTraversal(ptr->left); //왼쪽  순회
			printf("[%d]", ptr -> key); // 값 출력
			inorderTraversal(ptr->right);//오른쪽 순회 
	   }

}

void preorderTraversal(Node* ptr) //전위 순회 함수 
{
       if(ptr) //ptr이 NULL이 아니면 
	   {
	   	    printf("[%d]",ptr->key); // 먼저 값을 찍으면서 내려감 
	   	    preorderTraversal(ptr->left); //왼쪽 순회 
	   	    preorderTraversal(ptr->right); //오른쪽 순회 
		} 
}

void postorderTraversal(Node* ptr) //후위 순회 함수 
{
       if(ptr) //ptr이 NULL이 아니면
	   {
	   	    postorderTraversal(ptr->left); //왼쪽 순회 
			postorderTraversal(ptr->right); //오른쪽 순회 
			printf("[%d]",ptr->key);  //키값 출력 
		} 
}


int insert(Node* head, int key) //키값을 삽입하는 함수 
{
      Node* node = (Node*)malloc(sizeof(Node)); // 삽입될 노드 동적 할당
	  Node* lead = head->left; // 트리내에서 움직을 포인터를 루트로 설정
	  node->key=key; //새로만들 노드에 키값 삽입
	  node->left = NULL; //초기 값 NULL로 세팅 
	  node->right = NULL; 
	  
	  if(head->left ==NULL) // 트리가 비어있으면 root 노드가 없으면
	  {
	  	     head->left=node; //새로만든 노드 삽입
			 return 0; //함수 탈출 
	   } 
	   
	  while(lead) // 리드가 유효하면 (헤드노드 이외에 노드가 하나이상 있으면)
	  {
	  	    if(key == lead->key)  // 리드가 기리키는 노드의 키값과 일치할 경우 
	  	        return 0;  
	  	    else if(key < (lead->key))// 노드의 키값보다 작으면    
	  	    {
	  	        if(lead->left != NULL)// 리드의 다음위치가 비어있지 않으면 
	  	        {
	  	        	lead=lead->left; // 리드를 옮긴다 
				  }
				else // 리드의 다음위치가 비어있다면 
				{
					 lead->left=node; // 새로만든 노드 삽입
					 return 0; //함수 탈출 
				  }  
			  }
			
			else if(key > (lead->key))//리드가 가리키는 노드 키값 보다 클 경우  
			{
				if(lead->right != NULL) // 리드의 다음위치가 비어있지 않으면 
				{
					lead=lead->right; //리드를 옮긴다 
				}
				else //리드의 다음위치가 비어있다면 
				{
				    lead->right=node; //그곳에 새로만든 노드 삽입
					return 0; // 함수 탈출 
				}
			}
	   } 
	  
	  return 0;
}

int deleteLeafNode(Node* head, int key) //키값을 입력받아 그키값을 갖는 노드를 삭제 
{
      Node* lead=NULL; // 탐색하는 노드의 위치 노드 
      Node* pre = NULL; // lead의 동작을 기억하는 포인터
      
      lead = head->left; // 루트노드 삽입
	  
	  if(lead = NULL) //트리에 노드가 없으면
	  {
	  	     printf("트리에 노드가 존재하지 않습니다. \n");
			 return 0; //함수 탈출 
	   } 
	  
	  
	  while (lead) // 트리에 노드가 하나이상 있다면 
	  {
	  	    if((lead->key == key) && (lead->left=NULL) && (lead->right == NULL)) //key와 동일하고 리프노드일경우
			{
				  if(pre->key >= lead->key) // 현재노드가 이전노드보다 값이 작으면
				      pre->left = NULL; // 현재 노드가 연결되었던 링크 NULL 로 초기화
				  else
				      pre->right = NULL; //현재 노드가 연결되었던 링크 NULL 로 초기화
				  
				  free(lead); //key와 동일한 필드를 갖는 노드를 삭제한다
				  
				  return 0;	  	   
			 } 
			 
			else if (lead->key == key)// 키값과 같은 노드지만 리프노드가 아닌 경우의수
			{
				printf("이 값은 리프노드가 아닙니다.\n");
				return 0; 
			 } 
			
			else if (lead->key < key)// 키값이 현재 노드의 값보다 클 경우 
			{
				pre=lead; 
				lead = lead->right; //현재노드의 오른쪽으로 이동 
			}
			
		    else if (lead->key > key)// 키값이 현재 노드의 값 보다 작을 경우
			{
				pre=lead;
				lead=lead->left; // 현재노드의 왼쪽으로 이동 
			 } 
	  }
	 	  
	   printf("입력한 값이 노드에 없습니다.\n");
	   
	   return 0; 
}

Node* searchRecursive(Node* ptr, int key) // 재귀적으로 동일한 키값을 갖는 노드를 탐색한다 
{
       if (!ptr) // 트리가 비어있을 경우  
          return NULL; 
       
	   else if (key == ptr->key) //키값과 동일한 값을 갖는 노드가 존재할 경우
	      return ptr;  // ptr주소리턴
	      
	   else if (key < ptr->key) // 키값이 현재 노드보다 값이 작으면
	      return searchRecursive(ptr->left,key); // 현재 노드의 왼쪽으로 가야하기때문에
	      
	   else 	   
		  return searchRecursive(ptr->right,key); // 현재 노드의 오른쪽으로 가야하기 때문에 	   
}

Node* searchIterative(Node* head, int key) // 반복방식으로 동일한 키값을 갖는 노드를 탐색한다 
{
       Node* ptr = head->left; // head 자체가 넘어오므로 head left로 초기화 
       
       while(ptr) // 비어있지 않을때 까지 반복
	   {
	   	    if(key == ptr->key) //키값이 같은 경우
			   return ptr; 
			
			else if(key < ptr->key) //키값이 작은 경우
			   ptr = ptr->left; // 탐색노드 왼쪽으로 이동   
			
			else
			   ptr = ptr->right; // 탐색노드 오른쪽으로 이동   
		} 
		
		return NULL; //키와 동일한 값을 갖는 노드가 없으면 널값 리턴 
}


int freeBST(Node* head)
{
       Node *lead = NULL;
       
       if (cnt == 0) //루트노드로 시작 
	   {
	   	    lead = head->left;
			cnt++; 
		} 
		
		if(lead) //트리의 헤드가 비어있지 않으면
		// 후위순회 방식으로 맨아래 리프노드에서 차례로 노드 동적할당 해제 
		{
			freeBST(lead->left);
			freeBST(lead->right);
			
			if(lead->left != NULL)
			    lead->left = NULL;
			
			else if ( lead->right != NULL)
			    lead->right = NULL;
			
			free(lead); // 해당 노드 해제
			return 0;	    
		 } 
       
       free(head); //헤드 동적할당 해제
	   
	   return 0; 
}

