#include <stdio.h>
#include <stdlib.h>


struct Node_bst{

	int data ;
	struct Node_bst *left ;
	struct Node_bst *right ;

} ;

struct Node_avl{

	int data ;
	struct Node_avl *left ;
	struct Node_avl *right ;
	int height ;

} ;


struct Node_type2_bst{

	struct Node_bst *pointer ;
	struct Node_type2_bst *next ;

} ;


struct Node_type2_avl{

	struct Node_avl *pointer ;
	struct Node_type2_avl *next ;

} ;


int max(int a, int b){

	if(a>=b){
		return a ;
	}
	else{
		return b ;
	}

}


int in_between(int x, int a, int b){

	if(x>=a && x<=b){
		return 1 ;
	}
	else if(x<=a && x>=b){
		return 1 ;
	}
	else{
		return 0 ;
	}

}


int should_print(char query){

	if((query=='T' || query=='H') || (query=='A' || query=='U')){
		return 0 ;
	}
	else{
		return 1 ;
	}

}


struct Node_bst* delete_tree_bst(struct Node_bst *root){

	if(root==NULL){
		return root ;
	}
	else{
		root->left = delete_tree_bst(root->left) ;
		root->right = delete_tree_bst(root->right) ;
		free(root) ;
		root = NULL ;
		return root ;
	}

}


struct Node_avl* delete_tree_avl(struct Node_avl *root){

	if(root==NULL){
		return root ;
	}
	else{
		root->left = delete_tree_avl(root->left) ;
		root->right = delete_tree_avl(root->right) ;
		free(root) ;
		root = NULL ;
		return root ;
	}

}


void clear_trees(struct Node_bst **root1, struct Node_avl **root2, char query, int *tree_type){

	if(query == 'T' || query== 'H'){
		*root1 = delete_tree_bst(*root1) ;
		*root2 = delete_tree_avl(*root2) ;
		if(query == 'T'){
			*tree_type = 0 ;
		}
		else if(query == 'H'){
			*tree_type = 1 ;
		}
	}

}


struct Node_type2_bst* push_stack_bst(struct Node_type2_bst **top, struct Node_bst *point){

	if(point==NULL){
		return *top ;
	}
	struct Node_type2_bst *temp = (struct Node_type2_bst *)malloc(sizeof(struct Node_type2_bst)) ;
	temp->pointer = point ;
	if(top==NULL){
		temp->next = NULL ;
	}
	else{
		temp->next = *top ;
	}
	*top = temp ;
	return *top ;

}



struct Node_type2_avl* push_stack_avl(struct Node_type2_avl **top, struct Node_avl *point){

	if(point==NULL){
		return *top ;
	}
	struct Node_type2_avl *temp = (struct Node_type2_avl *)malloc(sizeof(struct Node_type2_avl)) ;
	temp->pointer = point ;
	if(top==NULL){
		temp->next = NULL ;
	}
	else{
		temp->next = *top ;
	}
	*top = temp ;
	return *top ;

}


struct Node_bst* pop_stack_bst(struct Node_type2_bst **top){

	struct Node_type2_bst *temp = *top ;
	struct Node_bst *value = temp->pointer ;
	*top = (*top)->next ;
	temp->next = NULL ;
	temp->pointer = NULL ;
	free(temp) ;
	return value ;

}


struct Node_avl* pop_stack_avl(struct Node_type2_avl **top){

	struct Node_type2_avl *temp = *top ;
	struct Node_avl *value = temp->pointer ;
	*top = (*top)->next ;
	temp->next = NULL ;
	temp->pointer = NULL ;
	free(temp) ;
	return value ;

}


struct Node_type2_bst* enqueue_bst(struct Node_type2_bst **front, struct Node_type2_bst **back, struct Node_bst *point){

	if(point==NULL){
		return *back ;
	}
	struct Node_type2_bst *temp = (struct Node_type2_bst *)malloc(sizeof(struct Node_type2_bst)) ;
	temp->pointer = point ;
	temp->next = NULL ;
	if(*front==NULL && *back==NULL){
		*front = temp ;
		*back = temp ;
	}
	else{
		(*back)->next = temp ;
		(*back) = temp ;
	}
	return *back ;

}


struct Node_type2_avl* enqueue_avl(struct Node_type2_avl **front, struct Node_type2_avl **back, struct Node_avl *point){

	if(point==NULL){
		return *back ;
	}
	struct Node_type2_avl *temp = (struct Node_type2_avl *)malloc(sizeof(struct Node_type2_avl)) ;
	temp->pointer = point ;
	temp->next = NULL ;
	if(*front==NULL && *back==NULL){
		*front = temp ;
		*back = temp ;
	}
	else{
		(*back)->next = temp ;
		(*back) = temp ;
	}
	return *back ;

}


