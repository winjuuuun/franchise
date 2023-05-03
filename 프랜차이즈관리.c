#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "FRANCHISECOMMON.h"
#include "FRANCHISEFILE.h"
SUM* sum_create(){
	SUM *N;
	N = (SUM*)malloc(sizeof(SUM));
	N->sum_prod_count=0;
	N->link = NULL;
	return N;
}
void add_sum(SUM *S,int sum_prod_count){
	SUM *P;
	SUM *N;
	P = S;
	N = sum_create();
	N->sum_prod_count = sum_prod_count; 
	while(P->link!=NULL){
		P = P->link;
	}
	P->link = N;
}
STACK* s_create(){
	STACK *N;
	N = (STACK*)malloc(sizeof(STACK));
	N->p = NULL;			//메인에서 스택 동작할당할떄 해주므로(임시로 그래프를 보관할거라서) 
	N->link = NULL;
	return N;
}
void push(PART *P){
	STACK *N;
	N = s_create();
	N->p = P;
	N->link = top->link;
	top->link = N;
}
PART* pop(){
	PART *ttemp;
	STACK *temp;
	temp = top->link;
	ttemp = temp->p;
	top->link = temp->link;
	free(temp);
	return ttemp;
}
int isEmpty(){
	return top->link==NULL;
}
PRODUCT* create_product(){
	PRODUCT *N;
	N = (PRODUCT*)malloc(sizeof(PRODUCT));
	N->left = NULL;
	N->right = NULL;
	strcpy(N->d.prod_name," ");
	N->d.prod_count = 0;
	N->d.money = 0;
	return N;
}
PART* create_part(int index){
	int i;
	PART *N;
	N = (PART*)malloc(sizeof(PART));
	strcpy(N->name," ");
	for(i=0;i<5;i++){
		N->link[i] = (PART*)malloc(sizeof(PART));
		N->link[i] = NULL;
	}
	N->index = index;
	N->prod = create_product();
	return N;
}
//나머지 넣어줄떄는 동적할당 필요없는거 아닌지? 
void pr_prod_list(PRODUCT *P){
	int i = 0;
	int j = 0;
	int k = 0;
	int level = 0;
	int count = 1; 
	int end=0;
	PRODUCT *N[128];//출력 
	PRODUCT *M[128];//자식 저장 
	
	N[0] = P;
	while(1){
		k=0;
		for(i=0;i<count;i++){
			printf("제품명:%s ",N[i]->d.prod_name);
			printf("수량:%d ",N[i]->d.prod_count);
			printf("단가:%d ",N[i]->d.money);
			printf("\n"); 
			if(N[i]->left!=NULL){
				M[k++] = N[i]->left;
			}
		    if(N[i]->right!=NULL){
				M[k++] = N[i]->right;
			}
		}
		printf("\n");
		count=k; 	//덮어씌운 범위 
		if(k==0)break;
		for(j=0;j<k;j++){
		   N[j] = M[j];//덮어씌우기 
		   M[j]=NULL;
	    }
	}	
}
void pr_total_list(PART **gar){
	PART *P;
	P = gar[0];
	int i;
	int cc=0;
	int count=0;
	int chkar[5]={0};
	while(1){
		if(cc!=0&&isEmpty()==1)break;
		count=0;
		for(i=0;i<5;i++){
			if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
				count++;
			}
		}
		if(cc==0&&count!=0){
			chkar[0]=1;
		}
		if(cc==4||count>0){
			printf("지점명:%s\n",P->name);
			pr_prod_list(P->prod);
		}
		if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
					chkar[P->link[i]->index]=1;
					push(P);
					P = P->link[i];
					break;
				}
			}
		}
		else if(count==1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
					chkar[P->link[i]->index]=1;
					P = P->link[i];
				}
			}
		}
		else{
			P = pop();
		}
		cc++;
	}
	printf("\n");
}
void nmg_insert_prod(PRODUCT *P,char *prod_name){
	int i = 0;
	int j = 0;
	int k = 0;
	int level = 0;
	int count = 1; 
	int end=0;
	PRODUCT *N[128];//출력 
	PRODUCT *M[128];//자식 저장 
	N[0] = P;
	while(1){
		k=0;
		for(i=0;i<count;i++){
			if(strcmp(N[i]->d.prod_name,prod_name)==0){
				N[i]->d.prod_count+=1;
				end=1;
				break;
			}
			if(N[i]->left!=NULL){
				M[k++] = N[i]->left;
			}
		    if(N[i]->right!=NULL){
				M[k++] = N[i]->right;
			}
		}
		printf("\n");
		count=k; 	//덮어씌운 범위 
		if(end==1||k==0)break;
		for(j=0;j<k;j++){
		   N[j] = M[j];//덮어씌우기 
		   M[j]=NULL;
	    }
	}	
}
int chk_part_name(PART **gar,char *part_name){
	int end=0;
	PART *P;
	P = gar[0];
	int i;
	int cc=0;
	int count=0;
	int chkar[5]={0};
	while(1){
		if(cc!=0&&isEmpty()==1)break;
		count=0;
		for(i=0;i<5;i++){
			if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
				count++;
			}
		}
		if(cc==0&&count!=0){
			chkar[0]=1;
		}
		if(cc==4||count>0){
			if(strcmp(P->name,part_name)==0){
				end = 1;
				break;
			}
		}
		if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
					chkar[P->link[i]->index]=1;
					push(P);
					P = P->link[i];
					break;
				}
			}
		}
		else if(count==1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
					chkar[P->link[i]->index]=1;
					P = P->link[i];
				}
			}
		}
		else{
			P = pop();
		}
		cc++;
	}
	if(end==1)return 1;
	else return 0;
}
//제품이 들어가지 않는다. 
int chk_prod_name(PRODUCT *P,char *prod_name){
	int i = 0;
	int j = 0;
	int k = 0;
	int level = 0;
	int count = 1; 
	int end=0;
	PRODUCT *N[128];//출력 
	PRODUCT *M[128];//자식 저장 
	N[0] = P;
	while(1){
		k=0;
		for(i=0;i<count;i++){
			if(strcmp(N[i]->d.prod_name,prod_name)==0){
				end=1;
				break;
			}
			if(N[i]->left!=NULL){
				M[k++] = N[i]->left;
			}
		    if(N[i]->right!=NULL){
				M[k++] = N[i]->right;
			}
		}
		printf("\n");
		count=k; 	//덮어씌운 범위 
		if(end==1||k==0)break;
		for(j=0;j<k;j++){
		   N[j] = M[j];//덮어씌우기 
		   M[j]=NULL;
	    }
	}
	if(end==1)return 1;
	else return 0;
}
void insert_prod(PRODUCT *P,char *prod_name,int prod_count,int money){
	PRODUCT *N;
	N = create_product();
	strcpy(N->d.prod_name,prod_name);
	N->d.prod_count = prod_count/5;
	N->d.money = money;
	if(strcmp(P->d.prod_name," ")==0){
		strcpy(P->d.prod_name,prod_name);
		P->d.prod_count = prod_count/5;
		P->d.money = money;
		return;
	}
	else{
		if(strcmp(P->d.prod_name,prod_name)<0){
			if(P->right==NULL){
				P->right = N;
				return;
			}
			insert_prod(P->right,prod_name,prod_count,money);
		}
		else{
			if(P->left==NULL){
				P->left = N;
				return;
			}
			insert_prod(P->left,prod_name,prod_count,money);
		}
	}
}
void sign_up_prod(PART **gar){
	int cc=0;
	int count=0;
	int chkar[5]={0};
	int chkar2[5]={0};
	int *rar;
	int rc;
	int rn;
	int i;
	char nprod_name[10];
	int nprod_count;
	int nmoney;
	PART *P;
	P = gar[0];
	printf("제품명:");
	scanf("%s",nprod_name);
	if(chk_prod_name(P->prod,nprod_name)==1){
		printf("동일한 제품을 등록할수 없습니다!!!\n");
		return;
	}
	printf("수량:");
	scanf("%d",&nprod_count);
	rc = nprod_count % 5;
	printf("단가:");
	scanf("%d",&nmoney);
	//그래프에 rc만큼 다 넣어주고 나서는 추가하는건 그래프 순서대로 넣어줘도 된다.
	while(1){
		if(cc!=0&&isEmpty()==1)break;
		count=0;
		for(i=0;i<5;i++){
			if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
				count++;
			}
		}
		if(cc==0&&count!=0){
			chkar[0]=1;
		}
		if(count>0||cc==4)insert_prod(P->prod,nprod_name,nprod_count,nmoney);
		if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
					chkar[P->link[i]->index]=1;
					push(P);
					P = P->link[i];
					break;
				}
			}
		}
		else if(count==1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
					chkar[P->link[i]->index]=1;
					P = P->link[i];
				}
			}
		}
		else{
			P = pop();
		}
		cc++;
	}
	P = gar[0];
	cc=0;
	count=0;
	while(1){
		if(cc==rc)break;
		count=0;
		for(i=0;i<5;i++){
			if(P->link[i]!=NULL&&chkar2[P->link[i]->index]==0){
				count++;
			}
		}
		if(cc==0&&count!=0){
			chkar2[0]=1;
		}
		if(count>0)nmg_insert_prod(P->prod,nprod_name);
		if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar2[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
					chkar2[P->link[i]->index]=1;
					push(P);
					P = P->link[i];
					break;
				}
			}
		}
		else if(count==1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar2[P->link[i]->index]==0){
					chkar2[P->link[i]->index]=1;
					P = P->link[i];
				}
			}
		}
		else{
			P = pop();
		}
		cc++;
	}
	pr_total_list(gar);	
}
void sel_pr_total_list(PART **gar,char *part_name){
	PART *P;
	P = gar[0];
	int i;
	int cc=0;
	int count=0;
	int chkar[5]={0};
	while(1){
		if(cc!=0&&isEmpty()==1)break;
		count=0;
		for(i=0;i<5;i++){
			if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
				count++;
			}
		}
		if(cc==0&&count!=0){
			chkar[0]=1;
		}
		if(cc==4||count>0){
			if(strcmp(P->name,part_name)==0){
				printf("지점명:%s\n",P->name);
				pr_prod_list(P->prod);
				break;
			}
		}
		if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
					chkar[P->link[i]->index]=1;
					push(P);
					P = P->link[i];
					break;
				}
			}
		}
		else if(count==1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
					chkar[P->link[i]->index]=1;
					P = P->link[i];
				}
			}
		}
		else{
			P = pop();
		}
		cc++;
	}
	printf("\n");
}
////
void sell_sel_prod(PRODUCT *P,char *prod_name,int prod_count){
	int i = 0;
	int j = 0;
	int k = 0;
	int level = 0;
	int count = 1; 
	int end=0;
	PRODUCT *N[128];//출력 
	PRODUCT *M[128];//자식 저장 
	N[0] = P;
	while(1){
		k=0;
		for(i=0;i<count;i++){
			if(strcmp(N[i]->d.prod_name,prod_name)==0){
				if(N[i]->d.prod_count>=prod_count){
					N[i]->d.prod_count-=prod_count;
				}
				else{
					printf("판매하는 제품의 수량이 지점이 보유한 제품의 수량보다 큽니다!!!\n");
				}
				end=1;
				break;
			}
			if(N[i]->left!=NULL){
				M[k++] = N[i]->left;
			}
		    if(N[i]->right!=NULL){
				M[k++] = N[i]->right;
			}
		}
		printf("\n");
		count=k; 	//덮어씌운 범위 
		if(end==1||k==0)break;
		for(j=0;j<k;j++){
		   N[j] = M[j];//덮어씌우기 
		   M[j]=NULL;
	    }
	}	
}
void sel_total_list(PART **gar,char *part_name,char *prod_name,int prod_count){
	PART *P;
	P = gar[0];
	int i;
	int cc=0;
	int count=0;
	int chkar[5]={0};
	while(1){
		if(cc!=0&&isEmpty()==1)break;
		count=0;
		for(i=0;i<5;i++){
			if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
				count++;
			}
		}
		if(cc==0&&count!=0){
			chkar[0]=1;
		}
		if(cc==4||count>0){
			if(strcmp(P->name,part_name)==0){
				sell_sel_prod(P->prod,prod_name,prod_count);
				break;
			}
		}
		if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
					chkar[P->link[i]->index]=1;
					push(P);
					P = P->link[i];
					break;
				}
			}
		}
		else if(count==1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
					chkar[P->link[i]->index]=1;
					P = P->link[i];
				}
			}
		}
		else{
			P = pop();
		}
		cc++;
	}
	printf("\n");
}
int bal_insert_prod(PRODUCT *P,char *prod_name){
	int i = 0;
	int j = 0;
	int k = 0;
	int level = 0;
	int count = 1; 
	int end=0;
	int sum_prod_count=0;
	PRODUCT *N[128];//출력 
	PRODUCT *M[128];//자식 저장 
	N[0] = P;
	while(1){
		k=0;
		for(i=0;i<count;i++){
			if(strcmp(N[i]->d.prod_name,prod_name)==0){
				sum_prod_count+=N[i]->d.prod_count;
				end=1;
				break;
			}
			if(N[i]->left!=NULL){
				M[k++] = N[i]->left;
			}
		    if(N[i]->right!=NULL){
				M[k++] = N[i]->right;
			}
		}
		printf("\n");
		count=k; 	//덮어씌운 범위 
		if(end==1||k==0)break;
		for(j=0;j<k;j++){
		   N[j] = M[j];//덮어씌우기 
		   M[j]=NULL;
	    }
	}
	return sum_prod_count;
}
void change_count_prod(PRODUCT *P,char *prod_name,int prod_count){
	int i = 0;
	int j = 0;
	int k = 0;
	int level = 0;
	int count = 1; 
	int end=0;
	int sum_prod_count=0;
	PRODUCT *N[128];//출력 
	PRODUCT *M[128];//자식 저장 
	N[0] = P;
	while(1){
		k=0;
		for(i=0;i<count;i++){
			if(strcmp(N[i]->d.prod_name,prod_name)==0){
				N[i]->d.prod_count = prod_count;
				end=1;
				break;
			}
			if(N[i]->left!=NULL){
				M[k++] = N[i]->left;
			}
		    if(N[i]->right!=NULL){
				M[k++] = N[i]->right;
			}
		}
		printf("\n");
		count=k; 	//덮어씌운 범위 
		if(end==1||k==0)break;
		for(j=0;j<k;j++){
		   N[j] = M[j];//덮어씌우기 
		   M[j]=NULL;
	    }
	}
}
void bal_total_list(PART **gar,char *prod_name){
	PART *P;
	P = gar[0];
	int i;
	int cc=0;
	int count=0;
	int sum_total_prod_count=0;
	int nn_prod_count=0;
	int nnmg_count=0;
	int chkar[5]={0};
	int chkar2[5]={0};
	int chkar3[5]={0};
	while(1){
		if(cc!=0&&isEmpty()==1)break;
		count=0;
		for(i=0;i<5;i++){
			if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
				count++;
			}
		}
		if(cc==0&&count!=0){
			chkar[0]=1;
		}
		if(cc==4||count>0){
			sum_total_prod_count+=bal_insert_prod(P->prod,prod_name);
		}
		if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
					chkar[P->link[i]->index]=1;
					push(P);
					P = P->link[i];
					break;
				}
			}
		}
		else if(count==1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
					chkar[P->link[i]->index]=1;
					P = P->link[i];
				}
			}
		}
		else{
			P = pop();
		}
		cc++;
	}
	printf("\n");
	if(sum_total_prod_count>=5){
		nn_prod_count = sum_total_prod_count/5;
		nnmg_count = sum_total_prod_count % 5;
		P = gar[0];
		cc=0;
		count=0;
		while(1){
			if(cc!=0&&isEmpty()==1)break;
			count=0;
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar2[P->link[i]->index]==0){
					count++;
				}
			}
			if(cc==0&&count!=0){
				chkar2[0]=1;
			}
			if(cc==4||count>0){
				change_count_prod(P->prod,prod_name,nn_prod_count);
			}
			if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
				for(i=0;i<5;i++){
					if(P->link[i]!=NULL&&chkar2[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
						chkar2[P->link[i]->index]=1;
						push(P);
						P = P->link[i];
						break;
					}
				}
			}
			else if(count==1){
				for(i=0;i<5;i++){
					if(P->link[i]!=NULL&&chkar2[P->link[i]->index]==0){
						chkar2[P->link[i]->index]=1;
						P = P->link[i];
					}
				}
			}
			else{
				P = pop();
			}
			cc++;
		}	
		P = gar[0];
		cc=0;
		count=0;
		while(1){
			if(cc==nnmg_count)break;
			count=0;
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar3[P->link[i]->index]==0){
					count++;
				}
			}
			if(cc==0&&count!=0){
				chkar3[0]=1;
			}
			if(count>0)nmg_insert_prod(P->prod,prod_name);
			if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
				for(i=0;i<5;i++){
					if(P->link[i]!=NULL&&chkar3[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
						chkar3[P->link[i]->index]=1;
						push(P);
						P = P->link[i];
						break;
					}
				}
			}
			else if(count==1){
				for(i=0;i<5;i++){
					if(P->link[i]!=NULL&&chkar3[P->link[i]->index]==0){
						chkar3[P->link[i]->index]=1;
						P = P->link[i];
					}
				}
			}
			else{
				P = pop();
			}
			cc++;
		}
	}
}
//같은 제품명을 다시 등록해도 되는지? 
void sell_prod(PART **gar){
	int nprod_count;
	char npart_name[10];
	char nprod_name[10];
	printf("판매할 지점명을 입력:");
	scanf("%s",npart_name); 
	if(chk_part_name(gar,npart_name)==0){
		printf("해당 지점명은 없습니다!!!\n");
		return;
	}
	sel_pr_total_list(gar,npart_name);
	printf("판매할 제품명을 입력:");
	scanf("%s",nprod_name);
	if(chk_prod_name(gar[0]->prod,nprod_name)==0){
		printf("해당 제품명은 없습니다!!!\n");
		return;
	}
	printf("판매할 수량을 입력:");
	scanf("%d",&nprod_count); 
	sel_total_list(gar,npart_name,nprod_name,nprod_count);//판매 
	//전체 지점의 해당 제품의 수량의 합계를 구하고 가맹점수와 비교하고 분배해줄지 결정 나머지는 수량을 하나씩 넣기 
	
	bal_total_list(gar,nprod_name); 
	pr_total_list(gar); 
}
////
void sel_pr_prod(PRODUCT *P,char *prod_name){
	int i = 0;
	int j = 0;
	int k = 0;
	int level = 0;
	int count = 1; 
	int end=0;
	PRODUCT *N[128];//출력 
	PRODUCT *M[128];//자식 저장 
	
	N[0] = P;
	while(1){
		k=0;
		for(i=0;i<count;i++){//한 계층 출력하기 
			if(strcmp(N[i]->d.prod_name,prod_name)==0){
				printf("제품명:%s ",N[i]->d.prod_name);
				printf("수량:%d ",N[i]->d.prod_count);
				printf("단가:%d ",N[i]->d.money);
				end = 1;
				break;
			}
			if(N[i]->left!=NULL){	//자식 저장 
				M[k++] = N[i]->left;
			}
		    if(N[i]->right!=NULL){	
				M[k++] = N[i]->right;
			}
		}
		printf("\n");
		count=k; 	//덮어씌울 범위 
		if(end==1||k==0)break;
		for(j=0;j<k;j++){	//다음 계층만큼  덮어씌우기 
		   N[j] = M[j];
		   M[j]=NULL;
	    }
	}	
}
void pr_part(PART **gar,char *prod_name){
	PART *P;
	P = gar[0];
	int i;
	int cc=0;
	int count=0;
	int chkar[5]={0};
	while(1){
		if(cc!=0&&isEmpty()==1)break;
		count=0;
		for(i=0;i<5;i++){
			if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
				count++;
			}
		}
		if(cc==0&&count!=0){
			chkar[0]=1;
		}
		if(cc==4||count>0){
			printf("지점명:%s\n",P->name);
			sel_pr_prod(P->prod,prod_name);
		}
		if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
					chkar[P->link[i]->index]=1;
					push(P);
					P = P->link[i];
					break;
				}
			}
		}
		else if(count==1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
					chkar[P->link[i]->index]=1;
					P = P->link[i];
				}
			}
		}
		else{
			P = pop();
		}
		cc++;
	}
}
void plus_part(PART **gar,char *prod_name,int prod_count){
	PART *P;
	P = gar[0];
	int i;
	int cc=0;
	int count=0;
	int chkar[5]={0};
	int chkar2[5]={0};
	int chkar3[5]={0};
	int chkar4[5]={0};
	int sum_total_prod_count=0;
	int nnprod_count=0;
	int nmgprod_count=0;
	while(1){
		if(cc!=0&&isEmpty()==1)break;
		count=0;
		for(i=0;i<5;i++){
			if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
				count++;
			}
		}
		if(cc==0&&count!=0){
			chkar[0]=1;
		}
		if(cc==4||count>0){
			sum_total_prod_count+=bal_insert_prod(P->prod,prod_name);
		}
		if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
					chkar[P->link[i]->index]=1;
					push(P);
					P = P->link[i];
					break;
				}
			}
		}
		else if(count==1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
					chkar[P->link[i]->index]=1;
					P = P->link[i];
				}
			}
		}
		else{
			P = pop();
		}
		cc++;
	}
	cc=0;
	count=0;
	P = gar[0];
	sum_total_prod_count+=prod_count;
	if(sum_total_prod_count>=5){
		nnprod_count = sum_total_prod_count / 5;
		nmgprod_count = sum_total_prod_count % 5;
		while(1){
			if(cc!=0&&isEmpty()==1)break;
			count=0;
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar2[P->link[i]->index]==0){
					count++;
				}
			}
			if(cc==0&&count!=0){
				chkar2[0]=1;
			}
			if(cc==4||count>0){
			 	change_count_prod(P->prod,prod_name,nnprod_count);
			}
			if(count>1){
				for(i=0;i<5;i++){
					if(P->link[i]!=NULL&&chkar2[P->link[i]->index]==0){
						chkar2[P->link[i]->index]=1;
						push(P);
						P = P->link[i];
						break;
					}
				}
			}
			else if(count==1){
				for(i=0;i<5;i++){
					if(P->link[i]!=NULL&&chkar2[P->link[i]->index]==0){
						chkar2[P->link[i]->index]=1;
						P = P->link[i];
					}
				}
			}
			else{
				P = pop();
			}
			cc++;
		}
		P = gar[0];
		cc=0;
		count=0;
		while(1){
			if(cc==nmgprod_count)break;
			count=0;
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar3[P->link[i]->index]==0){
					count++;
				}
			}
			if(cc==0&&count!=0){
				chkar3[0]=1;
			}
			if(count>0)nmg_insert_prod(P->prod,prod_name);
			if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
				for(i=0;i<5;i++){
					if(P->link[i]!=NULL&&chkar3[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
						chkar3[P->link[i]->index]=1;
						push(P);
						P = P->link[i];
						break;
					}
				}
			}
			else if(count==1){
				for(i=0;i<5;i++){
					if(P->link[i]!=NULL&&chkar3[P->link[i]->index]==0){
						chkar3[P->link[i]->index]=1;
						P = P->link[i];
					}
				}
			}
			else{
				P = pop();
			}
			cc++;
		}
	}
	else{
		P = gar[0];
		cc=0;
		count=0;
		while(1){
			if(cc==sum_total_prod_count)break;
			count=0;
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar4[P->link[i]->index]==0){
					count++;
				}
			}
			if(cc==0&&count!=0){
				chkar4[0]=1;
			}
			if(count>0)nmg_insert_prod(P->prod,prod_name);
			if(count>1){
				for(i=0;i<5;i++){
					if(P->link[i]!=NULL&&chkar4[P->link[i]->index]==0){
						chkar4[P->link[i]->index]=1;
						push(P);
						P = P->link[i];
						break;
					}
				}
			}
			else if(count==1){
				for(i=0;i<5;i++){
					if(P->link[i]!=NULL&&chkar4[P->link[i]->index]==0){
						chkar4[P->link[i]->index]=1;
						P = P->link[i];
					}
				}
			}
			else{
				P = pop();
			}
			cc++;
		}
	}	
}
void plus_prod(PART **gar){
	int nprod_count;
	char nprod_name[10];
	printf("추가할 제품명을 입력:");
	scanf("%s",nprod_name);
	if(chk_prod_name(gar[0]->prod,nprod_name)==0){
		printf("해당 제품명은 없습니다!!!\n");
		return;
	}
	pr_part(gar,nprod_name);
	printf("추가할 수량을 입력:");
	scanf("%d",&nprod_count);
	plus_part(gar,nprod_name,nprod_count); 
	pr_total_list(gar);
}
////
void pr_prod(PART **gar){
	char nprod_name[10];
	printf("조회할 제품명을 입력:");
	scanf("%s",nprod_name);
	if(chk_prod_name(gar[0]->prod,nprod_name)==0){
		printf("해당 제품명은 없습니다!!!\n");
		return;
	}
	pr_part(gar,nprod_name);
}
////
//첫 제품이 갯수가 하나만 있을때 첫 제품을 삭제할떄 다운 (가:1 나:10 다:10에서 가를 삭제)
//트리삭제랑 제품분배할떄 첫 제품을 지울떄 문제있는지 
void del_single_prod(PRODUCT *P,char *prod_name){
	PRODUCT *H = P;
	PRODUCT *B = P;
	PRODUCT *PP;
	PRODUCT *BB;
	PRODUCT *BL;
	PRODUCT *BE;
	PRODUCT *BBE;
	if(strcmp(H->d.prod_name,prod_name)==0&&H->left==NULL&&H->right==NULL){
		strcpy(H->d.prod_name," ");
		H->d.money = 0;
		H->d.prod_count = 0;
		return;
	}
	while(1){ 
		if(P==NULL)break;
		if(strcmp(P->d.prod_name,prod_name)==0){
			if(P->left==NULL&&P->right==NULL){//단말에선 단말만 삭제 
				if(B->left==P){
					B->left=NULL;
				}
				else if(B->right==P){
					B->right=NULL;
				}
				free(P);
				break;
			}
			else{//자식이 있다 
				PP = P;
				BB = PP;
				BE = PP;
				BL = PP;
				if(PP->right!=NULL){
					PP = PP->right;
					if(PP->left==NULL&&PP->right==NULL){
						if(B==P){
							P->d = PP->d;
							if(BB->left==PP){
								BB->left = NULL;
								free(PP);
								break;
							}
							else if(BB->right==PP){
								BB->right = NULL;
								free(PP);
								break;
							}
						}
						else if(B->left==P){
							P->d = PP->d;
							if(BB->left==PP){
								BB->left = NULL;
								free(PP);
								break;
							}
							else if(BB->right==PP){
								BB->right = NULL;
								free(PP);
								break;
							}
						}
						else if(B->right==P){
							P->d = PP->d;
							if(BB->left==PP){
								BB->left = NULL;
								free(PP);
								break;
							}
							else if(BB->right==PP){
								BB->right = NULL;
								free(PP);
								break;
							}
						}
					}
					if(PP->left!=NULL){
						while(PP->left!=NULL||PP->right!=NULL){
							BL = PP;
							PP = PP->left;
						}
						if(B==P){
							P->d = PP->d;
							if(BL->left==PP){
								BL->left = NULL;
								free(PP);
								break;
							}
							else if(BL->right==PP){
								BL->right = NULL;
								free(PP);
								break;
							}
						}
						else if(B->left==P){
							P->d = PP->d;
							if(BL->left==PP){
								BL->left = NULL;
								free(PP);
								break;
							}
							else if(BL->right==PP){
								BL->right = NULL;
								free(PP);
								break;
							}
						}
						else if(B->right==P){
							P->d = PP->d;
							if(BL->left==PP){
								BL->left = NULL;
								free(PP);
								break;
							}
							else if(BL->right==PP){
								BL->right = NULL;
								free(PP);
								break;
							}
						}
					}
					//BE: 지울값, PP: 진행값 
					//지울값부터 한 칸씩 위로 당기기  
					else{//문제 되는 상황  그냥 첫번쨰 지울떄 다운 
						while(PP->left!=NULL||PP->right!=NULL){
							BE->d = PP->d;	 //위로 당기기 
							BE = PP;		//지울값 이동 
							PP = PP->right;	
						}
						BE->d  = PP->d;		//위로 당기기 
						if(BE->left==PP){
							BE->left=NULL;
							free(PP);
							break;
						}
						else if(BE->right==PP){
							BE->right=NULL;
							free(PP);
							break;
						}
					}
				}
				else if(PP->left!=NULL){
					PP = PP->left;
					if(PP->left==NULL&&PP->right==NULL){
						if(B==P){
							P->d = PP->d;
							if(BB->left==PP){
								BB->left = NULL;
								free(PP);
								break;
							}
							else if(BB->right==PP){
								P->right = NULL;
								free(PP);
								break;
							}
						}
						else if(B->left==P){
							P->d = PP->d;
							if(BB->left==PP){
								BB->left = NULL;
								free(PP);
								break;
							}
							else if(BB->right==PP){
								BB->right = NULL;
								free(PP);
								break;
							}
						}
						else if(B->right==P){
							P->d = PP->d;
							if(BB->left==PP){
								BB->left = NULL;
								free(PP);
								break;
							}
							else if(BB->right==PP){
								BB->right = NULL;
								free(PP);
								break;
							}
						}
					}
					if(PP->right!=NULL){
						while(PP->left!=NULL||PP->right!=NULL){
							BE = PP;
							PP = PP->right;
						}
						P->d = PP->d;
						if(BE->left==PP){
							BE->left = NULL;
							free(PP);
							break;
						}
						else if(BE->right==PP){
							BE->right = NULL;
							free(PP);
							break;
						}
					}
					else{
						while(PP->left!=NULL||PP->right!=NULL){
							BL->d = PP->d;
							BL = PP;
							PP = PP->left;
						}
						BL->d = PP->d;
						if(BL->left==PP){
							BL->left = NULL;
							free(PP);
							break;
						}
						else if(BL->right==PP){
							BL->right = NULL;
							free(PP);
							break;
						}
					}
				}
			}
		}
		else{
			if(strcmp(P->d.prod_name,prod_name)>0){
				B = P;
				P = P->left;
			}
			else{
				B = P;
				P = P->right;
			}
		}
	}
}
void del_part(PART **gar,char *prod_name){//모든  지점 방문하지 못하고 있다. 
	PART *P;
	P = gar[0];
	int i;
	int cc=0;
	int count=0;
	int chkar[5]={0};
	while(1){
		if(cc!=0&&isEmpty()==1)break;
		count=0;
		for(i=0;i<5;i++){
			if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
				count++;
			}
		}
		if(cc==0&&count!=0){
			chkar[0]=1;
		}
		if(cc==4||count>0){
			del_single_prod(P->prod,prod_name);
		}
		if(count>1){//이미 4개의 링크가 다 연결 되어있는데 링크수로 나누는게 맞는지? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){//문자열인데 배열로 어떻게 표현할지? 
					chkar[P->link[i]->index]=1;
					push(P);
					P = P->link[i];
					break;
				}
			}
		}
		else if(count==1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
					chkar[P->link[i]->index]=1;
					P = P->link[i];
				}
			}
		}
		else{
			P = pop();
		}
		cc++;
	}
}
void del_prod(PART **gar){
	char delprod_name[10];
	printf("삭제할 제품명을 입력하세요:");
	scanf("%s",delprod_name);
	if(chk_prod_name(gar[0]->prod,delprod_name)==0){
		printf("해당 제품명은 없습니다!!!\n");
		return;
	} 
	del_part(gar,delprod_name);
	pr_total_list(gar);
}
//현재 위치의 연결된 링크 수를 세고(가장 최근에 왔던데 돌아가려고) 링크가 더 갈데가 있으면 푸시하고,없으면 안 넣는다. 
//링크수는 2개 1개 0개 생기는데 2개는 필요에 따라 푸시하고 1개는 이동만하고 0개는 팝하기 
STACK *top;
int main(){
	//파일 작성 후 바로 첫화면에서 "서울"이 안뜬다.
	srand((unsigned int)time(NULL));
	top = s_create();
	int cc=0;
	int count=0;
	int chkar[5]={0};
	int i,j;
	char *part_sen[5];
	char part_name[10];
 	PART *P,*gar[5];//다른함수에서 이중포인터로 포인터배열을 가져오기 
 	f_check(gar);
	printf("지점명: "); 
	P = gar[0];
	//스택 이용해서 깊이우선탐색하기 
	while(1){
		if(cc!=0&&isEmpty()==1)break;
		count=0;
		for(i=0;i<5;i++){
			if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
				count++;
			}
		}
		if(cc==0&&count!=0){
			printf("%s ",P->name);
			chkar[0]=1;
		}
		if(count>1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
					chkar[P->link[i]->index]=1;
					printf("%s ",P->link[i]->name);
					push(P);
					P = P->link[i];
					break;
				}
			}
		}
		else if(count==1){
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){
					chkar[P->link[i]->index]=1;
					printf("%s ",P->link[i]->name);
					P = P->link[i];
				}
			}
		}
		else{
			P = pop();
		}
		cc++;
	}
	printf("\n");
	int opt;
	while(opt!=6){
		printf("1.제품등록, 2.제품판매, 3.수량추가, 4.제품조회, 5.제품삭제 6.종료\n");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				sign_up_prod(gar); 
				break;
			case 2:
				sell_prod(gar);
				break;
			case 3:
				plus_prod(gar);//수량추가가 안된다. 
				break;
			case 4:
				pr_prod(gar);
				break;
			case 5:
				del_prod(gar);
				break;
			case 6:
				printf("종료!!!\n"); 
				break;
			default:
				printf("잘못입력!!!\n");
			break;
		}
	}
	f_write(gar);//첫번째 제품만 덜 더해진다. 
	return 0;
}

		 
