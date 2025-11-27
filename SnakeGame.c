#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>


#define food_char 'o'
#define empty_char ' '
#define snake_char '8'


typedef struct node{
	int data;
	int x;
	int y;
	struct node *next;
	
}node;

int rows,colms;
int score=0;
int gameover=0;
int foodx,foody;
int direction=1;
int fensx,fensy;
int hardmode=0;
int newfens=50;

node *head=NULL;
node *tail=NULL;

void add (int x,int y){
	node *n=malloc(sizeof(node));
	n->x=x;
	n->y=y;
	n->next=head;
	head=n;
	if(tail==NULL){
		tail=n;
	}
}

void rmv(){
	node *temp;
	if(head==tail){
		return;
		
	}
	temp=head;
	while(temp->next!=tail){
		
		temp=temp->next;
		
	}
	free(tail);
	tail=temp;
	tail->next=NULL;
	
}

int snakelocation(int x,int y){
	node *temp=head;
	while(temp!=NULL){
		if(temp->x==x && temp->y==y){
			return 1;
		}
		
		temp=temp->next;
		
	}
	return 0;
	
}
void placefood(){
	do{
		foodx=rand() % colms;
		foody=rand() % rows;
	}
	while(snakelocation(foodx,foody));
}

//hadi lel hard mode:

void placefens(){
	do{
		fensx=rand() % colms;
		fensy=rand() % rows;
	}
	while(snakelocation(fensx,fensy)|| (fensx==foodx && fensy==foody));
}



void keybinds(){
	if(_kbhit()){
		char c= _getch();
		if((c=='w' || c=='W')&&direction!=2){
			direction = 0;
		}
		if((c=='a' || c=='A')&&direction!=1){
			direction = 3;
		}
		if((c=='s' || c=='S')&&direction!=0){
			direction = 2;
		}
		if((c=='d' || c=='D')&&direction!=3){
			direction = 1;
		}
		if(c=='x' || c=='X'){
			gameover=1;
		}
		if(c=='p' || c=='P'){
			system("pause");
		}
		
		
		
	}
	
}
void gamelogic(){
	
	//nbdaw b movment:
	int headx = head->x;
	int heady = head->y;
	
	if(direction==0){
		heady--;
	}
	if(direction==1){
		headx++;
	}
	if(direction==2){
		heady++;
	}
	if(direction==3){
		headx--;
	}
	
	
	//losing case kyn 2:
	
	// 1-border case :
	
	if(headx<0 || headx >=colms || heady<0 || heady >=rows){
		gameover=1;
	}
	
	// 2-self case :
	if(snakelocation(headx,heady)){
		gameover=1;
	}
	
	//hna win ysra illusion t3 movment :
	
	// ndiro head w ida kla n5lo tail ida mklach n7oh :
	
	add(headx,heady);
	
	//+1 ki ykol:
	
	
	if(headx==foodx && heady==foody){
		score+=10;
		placefood();
		if(hardmode==1){
			placefens();
			
		}
		
	}
	else{
		rmv();
	}
	
	//fens f ns trig kol ma yakol ybdl plasto :
	
	if(headx==fensx && heady==fensy){
		gameover=1;
	}

}

void printing(){
	
	int i , y , x; 
	system("cls");
	
	
	printf("\nScore : %d\n",score);
	
	for(i=0;i<colms+2;i++){
		printf("*");
	}
	printf("\n");
	for(y=0;y<rows;y++){
		printf("*");
		for(x=0;x<colms;x++){
			if(snakelocation(x,y)){
				printf("%c",snake_char);
			}
			else if(x==foodx && y==foody){
				printf("%c",food_char);
			}
			else if(hardmode==1 && x==fensx && y==fensy){
				printf("#");
			}
			else{
				printf("%c",empty_char);
			}
			
		}
		printf("*\n");
	}
	for(i=0;i<colms+2;i++){
		printf("*");
	}
	
}



//HADI MAIN GAME :

void SnakeGame(int speed,int fens){
	system("title SnakeGame");
	
	printf("Size of the board 'rows / colms' :");
	scanf("%d %d",&rows,&colms);
	
	int firstx=colms/2;
	int firsty=rows/2;
	hardmode=fens;
	
	srand(time(NULL));
	
	add(firstx,firsty);
	placefood();
	if(hardmode==1){
		placefens();		
	}
	
	
	
	while(gameover==0){
		
		printing();
		keybinds();
		gamelogic();
		Sleep(speed);
		
		
		
	}
	system("color 4");
	printf("\nGameOver ! Your Score is : %d",score);
}


// Snakegame menuu: 

int main(){
    int mod;

    system("cls");
    system("color F");
    printf("=====================================\n");
    printf("            SNAKE GAME MODS          \n");
    printf("=====================================\n");
    printf("  [1] Easy Mode  (slow snake)\n");
    printf("  [2] Hard Mode  (fast snake)\n");
    printf("  [0] Back to Main Menu\n");
    printf("=====================================\n");

    do {
        printf("Choose a mode: ");
        scanf("%d", &mod);
    } while (mod < 0 || mod > 2);

    switch(mod){
        case 1:
            SnakeGame(150,0);  
            break;
        case 2:
            SnakeGame(40,1);    
            break;
        case 0:
            main();
            break;
    }
}







