#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define MAX 101

int Max(int a,int b){
	if(a>b) return a;
	return b;
}
bool checkonRow(int r_checked[],int i_checked,int value){
	int i;
	for(i=1;i<=i_checked;i++){
		if(r_checked[i]==value){
			return true;
		}
	}
	return false;
}

void printMatrix(int a[][MAX],int r,int c){
	int i,j;
	for(i=1;i<=r;i++){
		for(j=1;j<=c;j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
}

void multipleMatrix(int a[][MAX],int b[][MAX],int ra,int ca,int rb,int cb){
	system("cls");
	int c[MAX][MAX];
	int r_max = Max(ra,rb);
	int c_max = Max(ca,cb);
	int i,j,x;
	
	//Neu cot x dong
	for(i=1;i<=r_max;i++){
		for(j=1;j<=c_max;j++){
			c[i][j] = 0;
			for(x=1;x<=r_max;x++){
				c[i][j] += a[i][x] * b[x][j];
			}
		}
	}
	printf("Your matrix after multipling: \n");
	printMatrix(c,r_max,c_max);
	getchar();
}

int RankofMatrix(int in[][MAX],int r,int c){
	int i,j;
	int r_checked[r+1],i_checked = 1;
	int a[MAX][MAX];
	//Sao chep mang
	for(i=1;i<=r;i++){
		for(j=1;j<=c;j++){
			a[i][j] = in[i][j];
		}
	}
	
	//Chay column xuong duoi xem thang nao cung cap
	for(j=1;j<=c;j++){
		int count = 0;
		int dongmau,division,product;
		for(i=1;i<=r;i++){
			if(a[i][j] != 0 && count == 0){
				if(!checkonRow(r_checked,i_checked,i)){
					r_checked[i_checked] = i;
					i_checked++;
					count++;
				    dongmau = i;
				    division = a[i][j];
				    continue;
				}
				
			}
			//Xuat hien dong cung cap
			if(a[i][j] != 0 && count != 0){
			    product = a[i][j];
			    //Chay -> de tru hang dau
			    //x la hang ngang
			    int x;
			    for(x=j;x<=c;x++){
			    	a[i][x] -= product*a[dongmau][x]/division;
				}
			}
		}
	}
	int count = 0;
	//Check rank
	for(i=1;i<=r;i++){
		for(j=1;j<=c;j++){
			if(a[i][j] != 0){
				count++;
				break;
			}
		}
	}
	printMatrix(a,r,c);
	return count;
}

void enterMatrix(int a[][MAX],int* r,int* c){
	*r = 1;
	*c = 0;
	char check;
	int choice;
	//Nhap hang dau de xac dinh columns
	system("cls");
	printf("Enter your matrix: \n");
	do{
		*c=*c+1;
		scanf("%d",&a[1][*c]);
		
		check = getchar();
	}while(check!='\n');
	
	
	//Nhap tiep tuc de xac dinh rows
	do{
		system("cls");
		printf("\nYour matrix: \n");
		printMatrix(a,*r,*c);
		printf("\n");
		printf("====================================== MATRIX MANAGEMENT ======================================\n\n\n");
        printf("\t\t\t\t\t[1]=> Continue.\n");
        printf("\n");
        printf("\t\t\t\t\t[2]=> Return.\n");
        printf("\n");
        printf("================================================================================================\n\n");
		fflush(stdin);
		printf("\t\t\t\tEnter your choice: ");scanf("%d",&choice);
		
		if(choice ==1){
			*r=*r+1;
			int count = 0;
			do{
				system("cls");
	            printf("Enter your matrix: \n");
				count++;
		        scanf("%d",&a[*r][count]);
		        
		        check = getchar();
		        
				if(count==*c+1){
					printf("\n");
					printf("\t\t\t\t\tYour inputs are invalid.\n");
                    printf("\t\t\t\t\tPlease enter again.\n");
                    fflush(stdin);
                    getchar();
                    count = 0;
                    continue;
				}
				if(check == '\n' && count<*c){
					printf("\n");
					printf("\t\t\t\t\tYour inputs are invalid.\n");
                    printf("\t\t\t\t\tPlease enter again.\n");
                    fflush(stdin);
                    getchar();
                    count = 0;
                    continue;
				}
				if(check == '\n' && count==*c) break;
	        }while(count<=*c+1);
		}
	}while(choice!=2);
}

int main(){
	int a[MAX][MAX];
	int b[MAX][MAX];
	int ra=4,rb=4,ca=4,cb=4;
	int choice,ichoice,rank;
	
	do{
		system("cls");
		printf("Matrix A: \n");
	    printMatrix(a,ra,ca);
	    printf("Matrix B: \n");
	    printMatrix(b,rb,cb);
	
    printf("====================================== MATRIX MANAGEMENT ======================================\n\n\n");
    printf("\t\t\t\t\t[1]=> Enter matrix.\n");
    printf("\n");
    printf("\t\t\t\t\t[2]=> Multiple two matrix a and b.\n");
    printf("\n");
    printf("\t\t\t\t\t[3]=> Find the rank of the matrix.\n");
    printf("\n");
    printf("\t\t\t\t\t[4]=> Exit\n\n");
    printf("================================================================================================\n\n");
    printf("\t\t\t\tEnter your choice: ");scanf("%d",&choice);
    fflush(stdin);
    
	switch(choice){
		case 1:
			do{
			system("cls");
			printf("\t\t\t\t\t[1]=> Enter matrix A.\n");
            printf("\n");
            printf("\t\t\t\t\t[2]=> Enter matrix B.\n");
            printf("\n");
            printf("\t\t\t\tEnter your choice: ");
			scanf("%d",&ichoice);
            if(ichoice == 1){
            	enterMatrix(a,&ra,&ca);
			}
			else if (ichoice == 2){
				enterMatrix(b,&rb,&cb);
			}
            }while(ichoice !=1 && ichoice != 2);
            break;
		case 2:
			//TH ko nhan dc
			if(ca!=rb && cb!=ra){
				printf("\t\t\t\tra = %d, ca = %d, rb = %d, cb = %d.\n",ra,ca,rb,cb);
				printf("\t\t\t\tThe number of rows and the number of columns are not equal!\n");
				printf("\t\t\t\tPlease try again!\n");
				getchar();
				break;
			}
			//Neu row a = column b
			else if(ca == rb){
				multipleMatrix(a,b,ra,ca,rb,cb);
			}
			else if(cb == ra){
				multipleMatrix(b,a,rb,cb,ra,ca);
			}
			break;
		case 3:
			do{
			system("cls");
			printf("\t\t\t\t\t[1]=> Check rank of matrix A.\n");
            printf("\n");
            printf("\t\t\t\t\t[2]=> Check rank of matrix B.\n");
            printf("\n");
            printf("\t\t\t\tEnter your choice: ");
			scanf("%d",&ichoice);
            if(ichoice == 1){
            	rank = RankofMatrix(a,ra,ca);
            	printf("\n\n");
            	printf("\t\t\t\t\tRank of matrix A = %d.\n",rank);
			}
			else if (ichoice == 2){
				rank = RankofMatrix(b,rb,cb);
				printf("\n\n");
            	printf("\t\t\t\t\tRank of matrix B = %d.\n",rank);
			}
            }while(ichoice !=1 && ichoice != 2);
            fflush(stdin);
            getchar();
            break;
		}
            
    }while(choice!=4);
    
	
}
