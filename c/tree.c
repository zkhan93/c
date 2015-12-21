# include<stdio.h>
# include<stdlib.h>
typedef struct tree_node{
	int value;	
	struct tree_node* parent;
	struct tree_node* r_child;
	struct tree_node* l_child;
	
}tree_node;

typedef  struct queue_node{
	tree_node** value;
	struct queue_node* previous;
}queue_node;

void enqueue(queue_node** front,tree_node** new_node){
	if(*front=='\0'){
		queue_node* tmp_node=(queue_node*)malloc(sizeof(queue_node));
		tmp_node->value=new_node;
		tmp_node->previous='\0';
		*front=tmp_node;
		return;
	}
	queue_node* tmp_front=*front;
	while(tmp_front->previous!='\0'){
		tmp_front=tmp_front->previous;
	}
	tmp_front->previous=(queue_node*)malloc(sizeof(queue_node));
	tmp_front->previous->value=new_node;
	tmp_front->previous->previous='\0';
}

void printQueue(queue_node* front){
	queue_node* tmp_front=front;
	printf("\n------START--------\n");
	while(tmp_front!='\0'){
		printf("%d->",(*(tmp_front->value))->value);
		tmp_front=tmp_front->previous;
	}
	printf("\n------END--------\n");
}
/**
 * removes the from item from queue and return its value i.e., a pointer to tree_node
 **/ 
tree_node** dequeue(queue_node** queue){
	if(queue=='\0'){
		printf("Stack Empty\n");
		return '\0';
	}
	queue_node* top_queue_node=*queue;
	*queue=top_queue_node->previous;
	return top_queue_node->value;
}

//use of recursion to free up all the linked nodes in queue
void freeQueue(queue_node** node){
	if(*node=='\0')
		return;
	if((*node)->previous!='\0')
		freeQueue(&((*node)->previous));
	else
		free(*node);
}

//adding node in binary tree using BFS(queue)
void addNodeToTree(tree_node** tree, int value){
	//new node to insert into tree
	tree_node* new_node=(tree_node*)malloc(sizeof(tree_node));
	new_node->value=value;
	new_node->l_child='\0';
	new_node->r_child='\0';
	
	//dynamic stack
	queue_node* queue='\0';
	enqueue(&queue,tree);
	tree_node** tmp_tree='\0';
	while(queue!='\0'){
		tmp_tree=dequeue(&queue);
		if((*tmp_tree)->l_child!='\0')
			enqueue(&queue,&((*tmp_tree)->l_child));
		else{
			(*tmp_tree)->l_child=new_node;
			break;
		}
		if((*tmp_tree)->r_child!='\0')
			enqueue(&queue,&((*tmp_tree)->r_child));
		else{
			(*tmp_tree)->r_child=new_node;
			break;
		}
	}
	freeQueue(&queue);
}


//cannot be used in binary tree, useful in AVL tree but unable to implement rotation will see later
tree_node*  addNode(tree_node* head,int value){
	tree_node* child=(tree_node*)malloc(sizeof(tree_node));
	child->value=value;
	child->l_child='\0';
	child->r_child='\0';
	//if head is null return the new node
	if(head=='\0')
		return child;
	else{
		//set root node as current node
		tree_node* tmp_node=head;
		//while current node has childs (1 or 2)
		while(tmp_node!='\0' && (tmp_node->l_child!='\0' || tmp_node->r_child!='\0')){
			//if current node's value is less than or equal to the new node's value, move to left child
			if(tmp_node->value<=value){
				printf("moving to left");
				if(tmp_node->l_child=='\0')
					break;
				tmp_node=tmp_node->l_child;
			}
			//if current node's value is greater than the new node's value, move to right child
			else{
				printf("moving to right");
				if(tmp_node->r_child=='\0')
					break;
				tmp_node=tmp_node->r_child;
			}
		}
		//state:current node has no children
		//if current node's value is less than or equal to the new node's value than assign the new node as left children of the current node
		if(tmp_node->value<=value){
			tmp_node->l_child=child;
			printf("left child");
		}
		//else i.e., if current node's value greater than the new node's value then assign the new node as right child of current node
		else{
			tmp_node->r_child=child;
			printf("right child");
		}
		//return the head of new tree
		return head;
	}
}

