#include"stdio.h"
#include"windows.h"
#include"conio.h"


#define M 3
#define row 20


int m[row][row];
int n[M][M] = {0,1,0,1,0,1,0,1,0};
char w,a,s,d;




void  push_m(){
    for(int i = 0;i < row;i++){
        for(int j = 0;j < row;j++){
            m[i][j] = 0;
        }
    }
}




void add_m(int x,int y){
    if(x >= 0 && x < row - M  && y >= 0 && y < row - M ){
        for(int i = 0;i < 3;i++){
            for(int j = 0;j < 3;j++){
                m[x + i][y + j] = n[i][j];
            }
        }
    }
}


void print_m(){
    for(int i = 0;i < row;i++){
        printf("\n");
        for(int j = 0;j < row;j++){
            if(m[i][j] == 0)
                printf("□");
            else
                printf("★");
        }
    }
}


_Noreturn void direction(int x,int y){
    while(1){
        char ch;
        switch(ch = getch()){
            case 'w': x = x - 1;
                break;
            case 'a': y = y - 1;
                break;
            case 's': x = x + 1;
                break;
            case 'd': y = y + 1;
            default : break;
        }
        push_m();
        add_m(x,y);
        system("cls");
        print_m();

    }
}






int main(int argc,char** argv){
    int x = 5,y = 5;
    push_m();
    system("color 1e");
    add_m(x,y);
    print_m();
    direction(x,y);
    return 0;
}