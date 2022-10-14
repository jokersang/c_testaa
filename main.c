#include<stdio.h>
#include<windows.h>   //���û��Ӽ��̻�õ�����������
#include<conio.h>   //����û����̵�����
//����ȫ�ֱ���
int high,width;   //����߽�
int position_x,position_y;  //�ɻ�λ��
int bullet_x,bullet_y;  //�ӵ�λ��
int enemy_x,enemy_y;  //�о��ɻ�
int score;    //��÷���
int flag;    //�ɻ�״̬
void gotoxy(int x,int y);   //����ƶ���(x,y)λ��
void welcometogame();     //��ʼ������
int color(int c);       //����������ɫ
void explation();   //��Ϸ�Ҳ���ʾ
void scoreandtips();  //��ʾ��Ϸ��ʾ
void show();   //��ʾ��Ϸ����
void endgame();   //��Ϸ����
/**
 * ������ɫ����
 */
int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);    //����������ɫ
    return 0;
}

/**
* ���ù��λ��
*/
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}



void welcometogame() //��ʼ����
{
    int n;
    color(15);
    gotoxy(43,10);
    printf("�� �� �� ս");
    color(11);
    gotoxy(25, 22);
    printf("1.��ʼ��Ϸ");
    gotoxy(45, 22);
    printf("2.��Ϸ˵��");
    gotoxy(65, 22);
    printf("3.�˳���Ϸ");
    gotoxy(40,27);
    color(3);
    printf("��ѡ�� 1 2 3:");
    color(14);
    scanf("%d", &n);   //����ѡ��
    switch (n)
    {
        case 1:
            system("cls");
            show();
            break;
        case 2:
            explation();    //��Ϸ˵������
            break;
        case 3:
            exit(0);    //�˳���Ϸ
            break;
        default:
            color(12);
            gotoxy(40,28);
            printf("������1-3֮�����!");
            _getch();  //���������
            system("cls"); //����
            welcometogame();
    }
}


void explation() //��Ϸ��ʾ
{
    int i,j = 1;
    system("cls");
    color(10);
    gotoxy(44,1);
    printf("��Ϸ˵��");
    color(2);
    for (i = 3; i <= 28; i++)  //������±߿�===
    {
        for (j = 6; j <= 80; j++) //������ұ߿�||
        {
            gotoxy(j, i);
            if (i == 3 || i == 28) printf("=");
            else if (j == 6 || j == 80) printf("||");
        }
    }
    color(3);
    gotoxy(20,5);
    printf("1. W,A,S,D �ֱ���Ʒɻ������������ƶ�");
    color(10);
    gotoxy(20,8);
    printf("2. ���ո����ӵ������ел����ɵõ�һ��");
    color(14);
    gotoxy(20,11);
    printf("3.�����л��ӵ�����");
    color(11);
    gotoxy(20,14);
    printf("4. ESC ���˳���Ϸ");
    color(4);
    gotoxy(20,17);
    printf("5. �����죡����");
    color(7);
    gotoxy(20,20);
    printf("/*****�������������ҳ��*****/");
    _getch();        //�����������������
    system("cls");
    welcometogame();
}

void scoreandtips()//��Ϸ�����ʾ
{
    gotoxy(50,8);
    color(14);
    printf("��Ϸ�÷֣�%d ",score);
    gotoxy(50,10);
    printf("��W A S D �ֱ���Ʒɻ����ƶ�");
    gotoxy(50,12);
    printf("���¿ո����Ϊ�����ڵ�");
    gotoxy(50,14);
    printf("@ �����Ӿ��ǵ��˵ķɻ�");
}


void HideCursor() // �������ع��
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; // �ڶ���ֵΪ0��ʾ���ع��
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


void startup()   //���ݳ�ʼ��
{
    high=20;   //������Ϸ����ĸ߶�
    width=40;   //��Ϸ����Ŀ��

    position_x=high-3;  //����ɻ��ĳ�ʼλ��
    position_y=width/2;

    bullet_x=0;
    bullet_y=position_y;

    enemy_x=0;
    enemy_y=position_y;

    score=0;

    flag=0;    //�ɻ����

    HideCursor();
}

void show()    //��ʾ����
{

    int i,j,k;
    for(i=0;i<high;i++)
    {
        for(j=0;j<width;j++)
        {
            if(flag)
                break;
            else if((i==position_x)&&(j==position_y)) //�ɻ�����
            {
                printf("^");
            }
            else if((i==enemy_x)&&(j==enemy_y))  //�л�����
                printf("@");
            else if((i==bullet_x)&&(j==bullet_y))  //�ӵ�����
                printf("|");
            else if ((j==width-1)||(i==high-1)||(j==0)||(i==0))  //��ӡ�߽�
                printf("-");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    if((position_x==enemy_x)&&(position_y==enemy_y))
    {

        flag=1;   //�ɻ�ײ�� ��Ϸ����
        system("cls");
        printf("��Ϸ����!!!\n");

    }
    else
    {
        printf("���� %d",score);
    }
    /** _getch();        //�����������������
      system("cls");
      welcometogame();
   */

}

void endgame()
{
    int k,f;
    system("cls");
    printf("����1����һ�Σ�����2�������˵�������3�˳���Ϸ");
    scanf("%d",&k);
    system("cls");
    switch(k)
    {
        case 1:
            printf("��������Ϸ");
            system("cls");
            startup();   // ���ݳ�ʼ��
            show();
            break;
        case 2:
            printf("�������˵�");
            system("cls");
            welcometogame();
            startup();
            break;
        case 3:printf("�˳��ɹ�");
            exit(0);
            break;
        default:
            color(12);
            gotoxy(40,28);
            system("cls");
            printf("�������,����������ص����˵�");
            _getch();  //���������
            welcometogame();
            startup();
            system("cls");  //����
    }
}


void withoutInpute()   //���û������޹�
{
    if(bullet_x>0)    //�ӵ�����Ч��
        bullet_x--;
    if((bullet_x==enemy_x)&&(bullet_y==enemy_y)) //�ӵ����ел�
    {
        score++;
        bullet_x=-1;
        enemy_x=1;
        enemy_y=2+rand()%width-2;
    }


    static int speed;
    if(speed<30)   //�����л��ٶȣ���Ӱ��ɻ����ӵ��ٶ�
        speed++;
    if(speed==30)
    {
        if(enemy_x<high)
            enemy_x++;
        else
        {
            enemy_x=0;
            enemy_y=2+rand()%width-2;
        }
        speed=0;
    }




}
void withInpute()   //���û������й�
{
    char input;
    if(kbhit())     //���Ʒɻ�����
    {
        input=getch();
        if((input=='w')&&position_x>1)
            position_x--;
        if((input=='s')&&position_x<high-2)
            position_x++;
        if((input=='a')&&position_y>1)
            position_y--;
        if((input=='d')&&position_y<width-2)
            position_y++;
        if(input==' ')
        {
            bullet_x=position_x-1;
            bullet_y=position_y;
        }
    }
}

int main()
{
    system("mode con cols=100 lines=30");  //���ÿ���̨�Ŀ��
    welcometogame();
    startup();   // ���ݳ�ʼ��
    //explation();
    while(1)   // ��Ϸѭ��ִ��
    {
        gotoxy(0,0);
        show();   // ��ʾ����
        scoreandtips();
        if(flag == 1)
        {
            endgame();
        }
        withoutInpute(); // ���û������޹صĸ���
        withInpute();  // ���û������йصĸ���
    }
    return 0;
}

int add() {
    printf("a");
}

