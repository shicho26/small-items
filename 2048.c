#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void move(int num[4][4],char ch){
    int i,j,k;
    switch(ch){
        case 'a':
        for(i=0;i<4;++i){
            for(j=1;j<4;++j){
                if(num[i][j]){
                    k=j;
                    while((!num[i][k-1]||num[i][k-1]==num[i][k])&&k>0){
                        num[i][k-1]+=num[i][k];
                        num[i][k]=0;
                        k--;
                    }
                }
            }
        }
        break;
        case 'w':
        for(i=1;i<4;++i){
            for(j=0;j<4;++j){
                k=i;
                if(num[k][j]){
                    while((num[k-1][j]==0||num[k-1][j]==num[k][j])&&k>0){
                        num[k-1][j]+=num[k][j],num[k][j]=0;
                        k--;
                    }
                }
            }
        }
        break;
        case 'd':
        for(i=0;i<4;++i){
            for(j=2;j>=0;--j){
                k=j;
                if(num[i][k]){
                    while((num[i][k+1]==0||num[i][k+1]==num[i][k])&&k<3){
                        num[i][k+1]+=num[i][k],num[i][k]=0;
                        ++k;
                    }
                }
            }
        }
        break;
        case 's':
        for(i=2;i>=0;--i){
            for(j=0;j<4;++j){
                k=i;
                if(num[k][j]){
                    while((num[k+1][j]==0||num[k+1][j]==num[k][j])&&k<3){
                        num[k+1][j]+=num[k][j],num[k][j]=0;
                        ++k;
                    }
                }
            }
        }
        break;
        default:
        ;
    }
}

int create_num(int num[4][4],int blanks[]){
    int i,j,rest=blanks[0],count=0;
    if(!rest)   return 0;
    while(rest>0&&count<2){
        i=rand()%rest+1;
        i=blanks[i];    //i=1~16
        j=i%4,i/=4;
        if(!j)  i--,j=3;
        else    j--;
        num[i][j]=2;
        count++;
    }
    return 1;
}

void blank_field(int num[4][4],int blanks[]){
    memset(blanks,0,17*sizeof(int));
    int count=0;
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            if(!num[i][j]){
                blanks[++count]=4*i+j+1;    //1基顺序
            }
        }
    }
    blanks[0]=count;
}

void prt_board(int num[4][4]){
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            printf("%d\t",num[i][j]);
        }
        puts("\n");
    }
    puts("\n");
}

void get_score(int num[4][4],int* score){
    int s=0;
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            s+=num[i][j];
        }
    }
    *score=s;
}

void game_2048(){
    int num[4][4]={0},blanks[17]={0},count=0,score;
    printf("Press any key to start the game.\n");
    char ch;
    getch();
    while(1){
        blank_field(num,blanks);
        if(!(create_num(num,blanks))){
            printf("Game Over.\n");
            break;
        }
        get_score(num,&score);
        system("cls");
        printf("Step %d\t\t\tscore:%d\n\n",++count,score);
        prt_board(num);
        printf("\nw:up\ta:left\ts:down\td:right\n\n");
        ch=0;
        while(!(ch=='w'||ch=='a'||ch=='s'||ch=='d')){
            ch=getch();
        }
        move(num,ch);
    }
}

int main(){
    srand(time(NULL));
    game_2048();
    return 0;
}