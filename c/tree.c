# include<stdio.h>
# include<stdlib.h>
typedef struct node{
	int value;	
	struct node* parent;
	struct node* r_child;
	struct node* l_child;
	
}node;
node*  addNode(node* head,int value){
	node* child=(node*)malloc(sizeof(node));
	child->value=value;
	child->l_child='\0';
	child->r_child='\0';
	if(head=='\0')
		return child;
	else{
		node* tmp_node=head;		
		while(tmp_node->l_child!='\0' && tmp_node->r_child!='\0'){
			if(tmp_node->value<=value){
				tmp_node=tmp_node->l_child;
			}
			else{
				tmp_node=tmp_node->r_child;
			}
		}
		if(tmp_node->value<=value)
			tmp_node->l_child=child;
		else
			tmp_node->r_child=child;
		return head;
	}
}

int countHeight(node* head){
	if(head=='\0')
		return 0;
	int cnt_right=countHeight(head->r_child);
	int cnt_left=countHeight(head->l_child);
	return 1+(cnt_right>cnt_left?cnt_right:cnt_left);
}
node* getNodeByIndex(node* head,int index){
	if(head=='\0' || index==0 || index==1)
		return head;
	node* tmp_head=head;
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
		if(path_index[tmp]%2==0)
			tmp_head=tmp_head->l_child;
		else
			tmp_head=tmp_head->r_child;
	}
	return tmp_head;
}

void printTree(node* head){
	if(head=='\0')
		return;
	int i=1,total_nodes=1;
	node* tmp_head=head;
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
			printf("%d",getNodeByIndex(head,i++)->value);
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

node* getNewNode(int value){
	node* new_node=(node*)malloc(sizeof(node));
	new_node->value=value;
	new_node->l_child='\0';
	new_node->r_child='\0';
	return new_node;
}

int main(){
	node* head=getNewNode(1);
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
	return 0;
}