struct Node_bst* dequeue_bst(struct Node_type2_bst **front, struct Node_type2_bst **back){

	struct Node_type2_bst *temp = *front ;
	struct Node_bst *value = temp->pointer ;
	*front = (*front)->next ;
	if((*front)==NULL){
		*back = NULL ;
	}
	temp->next = NULL ;
	temp->pointer = NULL ;
	free(temp) ;
	temp = NULL ;
	return value ;

}


struct Node_avl* dequeue_avl(struct Node_type2_avl **front, struct Node_type2_avl **back){

	struct Node_type2_avl *temp = *front ;
	struct Node_avl *value = temp->pointer ;
	*front = (*front)->next ;
	if((*front)==NULL){
		*back = NULL ;
	}
	temp->next = NULL ;
	temp->pointer = NULL ;
	free(temp) ;
	temp = NULL ;
	return value ;

}


int give_height_avl(struct Node_avl *node){
    
    if(node == NULL){
        return -1 ;
    }
    else{
        return node->height ;
    }
    
}


int update_height_bst(struct Node_bst *node){

	if(node == NULL){
		return -1 ;
	}
	else{
		return 1 + max(update_height_bst(node->left),update_height_bst(node->right)) ;
	}

}


int update_height_avl(struct Node_avl *node){

	if(node == NULL){
		return -1 ;
	}
	else{
		return 1 + max(give_height_avl(node->left),give_height_avl(node->right)) ;
	}

}


int adjusted_height_bst(struct Node_bst *node){

	if(node==NULL){
		return 0 ;
	}
	else{
		return 1 + update_height_bst(node) ;
	}

}


int adjusted_height_avl(struct Node_avl *node){

	if(node==NULL){
		return 0 ;
	}
	else{
		return 1 + give_height_avl(node) ;
	}

}


int height_diff_avl(struct Node_avl *node){

	if(node==NULL){
		return 0 ;
	}
	else{
		return give_height_avl(node->left) - give_height_avl(node->right) ;
	}

}


struct Node_avl* left_rotate_root(struct Node_avl *root){

	struct Node_avl *right_child = root->right ;
	struct Node_avl *right_left_child = right_child->left ;

	root->right = right_left_child ;
	right_child->left = root ;

	root->height = update_height_avl(root) ;
	right_child->height = update_height_avl(right_child) ;

	return right_child ;

}


struct Node_avl* right_rotate_root(struct Node_avl *root){

	struct Node_avl *left_child = root->left ;
	struct Node_avl *left_right_child = left_child->right ;

	root->left = left_right_child ;
	left_child->right = root ;

	root->height = update_height_avl(root) ;
	left_child->height = update_height_avl(left_child) ;

	return left_child ;

}


struct Node_avl* balance_avl_tree(struct Node_avl *root){

	if(root==NULL){
		return root ;
	}

	root->height = update_height_avl(root) ;

	if(height_diff_avl(root) > 1){
		if(height_diff_avl(root->left) >= 0){
			root = right_rotate_root(root) ;
		}
		else{
			root->left = left_rotate_root(root->left) ;
			root = right_rotate_root(root) ;
		}
	}
	else if(height_diff_avl(root) < -1){
		if(height_diff_avl(root->right) <= 0){
			root = left_rotate_root(root) ;
		}
		else{
			root->right = right_rotate_root(root->right) ;
			root = left_rotate_root(root) ;
		}
	}

	return root ;

}


struct Node_bst* bst_insert(struct Node_bst *root, int value){

	if(root==NULL){
		struct Node_bst *new_node = (struct Node_bst *)malloc(sizeof(struct Node_bst)) ;
		new_node->data = value ;
		new_node->left = NULL ;
		new_node->right = NULL ;
		root = new_node ;
	}
	else if(root->data > value){
		root->left = bst_insert(root->left,value) ;
	}
	else if(root->data < value){
		root->right = bst_insert(root->right,value) ;
	}

	return root ;

}


struct Node_bst* bst_delete(struct Node_bst *root, int value){

