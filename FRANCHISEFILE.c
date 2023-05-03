#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef FRANCHISEFILE_H
#define FRANCHISEFILE_H
#include "FRANCHISECOMMON.h"
#include "FRANCHISEFILE.h"
void nmg_part(PART **gar,char *prod_name,int rc){
	PART *P;
	int chkar2[5]={0};
	P = gar[0];
	int cc=0;
	int count=0;
	int i;
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
		if(count>0)nmg_insert_prod(P->prod,prod_name);
		if(count>1){//�̹� 4���� ��ũ�� �� ���� �Ǿ��ִµ� ��ũ���� �����°� �´���? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar2[P->link[i]->index]==0){//���ڿ��ε� �迭�� ��� ǥ������? 
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
}
void save_part(PART **gar,char *prod_name,int prod_count){
	PART *P;
	P = gar[0];
	int i;
	int cc=0;
	int count=0;
	int chkar[5]={0};
	int money=0;
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
			insert_prod(P->prod,prod_name,prod_count,money);
		}
		if(count>1){//�̹� 4���� ��ũ�� �� ���� �Ǿ��ִµ� ��ũ���� �����°� �´���? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){//���ڿ��ε� �迭�� ��� ǥ������? 
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
void f_check(PART **gar){
	FILE *fp,*ffp;
	char part_list[10];
	char ch;
	char *res;
	int i = 0;
	int j=0;
	int k=0;
	int num=0;
	char prod_name[10];
	int prod_count=0;
	int res2;
	int rc=0;
	
	fp = fopen("PART.txt","r");	
	while(1){
		res = fgets(part_list,sizeof(part_list),fp);
		if(res==NULL)break;
		part_list[strlen(part_list)-1]='\0';
		gar[k] = create_part();
		strcpy(gar[k]->name,part_list);
		gar[k]->index = num;
		num++;
		k++;
	}
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if(i!=j)gar[i]->link[j] = gar[j];
		}
	}
	fclose(fp);
	
	fp = fopen("PRODUCT.txt","r");
	while(1){
		res2 = fscanf(fp,"%s %d\n",prod_name,&prod_count);
		if(res2==EOF)break;
		rc = prod_count % 5;
		save_part(gar,prod_name,prod_count);
		nmg_part(gar,prod_name,rc);
	}
	fclose(fp);	
}
//��ǰ����  2�������ڹ迭�� �־���ϴ���? 
void fwrite_sum_prod_count(PRODUCT *P,SUM *S,FILE *fp){
	int i = 0;
	int j = 0;
	int k = 0;
	int level = 0;
	int count = 1; 
	int end=0;
	int sum_prod_count=0;
	SUM *SS;
	SS = S->link;
	PRODUCT *N[128];//��� 
	PRODUCT *M[128];//�ڽ� ���� 
	N[0] = P;
	while(1){
		k=0;
		for(i=0;i<count;i++){
			fprintf(fp,"%s %d\n",N[i]->d.prod_name,SS->sum_prod_count);
			SS = SS->link;
			if(N[i]->left!=NULL){
				M[k++] = N[i]->left;
			}
		    if(N[i]->right!=NULL){
				M[k++] = N[i]->right;
			}
		}
		printf("\n");
		count=k; 	//����� ���� 
		if(k==0)break;
		for(j=0;j<k;j++){
		   N[j] = M[j];//������ 
		   M[j]=NULL;
	    }
	}
}
void sum_prod_count(PRODUCT *P,SUM *S){
	int i = 0;
	int j = 0;
	int k = 0;
	int level = 0;
	int count = 1; 
	int end=0;
	int sum_prod_count=0;
	SUM *SS;
	SS = S->link;
	PRODUCT *N[128];//��� 
	PRODUCT *M[128];//�ڽ� ���� 
	N[0] = P;
	while(1){
		k=0;
		for(i=0;i<count;i++){
			SS->sum_prod_count+=N[i]->d.prod_count;
			SS = SS->link;
			if(N[i]->left!=NULL){
				M[k++] = N[i]->left;
			}
		    if(N[i]->right!=NULL){
				M[k++] = N[i]->right;
			}
		}
		printf("\n");
		count=k; 	//����� ���� 
		if(k==0)break;
		for(j=0;j<k;j++){
		   N[j] = M[j];//������ 
		   M[j]=NULL;
	    }
	}
}
void add_sum_prod(PRODUCT *P,SUM *S){
	int i = 0;
	int j = 0;
	int k = 0;
	int level = 0;
	int count = 1; 
	int end=0;
	int sum_prod_count=0;
	PRODUCT *N[128];//��� 
	PRODUCT *M[128];//�ڽ� ���� 
	N[0] = P;
	while(1){
		k=0;
		for(i=0;i<count;i++){
			add_sum(S,N[i]->d.prod_count);
			if(N[i]->left!=NULL){
				M[k++] = N[i]->left;
			}
		    if(N[i]->right!=NULL){
				M[k++] = N[i]->right;
			}
		}
		printf("\n");
		count=k; 	//����� ���� 
		if(k==0)break;
		for(j=0;j<k;j++){
		   N[j] = M[j];//������ 
		   M[j]=NULL;
	    }
	}
}
void sum_total_list(PART **gar,SUM *S,FILE *fp){
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
			if(strcmp(P->name,gar[0]->name)==0){
				add_sum_prod(P->prod,S);
			}
			else{
				sum_prod_count(P->prod,S);
				if(cc==4)fwrite_sum_prod_count(P->prod,S,fp);
			}
		}
		if(count>1){//�̹� 4���� ��ũ�� �� ���� �Ǿ��ִµ� ��ũ���� �����°� �´���? 
			for(i=0;i<5;i++){
				if(P->link[i]!=NULL&&chkar[P->link[i]->index]==0){//���ڿ��ε� �迭�� ��� ǥ������? 
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
void f_write(PART **gar){//���� ���Ⱑ ���� 
	SUM *S;
	S = sum_create();
	FILE *fp;
	fp = fopen("PRODUCT.txt","w");
	sum_total_list(gar,S,fp);
	fclose(fp);
}
		
#endif
