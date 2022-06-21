#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct stack{
	int i;
	int j;
	struct stack *next;
}STACK;

STACK* top=NULL;
int puan;

int popi(){
    return top->i;
}

int popj(){
	STACK *temp = top;
	int temp_data = top->j;
	top = top->next;
	free(temp);
    return temp_data;
}

void push(int i,int j){
	STACK *yeni;
    yeni = (STACK*)malloc(sizeof(STACK));
    yeni->i = i;
    yeni->j = j;
    if (top == NULL) {
        yeni->next = NULL;
    } else {
        yeni->next = top;
    }
    top = yeni;
}

void uyu(){
	int i,j;
	for(i=0;i<20000;i++){
		for(j=0;j<10000;j++);
	}
}

void DFS(int map[32][44],int i, int j,char yol[32][44]){
	push(i,j);
	int flag=0, flag2=0;
    while(flag==0){
    	flag2=0;
    	i=popi();
    	j=popj();
    	if(i==29 && j==41)
    		flag=1;
    	
    	map[i][j]=2;
		
    	if(map[i][j+1]==1){
    		push(i,j+1);
    		flag2=1;
		}
		if(map[i+1][j]==1){
    		push(i+1,j);
    		flag2=1;
		}
		if(map[i][j-1]==1){
    		push(i,j-1);
    		flag2=1;
		}
		if(map[i-1][j]==1){
    		push(i-1,j);
    		flag2=1;
		}
		if(flag2==0){
			puan-=5;
		}
		if(yol[i][j]=='O'){
			puan+=10;
		}
		
		for(i=0;i<31;i++){
    		for(j=0;j<44;j++){
    			if(map[i][j]==2){
    				printf("*");
				}
				else{
					printf("%c",yol[i][j]);
				}
			}
			printf("\n");
		}
		printf("\n\n\n\n");
		uyu();
	}
}

void randomElma(char yol[32][44]){
	srand(time(NULL));
	int i,j;
	for(i=0;i<32;i++){
		for(j=0;j<44;j++){
			if(yol[i][j]==' '){
				if((rand()%10)==1){
					yol[i][j]='O';
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int N=31, M=43;
	int i=0, j=0;
	char ch;
	int map[32][44];
	char yol[32][44];
	puan=0;
	
    FILE *dosya;
	dosya=fopen("harita.txt","r");
	
    while ((ch = fgetc(dosya)) != EOF){
    	yol[i][j]=ch;
        if(ch==' ')
        	map[i][j]=1;
		else
			map[i][j]=0;
		if(ch=='\n'){
			i++; j=0;
		}
		else{
			j++;
		}
    }
	
	
	fclose(dosya);
    map[29][1]=1;
    map[29][41]=1;
    
    randomElma(yol);
    
    DFS(map,29,1,yol);
	printf("\nTOPLAM SCORE: %d",puan);
	return 0;
}