	if(root==NULL){
		return root ;
	}
	else if(root->data > value){
		root->left = bst_delete(root->left,value) ;
	}
	else if(root->data < value){
		root->right = bst_delete(root->right,value) ;
	}
	else{
		if(root->left==NULL && root->right==NULL){
			free(root) ;
			root = NULL ;
		}
		else if(root->left==NULL){
			struct Node_bst *replacement = root->right ;
			root->right = NULL ;
			free(root) ;
			root = replacement ;
		}
		else if(root->right==NULL){
			struct Node_bst *replacement = root->left ;
			root->left = NULL ;
			free(root) ;
			root = replacement ;
		}
		else{
			struct Node_bst *replacement = root->left ;
			while(replacement->right != NULL){
				replacement = replacement->right ;
			}
			root->data = replacement->data ;
			root->left = bst_delete(root->left,root->data) ;
		}
	}

	return root ;

}


struct Node_avl* avl_insert(struct Node_avl *root, int value){

	if(root==NULL){
		struct Node_avl *new_node = (struct Node_avl *)malloc(sizeof(struct Node_avl)) ;
		new_node->data = value ;
		new_node->left = NULL ;
		new_node->right = NULL ;
		new_node->height = 0 ;
		root = new_node ;
	}
	else if(root->data > value){
		root->left = avl_insert(root->left,value) ;
	}
	else if(root->data < value){
		root->right = avl_insert(root->right,value) ;
	}

	root = balance_avl_tree(root) ;

	return root ;

}


struct Node_avl* avl_delete(struct Node_avl *root, int value){

	if(root==NULL){
		return root ;
	}
	else if(root->data > value){
		root->left = avl_delete(root->left,value) ;
	}
	else if(root->data < value){
		root->right = avl_delete(root->right,value) ;
	}
	else{
		if(root->left==NULL && root->right==NULL){
			free(root) ;
			root = NULL ;
		}
		else if(root->left==NULL){
			struct Node_avl *replacement = root->right ;
			root->right = NULL ;
			free(root) ;
			root = replacement ;
		}
		else if(root->right==NULL){
			struct Node_avl *replacement = root->left ;
			root->left = NULL ;
			free(root) ;
			root = replacement ;
		}
		else{
			struct Node_avl *replacement = root->left ;
			while(replacement->right != NULL){
				replacement = replacement->right ;
			}
			root->data = replacement->data ;
			root->left = avl_delete(root->left,root->data) ;
		}
	}

	root = balance_avl_tree(root) ;

	return root ;

}


int find_bst(struct Node_bst *root, int value){

	if(value<0 || root==NULL){
		return 0 ;
	}
	if(root->data < value){
		return find_bst(root->right,value) ;
	}
	else if(root->data > value){
		return find_bst(root->left,value) ;
	}
	else{
		return 1 ;
	}

}


int find_avl(struct Node_avl *root, int value){

	if(value<0 || root==NULL){
		return 0 ;
	}
	if(root->data < value){
		return find_avl(root->right,value) ;
	}
	else if(root->data > value){
		return find_avl(root->left,value) ;
	}
	else{
		return 1 ;
	}

}


int num_leaves_bst(struct Node_bst *root){

	if(root==NULL){
		return 0 ;
	}
	else if(root->left==NULL && root->right==NULL){
		return 1 ;
	}
	else{
	    return num_leaves_bst(root->left) + num_leaves_bst(root->right) ;
	}

}


int num_leaves_avl(struct Node_avl *root){

	if(root==NULL){
		return 0 ;
	}
	else if(root->left==NULL && root->right==NULL){
		return 1 ;
	}
	else{
	    return num_leaves_avl(root->left) + num_leaves_avl(root->right) ;
	}

}


int num_nodes_bst(struct Node_bst *root){

	if(root==NULL){
		return 0 ;
	}
	else{
		return 1 + num_nodes_bst(root->left) + num_nodes_bst(root->right) ;
	}

}


int num_nodes_avl(struct Node_avl *root){

	if(root==NULL){
		return 0 ;
	}
	else{
		return 1 + num_nodes_avl(root->left) + num_nodes_avl(root->right) ;
	}

}


void preorder_bst(struct Node_bst *root, int *i){

	if(root==NULL){
		return ;
	}
	struct Node_type2_bst *top = NULL ;
	top = push_stack_bst(&top,root) ;
	while(top!=NULL){
		struct Node_bst *temp = pop_stack_bst(&top) ;
		if((*i)==0){
			printf("%d",temp->data) ;
			(*i)++ ;
		}
		else{
			printf(" %d",temp->data) ;
		}
		top = push_stack_bst(&top,temp->right) ;
		top = push_stack_bst(&top,temp->left) ;
	}	

}