int countHeight(tree_node* head){
	if(head=='\0')
		return 0;
	int cnt_right=countHeight(head->r_child);
	int cnt_left=countHeight(head->l_child);
	return 1+(cnt_right>cnt_left?cnt_right:cnt_left);
}
tree_node* getNodeByIndex(tree_node* head,int index){
	if(head=='\0' || index==0 || index==1)
		return head;
	tree_node* tmp_head=head;
	int len=0,tmp=index;
	while(tmp>0){
		len++;
		tmp/=2;
	}
	int path_index[len];
	tmp=index;
	int i;
	for(i=0;i<len;i++){
		path_index[i]=tmp;
		if(tmp>0)
			tmp/=2;
	}
	for(tmp=len-2;tmp>=0;tmp--){
		if(path_index[tmp]%2==0){
			if(tmp_head!='\0')
				tmp_head=tmp_head->l_child;
		}
		else{
			if(tmp_head!='\0')
				tmp_head=tmp_head->r_child;
		}
	}
	return tmp_head;
}

void printTree(tree_node* head){
	if(head=='\0')
		return;
	int i=1,total_nodes=1;
	tree_node* tmp_node;
	int height=countHeight(head)-1;
	int tabs=1,i_tabs=1;
	int m_tabs=0;
	int nodes_to_print=1;
	while(height--){
		tabs*=2;
		total_nodes*=2;
	}
	total_nodes=total_nodes*2-1;
	tabs-=1;
	i_tabs=tabs;
	m_tabs=0;
	int t_tabs,t_ntp;
	while(i_tabs>=0 && i<=total_nodes){
		t_ntp=nodes_to_print;
		t_tabs=i_tabs;
		while(t_tabs--)
			printf("\t");
		while(t_ntp--){
			tmp_node=getNodeByIndex(head,i++);
			if(tmp_node=='\0')
				printf("-");
			else
				printf("%d",tmp_node->value);
			t_tabs=m_tabs;
			while(t_tabs--)
				printf("\t");
		}
		i_tabs/=2;
		nodes_to_print*=2;
		m_tabs=(tabs*2-2*i_tabs)/(nodes_to_print-1);
		printf("\n\n");
	}
}

tree_node* getNewNode(int value){
	tree_node* new_node=(tree_node*)malloc(sizeof(tree_node));
	new_node->value=value;
	new_node->l_child='\0';
	new_node->r_child='\0';
	return new_node;
}

int main(){

/*	//queu demo
	queue_node* queue='\0';
	tree_node* tmp=(tree_node*)malloc(sizeof(tree_node));
	tmp->value=1;
	enqueue(&queue,tmp);
	printQueue(queue);
	tmp=(tree_node*)malloc(sizeof(tree_node));
	tmp->value=2;
	enqueue(&queue,tmp);
	printQueue(queue);
	tmp=(tree_node*)malloc(sizeof(tree_node));
	tmp->value=3;
	enqueue(&queue,tmp);
	printQueue(queue);
	tmp=dequeue(&queue);
	printf("dequeue %d",tmp->value);
	printQueue(queue);
	tmp=(tree_node*)malloc(sizeof(tree_node));
	tmp->value=4;
	enqueue(&queue,tmp);
	printQueue(queue);
	*/
	
	
	tree_node* head=getNewNode(1);
	int i=2;
	for(i=2;i<=15;i++){
		addNodeToTree(&head,i);
		printTree(head);
	}
/*
	head->l_child=getNewNode(3);
	head->r_child=getNewNode(2);
	head->l_child->l_child=getNewNode(4);
	head->l_child->r_child=getNewNode(6);
	head->r_child->l_child=getNewNode(5);
	head->r_child->r_child=getNewNode(29);
	
	head->l_child->l_child->l_child=getNewNode(28);
	head->l_child->l_child->r_child=getNewNode(92);
	head->l_child->r_child->l_child=getNewNode(102);
	head->l_child->r_child->r_child=getNewNode(211);
	
	head->r_child->l_child->l_child=getNewNode(122);
	head->r_child->l_child->r_child=getNewNode(123);
	head->r_child->r_child->l_child=getNewNode(214);
	head->r_child->r_child->r_child=getNewNode(215);
	printTree(head);
*/
	return 0;
}