void preorder_avl(struct Node_avl *root, int *i){

	if(root==NULL){
		return ;
	}
	struct Node_type2_avl *top = NULL ;
	top = push_stack_avl(&top,root) ;
	while(top!=NULL){
		struct Node_avl *temp = pop_stack_avl(&top) ;
		if((*i)==0){
			printf("%d",temp->data) ;
			(*i)++ ;
		}
		else{
			printf(" %d",temp->data) ;
		}
		top = push_stack_avl(&top,temp->right) ;
		top = push_stack_avl(&top,temp->left) ;
	}	

}


void inorder_bst(struct Node_bst *root, int *i){

	if(root==NULL){
		return ;
	}
	else{
		inorder_bst(root->left,i) ;
		if((*i)==0){
			printf("%d",root->data) ;
			(*i)++ ;
		}
		else{
			printf(" %d",root->data) ;
		}
		inorder_bst(root->right,i) ;
	}

}


void inorder_avl(struct Node_avl *root, int *i){

	if(root==NULL){
		return ;
	}
	else{
		inorder_avl(root->left,i) ;
		if((*i)==0){
			printf("%d",root->data) ;
			(*i)++ ;
		}
		else{
			printf(" %d",root->data) ;
		}
		inorder_avl(root->right,i) ;
	}

}


void postorder_bst(struct Node_bst *root, int *i){

	if(root==NULL){
		return ;
	}
	else{
		postorder_bst(root->left,i) ;
		postorder_bst(root->right,i) ;
		if((*i)==0){
			printf("%d",root->data) ;
			(*i)++ ;
		}
		else{
			printf(" %d",root->data) ;
		}
	}

}


void postorder_avl(struct Node_avl *root, int *i){

	if(root==NULL){
		return ;
	}
	else{
		postorder_avl(root->left,i) ;
		postorder_avl(root->right,i) ;
		if((*i)==0){
			printf("%d",root->data) ;
			(*i)++ ;
		}
		else{
			printf(" %d",root->data) ;
		}
	}

}


void levelorder_bst(struct Node_bst *root, int *i){

	if(root==NULL){
		return ;
	}
	struct Node_type2_bst *front = NULL ;
	struct Node_type2_bst *back = NULL ;
	back = enqueue_bst(&front,&back,root) ;
	while(front!=NULL && back!=NULL){
		struct Node_bst *temp = dequeue_bst(&front,&back) ;
		if((*i)==0){
			printf("%d",temp->data) ;
			(*i)++ ;
		}
		else{
			printf(" %d",temp->data) ;
		}
		back = enqueue_bst(&front,&back,temp->left) ;
		back = enqueue_bst(&front,&back,temp->right) ;
	} 

}


void levelorder_avl(struct Node_avl *root, int *i){

	if(root==NULL){
		return ;
	}
	struct Node_type2_avl *front = NULL ;
	struct Node_type2_avl *back = NULL ;
	back = enqueue_avl(&front,&back,root) ;
	while(front!=NULL && back!=NULL){
		struct Node_avl *temp = dequeue_avl(&front,&back) ;
		if((*i)==0){
			printf("%d",temp->data) ;
			(*i)++ ;
		}
		else{
			printf(" %d",temp->data) ;
		}
		back = enqueue_avl(&front,&back,temp->left) ;
		back = enqueue_avl(&front,&back,temp->right) ;
	} 

}


int max_width_bst(struct Node_bst *root){

	if(root==NULL){
		return 0 ;
	}
	struct Node_type2_bst *front = NULL ;
	struct Node_type2_bst *back = NULL ;
	back = enqueue_bst(&front,&back,root) ;
	int present_level = 1, next_level = 0, max_count = 1, index_in_level = 0 ;
	while(front!=NULL && back!=NULL){
		struct Node_bst *temp = dequeue_bst(&front,&back) ;
		if(temp->left != NULL){
			back = enqueue_bst(&front,&back,temp->left) ;
			next_level++ ;
		}
		if(temp->right != NULL){
			back = enqueue_bst(&front,&back,temp->right) ;
			next_level++ ;
		}
		index_in_level++ ;
		if(index_in_level==present_level){
			index_in_level = 0 ;
			present_level = next_level ;
			next_level = 0 ;
			max_count = max(max_count,present_level) ;
		}
	} 
	return max_count ;

}


int max_width_avl(struct Node_avl *root){

	if(root==NULL){
		return 0 ;
	}
	struct Node_type2_avl *front = NULL ;
	struct Node_type2_avl *back = NULL ;
	back = enqueue_avl(&front,&back,root) ;
	int present_level = 1, next_level = 0, max_count = 1, index_in_level = 0 ;
	while(front!=NULL && back!=NULL){
		struct Node_avl *temp = dequeue_avl(&front,&back) ;
		if(temp->left != NULL){
			back = enqueue_avl(&front,&back,temp->left) ;
			next_level++ ;
		}
		if(temp->right != NULL){
			back = enqueue_avl(&front,&back,temp->right) ;
			next_level++ ;
		}
		index_in_level++ ;
		if(index_in_level==present_level){
			index_in_level = 0 ;
			present_level = next_level ;
			next_level = 0 ;
			max_count = max(max_count,present_level) ;
		}
	} 
	return max_count ;

}


int common_ancestor_bst(struct Node_bst *root, int value1, int value2){

	struct Node_bst *current = root ;
	if(find_bst(root,value1)==1 && (value1==value2)){
	    return value1 ;
	}
	if(find_bst(root,value1)==0 || find_bst(root,value2)==0){
		return -1 ;
	}
	while(current!=NULL && in_between(current->data,value1,value2)==0){
		if(current->data < value1){
			current = current->right ;
		}
		else{
			current = current->left ;
		}
	}
	return current->data ;

}


int common_ancestor_avl(struct Node_avl *root, int value1, int value2){

	struct Node_avl *current = root ;
	if(find_avl(root,value1)==1 && (value1==value2)){
	    return value1 ;
	}
	if(find_avl(root,value1)==0 || find_avl(root,value2)==0){
		return -1 ;
	}
	while(current!=NULL && in_between(current->data,value1,value2)==0){
		if(current->data < value1){
			current = current->right ;
		}
		else{
			current = current->left ;
		}
	}
	return current->data ;

}


void route_bst(struct Node_bst *root, int value1, int value2){

	if(find_bst(root,value1)==0){
		printf("Source does not exist") ;
		return ;
	}
	else if(find_bst(root,value2)==0){
		printf("Destination does not exist") ;
		return ;
	}
	else{
		struct Node_bst *current = root ;
		while(current->data!=value1){
			if(current->data < value1){
				current = current->right ;
			}
			else{
				current = current->left ;
			}
		}
		if(find_bst(current,value2)==0){
			printf("Unreachable") ;
			return ;
		}
		else{
			int i=0 ;
			while(current->data != value2){
				if(i==0){
					printf("%d",current->data) ;
					i++ ;
				}
				else{
					printf(" %d",current->data) ;
				}
				if(current->data > value2){
					printf(" %c",'L') ;
					current = current->left ;
				}
				else{
					printf(" %c",'R') ;
					current = current->right ;
				}
			}
			if(i==0){
				printf("%d",value2) ;
			}
			else{
				printf(" %d",value2) ;
			}
			return ;
		}
	}

}


void route_avl(struct Node_avl *root, int value1, int value2){

	if(find_avl(root,value1)==0){
		printf("Source does not exist") ;
		return ;
	}
	else if(find_avl(root,value2)==0){
		printf("Destination does not exist") ;
		return ;
	}
	else{
		struct Node_avl *current = root ;
		while(current->data!=value1){
			if(current->data < value1){
				current = current->right ;
			}
			else{
				current = current->left ;
			}
		}
		if(find_avl(current,value2)==0){
			printf("Unreachable") ;
			return ;
		}
		else{
			int i=0 ;
			while(current->data != value2){
				if(i==0){
					printf("%d",current->data) ;
					i++ ;
				}
				else{
					printf(" %d",current->data) ;
				}
				if(current->data > value2){
					printf(" %c",'L') ;
					current = current->left ;
				}
				else{
					printf(" %c",'R') ;
					current = current->right ;
				}
			}
			if(i==0){
				printf("%d",value2) ;
			}
			else{
				printf(" %d",value2) ;
			}
			return ;
		}
	}

}


int diameter_bst(struct Node_bst *root){

	if(root==NULL){
		return 0 ;
	}
	else{
		return max(1+adjusted_height_bst(root->left)+adjusted_height_bst(root->right),max(diameter_bst(root->left),diameter_bst(root->right))) ;
	}

}


int diameter_avl(struct Node_avl *root){

	if(root==NULL){
		return 0 ;
	}
	else{
		return max(1+adjusted_height_avl(root->left)+adjusted_height_avl(root->right),max(diameter_avl(root->left),diameter_avl(root->right))) ;
	}

}


void store_leaves_bst(struct Node_bst *root, int arr[], int *index){

	if(root==NULL){
		return ;
	}
	else if(root->left==NULL && root->right==NULL){
		(*index)++ ;
		arr[*index] = root->data ;
		return ;
	}
	else{
		store_leaves_bst(root->right,arr,index) ;
		store_leaves_bst(root->left,arr,index) ;
		return ;
	}

}


void store_leaves_avl(struct Node_avl *root, int arr[], int *index){

	if(root==NULL){
		return ;
	}
	else if(root->left==NULL && root->right==NULL){
		(*index)++ ;
		arr[*index] = root->data ;
		return ;
	}
	else{
		store_leaves_avl(root->right,arr,index) ;
		store_leaves_avl(root->left,arr,index) ;
		return ;
	}

}


void perimeter_function_bst(struct Node_bst *root){

	int n = num_nodes_bst(root) ;
	if(n==0){
		return ;
	}
	int arr[n] ;
	int index = -1 ;
	struct Node_bst *current = root ;
	while(current!=NULL){
		if((current->left)==NULL && (current->right)==NULL){
			break ;
		}
		index++ ;
		arr[index] = current->data ;
		if(current->right != NULL){
			current = current->right ;
		}
		else{
			current = current->left ;
		}
	}
	store_leaves_bst(root,arr,&index) ;
	current = root->left ;
	int num = 0 ;
	while(current!=NULL){
		if((current->left)==NULL && (current->right)==NULL){
			break ;
		}
		num++ ;
		if(current->left != NULL){
			current = current->left ;
		}
		else{
			current = current->right ;
		}
	}
	current = root->left ;
	index = index + num ;
	int total_perimeter_nodes = index + 1 ;
	while(current!=NULL){
		if((current->left)==NULL && (current->right)==NULL){
			break ;
		}
		arr[index] = current->data ;
		index-- ;
		if(current->left != NULL){
			current = current->left ;
		}
		else{
			current = current->right ;
		}
	}
	index = 0 ;
	long int sum = 0 ;
	for(int i=0 ; i<total_perimeter_nodes ; i++){
		sum = sum + arr[i] ;
	}
	printf("%ld",sum) ;
	for(int i=0 ; i<total_perimeter_nodes ; i++){
		printf(" %d",arr[i]) ;
	}

}


void perimeter_function_avl(struct Node_avl *root){

	int n = num_nodes_avl(root) ;
	if(n==0){
		return ;
	}
	int arr[n] ;
	int index = -1 ;
	struct Node_avl *current = root ;
	while(current!=NULL){
		if((current->left)==NULL && (current->right)==NULL){
			break ;
		}
		index++ ;
		arr[index] = current->data ;
		if(current->right != NULL){
			current = current->right ;
		}
		else{
			current = current->left ;
		}
	}
	store_leaves_avl(root,arr,&index) ;
	current = root->left ;
	int num = 0 ;
	while(current!=NULL){
		if((current->left)==NULL && (current->right)==NULL){
			break ;
		}
		num++ ;
		if(current->left != NULL){
			current = current->left ;
		}
		else{
			current = current->right ;
		}
	}
	current = root->left ;
	index = index + num ;
	int total_perimeter_nodes = index + 1 ;
	while(current!=NULL){
		if((current->left)==NULL && (current->right)==NULL){
			break ;
		}
		arr[index] = current->data ;
		index-- ;
		if(current->left != NULL){
			current = current->left ;
		}
		else{
			current = current->right ;
		}
	}
	index = 0 ;
	long int sum = 0 ;
	for(int i=0 ; i<total_perimeter_nodes ; i++){
		sum = sum + arr[i] ;
	}
	printf("%ld",sum) ;
	for(int i=0 ; i<total_perimeter_nodes ; i++){
		printf(" %d",arr[i]) ;
	}

}


void tree_ops(struct Node_bst **root1, struct Node_avl **root2, char query, int tree_type){

	switch(query){

		case 'T' :
		{

			char temp ;
			scanf("%c",&temp) ;
			if(temp=='\n'|| temp==EOF){
				break ;
			}
			int num ;
			do{
			  	scanf("%d%c", &num, &temp); 
			  	if(num>0){
			  		*root1 = bst_insert(*root1,num) ;
			  	}
			  	else{
			  		*root1 = bst_delete(*root1,-1*num) ;
			  	}
		  	} 	while(temp!='\n' && temp!=EOF);

			break ;

		}

		case 'H' :

		{
			char temp ;
			scanf("%c",&temp) ;
			if(temp=='\n' || temp==EOF){
				break ;
			}
			int num ;
			do{
			  	scanf("%d%c", &num, &temp); 
			  	if(num>0){
			  		*root2 = avl_insert(*root2,num) ;
			  	}
			  	else{
			  		*root2 = avl_delete(*root2,-1*num) ;
			  	}
		  	} 	while(temp!='\n' && temp!=EOF); 

			break ;
		}

		case 'A' :

		{
			char temp ;
			scanf("%c",&temp) ;
			if(temp=='\n' || temp==EOF){
				break ;
			}
			int num ;
			do{
			  	scanf("%d%c", &num, &temp); 
			  	if(num>0){
			  		if(tree_type==0){
			  			*root1 = bst_insert(*root1,num) ;
			  		}
			  		else{
			  			*root2 = avl_insert(*root2,num) ;
			  		}
			  	}
			  	else{
			  		continue ;
			  	}
		  	} 	while(temp!= '\n' && temp!=EOF); 

			break ;
		}

		case 'U' :
		{
			char temp ;
			scanf("%c",&temp) ;
			if(temp=='\n' || temp==EOF){
				break ;
			}
			int num ;
			do{
			  	scanf("%d%c", &num, &temp); 
			  	if(num>0){
			  		if(tree_type==0){
			  			*root1 = bst_delete(*root1,num) ;
			  		}
			  		else{
			  			*root2 = avl_delete(*root2,num) ;
			  		}
			  	}
			  	else{
			  		continue ;
			  	}
		  	} 	while(temp!= '\n' && temp!=EOF); 
		  	
			break ;
		}

		case 'F' :

		{
			int num ;
			char temp1, temp2 ;
			scanf("%c%d%c",&temp1,&num,&temp2) ;
			if(tree_type==0){
				if(find_bst(*root1,num)==1){
					printf("Yes") ;
				}
				else{
					printf("No") ;
				}
			}
			else{
				if(find_avl(*root2,num)==1){
					printf("Yes") ;
				}
				else{
					printf("No") ;
				}
			}
			break ;
		}

		case 'Q' :

		{
			char temp ;
			scanf("%c",&temp) ;
			if(tree_type==0){
				printf("%d",num_leaves_bst(*root1)) ;
			}
			else{
				printf("%d",num_leaves_avl(*root2)) ;
			}
			break ;
		}

		case 'N' :

		{
			char temp ;
			scanf("%c",&temp) ;
			if(tree_type==0){
				printf("%d",num_nodes_bst(*root1)) ;
			}
			else{
				printf("%d",num_nodes_avl(*root2)) ;
			}
			break ;
		}

		case 'P' :

		{
			char temp ;
			int i = 0 ;
			scanf("%c",&temp) ;
			if(tree_type==0){
				preorder_bst(*root1,&i) ;
			}
			else{
				preorder_avl(*root2,&i) ;
			}
			break ;
		}

		case 'I' :

		{
			char temp ;
			int i = 0 ;
			scanf("%c",&temp) ;
			if(tree_type==0){
				inorder_bst(*root1,&i) ;
			}
			else{
				inorder_avl(*root2,&i) ;
			}
			break ;
		}

		case 'S' :

		{
			char temp ;
			int i = 0 ;
			scanf("%c",&temp) ;
			if(tree_type==0){
				postorder_bst(*root1,&i) ;
			}
			else{
				postorder_avl(*root2,&i) ;
			}
			break ;
		}

		case 'L' :

		{
			char temp ;
			int i = 0 ;
			scanf("%c",&temp) ;
			if(tree_type==0){
				levelorder_bst(*root1,&i) ;
			}
			else{
				levelorder_avl(*root2,&i) ;
			}
			break ;
		}

		case 'D' :

		{
			char temp ;
			scanf("%c",&temp) ;
			if(tree_type==0){
				printf("%d",update_height_bst(*root1)) ;
			}
			else{
				printf("%d",give_height_avl(*root2)) ;
			}
			break ;
		}

		case 'W' :

		{
			char temp ;
			scanf("%c",&temp) ;
			if(tree_type==0){
				printf("%d",max_width_bst(*root1)) ;
			}
			else{
				printf("%d",max_width_avl(*root2)) ;
			}
			break ;
		}

		case 'C' :

		{
			int num1, num2 ;
			char temp1, temp2, temp3 ;
			scanf("%c%d%c%d%c",&temp1,&num1,&temp2,&num2,&temp3) ;
			if(tree_type==0){
				printf("%d",common_ancestor_bst(*root1,num1,num2)) ;
			}
			else{
				printf("%d",common_ancestor_avl(*root2,num1,num2)) ;
			}
			break ;
		}

		case 'R' :

		{
			int num1, num2 ;
			char temp1, temp2, temp3 ;
			scanf("%c%d%c%d%c",&temp1,&num1,&temp2,&num2,&temp3) ;
			if(tree_type==0){
				route_bst(*root1,num1,num2) ;
			}
			else{
				route_avl(*root2,num1,num2) ;
			}
			break ;
		}

		case 'X' :

		{
			char temp ;
			scanf("%c",&temp) ;
			if(tree_type==0){
				printf("%d",diameter_bst(*root1)) ;
			}
			else{
				printf("%d",diameter_avl(*root2)) ;
			}
			break ;
		}

		case 'Y' :

		{
			char temp ;
			scanf("%c",&temp) ;
			if(tree_type==0){
				perimeter_function_bst(*root1) ;
			}
			else{
				perimeter_function_avl(*root2) ;
			}
			break ;
		}

	}

}


int main(){

	int t ;
	char temp ;
	scanf("%d%c",&t,&temp) ;
	char query ;
	int tree_type = 0 ;
	int print_sequence = 0 ;
	struct Node_bst *tree_root_bst = NULL ;
	struct Node_avl *tree_root_avl = NULL ;

	while(t>0){

		scanf("%c",&query) ;

		clear_trees(&tree_root_bst,&tree_root_avl,query,&tree_type) ;

		tree_ops(&tree_root_bst,&tree_root_avl,query,tree_type) ;

		print_sequence = should_print(query) ;

		if(t>1 && print_sequence==1){
			printf("\n") ;
		}

		if(t==1){
			if(tree_type == 0){
				tree_root_bst = delete_tree_bst(tree_root_bst) ;
			}
			else{
				tree_root_avl = delete_tree_avl(tree_root_avl) ;
			}
		}

		t-- ;

	}

	return 0 ;

}

/*


Testcases used to test my code :




Testcase 1 :

58
T
A 1 6 2 3 5 4
P
I
S
L
D
R 1 4
R 4 3
R 3 4
R 5 2
R 5 7
R 7 2
R 8 8
R 5 5
C 1 5
C 3 2
C 4 6
C 7 5
U 6 2
P
I
S
L
T
A 1 2
I
H 1 2
I
H
A 1 6 2 3 5 4
P
I
S
L
D
R 1 4
R 4 3
R 3 4
R 5 2
R 5 7
R 7 2
R 8 8
R 5 5
C 1 5
C 3 2
C 4 6
C 7 5
U 6 2
P
I
S
L
T
A 1 2
I
H 1 2
I

Output :

1 6 2 3 5 4
1 2 3 4 5 6
4 5 3 2 6 1
1 6 2 3 5 4
5
1 R 6 L 2 R 3 R 5 L 4
Unreachable
3 R 5 L 4
Unreachable
Destination does not exist
Source does not exist
Source does not exist
5
1
2
6
-1
1 3 5 4
1 3 4 5
4 5 3 1
1 3 5 4
1 2
1 2
3 2 1 5 4 6
1 2 3 4 5 6
1 2 4 6 5 3
3 2 5 1 4 6
2
Unreachable
Unreachable
3 R 5 L 4
Unreachable
Destination does not exist
Source does not exist
Source does not exist
5
3
3
5
-1
3 1 5 4
1 3 4 5
1 4 5 3
3 1 5 4
1 2
1 2




Testcase 2 :

11
H
A 1 6 2 3 5 4
P
I
S
L
U 6 2
P
I
S
L

Output :

3 2 1 5 4 6
1 2 3 4 5 6
1 2 4 6 5 3
3 2 5 1 4 6
3 1 5 4
1 3 4 5
1 4 5 3
3 1 5 4




Testcase 3 :

26
H 1 5 2 8 5 6 15
A 6 7
U 8 1 4
I
D
X
A 4 7 6 9 13
P
I
S
L
N
Q
X
Y
W
F 6
F 8
C 9 13
R 4 7
H 1 5 3
N
P
I
S
L

Output :

2 5 6 7 15
2
5
6 4 2 5 9 7 15 13
2 4 5 6 7 9 13 15
2 5 4 7 13 15 9 6
6 4 9 2 5 7 15 13
8
4
6
61 6 9 15 13 7 5 2 4
4
Yes
No
9
Unreachable
3
3 1 5
1 3 5
1 5 3
3 1 5




Testcase 4 (From Assignment Sheet) :

7
T 10 12 9 6 11 15
U 6
I
L
Y
X
D

Output :

9 10 11 12 15
10 9 12 11 15
57 10 12 15 11 9
4
2




Testcase 5 (From Assignment Sheet):

13
H 10 1 8 7 -10
A 4 5
U 8
P
I
S
L
X
Y
D
W
C 1 5
R 1 7

Output :

4 1 7 5
1 4 5 7
1 5 7 4
4 1 7 5
4
17 4 7 5 1
2
2
4
Unreachable



*/
