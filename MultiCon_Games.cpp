#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <fstream>

#define MAXSNAKESIZE 100
#define MAXFRAMEX 119
#define MAXFRAMEY 29

#define dinoPos 2
#define hurdlePos 74

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define Enemy_DIF 45

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int dinoY;
int speed = 40;
int gameover = 0;

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char bird[3][5] = { ' ',' ','+',' ',' ',
					'|','+','+','+','|',
					'+','+','+','+','+' };

int birdPos = WIN_WIDTH/2;
int score = 0;
int bullets[20][4];
int bulletsLife[20];
int bIndex = 0;

void setcursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if(size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void gameover1(){
    system("cls");
    cout<<endl;
    cout<<"\t\t\t\t##############################"<<endl;
    cout<<"\t\t\t\t#--**-- Game Over --**--#"<<endl;
    cout<<"\t\t\t\t##############################"<<endl<<endl;
    cout<<"\t\t\t\t Developed By:"<<endl;
    cout<<"\t\t\t\t --------------------"<<endl;
    cout<<"\t\t\t\t Bayzid Simon Sarkar"<<endl<<endl<<endl;
    cout<<"\t\t\t\t Press any key to go back to game menu."<<endl<<endl;
    getch();
}

void gameover2(){
    system("cls");
    cout << endl;
    cout << "\t\t\t\t------------------------------" << endl;
    cout << "\t\t\t\t|-@@@@- Game Over -@@@@-|" << endl;
    cout << "\t\t\t\t------------------------------" << endl << endl;
    cout << "\t\t\t\t\tDeveloped By:" << endl;
    cout << "\t\t\t\t\t----------------" << endl;
    cout << "\t\t\t\t\tBayzid Simon Sarkar" << endl << endl << endl;
    cout << "\t\t\t\tPress any key to go back to game menu." << endl << endl;
    getch();
}

void gameover3(){
    system("cls");
    cout << endl;
    cout << "\t\t\t\t------------------------------" << endl;
    cout << "\t\t\t\t|-@@@@- Game Over -@@@@-|" << endl;
    cout << "\t\t\t\t------------------------------" << endl << endl;
    cout << "\t\t\t\t\tDeveloped By:" << endl;
    cout << "\t\t\t\t\t----------------" << endl;
    cout << "\t\t\t\t\tBayzid Simon Sarkar" << endl << endl << endl;
    cout << "\t\t\t\tPress any key to go back to game menu." << endl << endl;
    getch();
}

void gameover4(){
    system("cls");
    cout << endl;
    cout << "\t\t\t\t------------------------------" << endl;
    cout << "\t\t\t\t|-@@@@- Game Over -@@@@-|" << endl;
    cout << "\t\t\t\t------------------------------" << endl << endl;
    cout << "\t\t\t\t\tDeveloped By:" << endl;
    cout << "\t\t\t\t\t----------------" << endl;
    cout << "\t\t\t\t\tBayzid Simon Sarkar" << endl << endl << endl;
    cout << "\t\t\t\tPress any key to go back to game menu." << endl << endl;
    getch();
}

void gameover5(){
    system("cls");
    cout << endl;
    cout << "\t\t\t\t------------------------------" << endl;
    cout << "\t\t\t\t|-@@@@- Game Over -@@@@-|" << endl;
    cout << "\t\t\t\t------------------------------" << endl << endl;
    cout << "\t\t\t\t\tDeveloped By:" << endl;
    cout << "\t\t\t\t\t----------------" << endl;
    cout << "\t\t\t\t\tBayzid Simon Sarkar" << endl << endl << endl;
    cout << "\t\t\t\tPress any key to go back to game menu." << endl << endl;
    getch();
}

void instructions1(){
    system("cls");
    cout<<"\t\t\t\t Instructions:";
    cout<<"\n\t\t\t\t-------------------------------";
    cout<<"\n\t\t\t\tAvoid Cars by moving left or right.";
    cout<<"\n\n\t\t\t\tPress 'A' to move left";
    cout<<"\n\t\t\t\tPress 'D' to move right";
    cout<<"\n\t\t\t\tPress 'Escape' to exit";
    cout<<"\n\n\t\t\t\tPress any key to go back to game menu";
    getch();
}

void instructions3(){
    system("cls");
    cout<<"\t\t\t\t Instructions:";
    cout<<"\n\t\t\t\t------------------------------";
    cout<<"\n\t\t\t\tPress spacebar to make bird fly";
    cout<<"\n\n\t\t\t\tPress any key to go back to game menu";
    getch();
}


void instructions4(){
    system("cls");
    cout<<"\t\t\t\t Instructions:";
    cout<<"\n\t\t\t\t------------------------------";
    cout<<"\n\t\t\t\tPress spacebar to make bird fly";
    cout<<"\n\n\t\t\t\tPress any key to go back to game menu";
    getch();
}


void instructions5(){
    system("cls");
    cout<<"\t\t\t\t Instructions:";
    cout<<"\n\t\t\t\t------------------------------";
    cout<<"\n\t\t\t\t1. Avoid hurdles by jumping.";
    cout<<"\n\t\t\t\t2. Press 'Spacebar' to jump.";
    cout<<"\n\t\t\t\t3. Press 'P' to pause game.";
    cout<<"\n\t\t\t\t4. Press 'Escape' to exit from game.";
    cout<<"\n\n\t\t\t\tPress any key to go back to game menu";
    getch();
}

void drawHurdle() {
    static int plantX = 0;
    static int score = 0;
    if (plantX == 56 && dinoY < 4) {
        score = 0;
        speed = 40;
        gotoxy(47, 8); cout << "Game Over" << endl << endl;
        cout << "\t\t\t\t\t Developed By:" << endl;
        cout << "\t\t\t\t\t -------------------" << endl;
        cout << "\t\t\t\t\t Bayzid Simon Sarkar" << endl;
        cout << "\t\t\t\t\t Morshada Alam Maisha" << endl;
        cout << "\t\t\t\t\t Shashwati Paul Progga" << endl << endl;
        cout << "\t\t\t Press any key to go back to game menu";
        getch();
        //gameover5 = 1;
    }
}



int loggedin()
{
    system("cls");
    string username, password, un, pw;

    cout << "\n\n\t\t\t\tEnter Username :";
    cin >> username;
    cout << "\t\t\t\tEnter Password :";
    cin >> password;

    ifstream read;

    read.open("database.txt");
    getline(read, un);
    getline(read, pw);
    read.close();

    if (un == username && pw == password)
    {
            return 1;
    }
    else
    {
        return 0;
    }
    cout << "\n\t\t\tPlease Wait..........Loading\n\n" << endl << endl;
    for (int i = 0; i < 120; i++) {
        Sleep(3);
        printf("%c", 219);
    }
printf("\n\n\t\t\tSuccessfully loaded");
cout << "\n\n\t\t\tPress Enter to Exit\n";
}


//Car Game Logic

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

char car[4][4] = { ' ','*','*',' ',
					'*','*','*','*',
					' ','*','*',' ',
					'*','*','*','*'};

int carPos = WIN_WIDTH/2;

void drawBorder(){
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j,i); cout<<"�";
			gotoxy(WIN_WIDTH-j,i); cout<<"�";
		}
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"�";
	}
}
void genEnemy(int ind){
	enemyX[ind] = 17 + rand()%(33);
}
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<"****";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ** ";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"****";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ** ";
	}
}
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    ";
	}
}
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 1;
	genEnemy(ind);
}

void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<car[i][j];
		}
	}
}
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<" ";
		}
	}
}

int collision(){
	if( enemyY[0]+4 >= 23 ){
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
			return 1;
		}
	}
	return 0;
}

void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void play1(){
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;

	system("cls");
	drawBorder();
	updateScore();
	genEnemy(0);
	genEnemy(1);

	gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";

	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";

	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' ){
				if( carPos < 50 )
					carPos += 4;
			}
			if(ch==27){
				break;
			}
		}

		drawCar();
		drawEnemy(0);
		drawEnemy(1);
		if( collision() == 1  ){
			gameover1();
			return;
		}
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);

		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;

		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;

		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;

		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

//Snake Game Logic

class Point{
	private:
		int x;
		int y;
	public:
		Point(){
			x = y = 10;
		}
		Point(int x, int y){
			this -> x = x;
			this -> y = y;
		}
		void SetPoint(int x, int y){
			this -> x = x;
			this -> y = y;
		}
		int GetX(){
			return x;
		}
		int GetY(){
			return y;
		}
		void MoveUp(){
			y--;
			if( y < 0 )
				y = MAXFRAMEY;
		}
		void MoveDown(){
			y++;
			if( y > MAXFRAMEY )
				y = 0;
		}
		void MoveLeft(){
			x--;
			if( x < 0 )
				x = MAXFRAMEX;
		}
		void MoveRight(){
			x++;
			if( x > MAXFRAMEX )
				x = 0;
		}
		void Draw(char ch='O'){
			gotoxy(x,y);
			cout<<ch;
		}
		void Erase(){
			gotoxy(x,y);
			cout<<" ";
		}
		void CopyPos(Point * p){
			p->x = x;
			p->y = y;
		}
		int IsEqual(Point * p){
			if( p->x == x && p->y ==y )
				return 1;
			return 0;
		}
		void Debug(){
			cout<<"("<<x<<","<<y<<") ";
		}
};

class Snake{
	private:
		Point * cell[MAXSNAKESIZE]; // array of points to represent snake
		int size; // current size of snake
		char dir; // current direction of snake
		Point fruit;
		int state; // bool representing state of snake i.e. living, dead
		int started;
		int blink; // fruit blink
	public:
		Snake(){
			size = 1; // default size
			cell[0] = new Point(20,20); // 20,20 is default position
			for( int i=1; i<MAXSNAKESIZE; i++){
				cell[i] = NULL;
			}
			fruit.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY);
			state = 0;
			started = 0;
		}
		void AddCell(int x, int y){
			cell[size++] = new Point(x,y);
		}
		void TurnUp(){
			if( dir!='s' )
			dir = 'w'; // w is control key for turning upward
		}
		void TurnDown(){
			if( dir!='w' )
			dir = 's'; // w is control key for turning downward
		}
		void TurnLeft(){
			if( dir!='d' )
			dir = 'a'; // w is control key for turning left
		}
		void TurnRight(){
			if( dir!='a' )
			dir = 'd'; // w is control key for turning right
		}
		void WelcomeScreen(){
			SetConsoleTextAttribute(console,15);
			cout<<"\n            /^\\/^\\                                             ";
			cout<<"\n          _|__|  O|                                              ";
			cout<<"\n \\/     /~     \\_/ \\                                          ";
			cout<<"\n  \\____|__________/  \\                                         ";
			cout<<"\n         \\_______      \\                                       ";
			cout<<"\n                 `\\     \\                 \\                   ";
			cout<<"\n                   |     |                  \\                   ";
			cout<<"\n                  /      /                    \\                 ";
			cout<<"\n                 /     /                       \\\\              ";
			cout<<"\n               /      /                         \\ \\            ";
			cout<<"\n              /     /                            \\  \\          ";
			cout<<"\n            /     /             _----_            \\   \\        ";
			cout<<"\n           /     /           _-~      ~-_         |   |          ";
			cout<<"\n          (      (        _-~    _--_    ~-_     _/   |          ";
			cout<<"\n           \\      ~-____-~    _-~    ~-_    ~-_-~    /          ";
			cout<<"\n             ~-_           _-~          ~-_       _-~   - jurcy -";
			cout<<"\n                ~--______-~                ~-___-~               ";
		}
		void Move(){
			// Clear screen
			system("cls");

			if( state == 0 ){
				if( !started ){
					WelcomeScreen();
					cout<<"\n\nPress any key to start";
					getch();
					started = 1;
					state = 1;
				}else{
					cout<<"\nGame Over";
					cout<<"\nPress any key to start";
					getch();
					state = 1;
					size = 1;
				}
			}

			// making snake body follow its head
			for(int i=size-1; i>0; i--){
				cell[i-1]->CopyPos(cell[i]);
			}

			// turning snake's head
			switch(dir){
				case 'w':
					cell[0]->MoveUp();
					break;
				case 's':
					cell[0]->MoveDown();
					break;
				case 'a':
					cell[0]->MoveLeft();
					break;
				case 'd':
					cell[0]->MoveRight();
					break;
			}

			if( SelfCollision() )
				state = 0;

			// Collision with fruit
			if( fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()){
				AddCell(0,0);
				fruit.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY);
			}

			//drawing snake
			for(int i=0; i<size; i++)
				cell[i]->Draw();

			SetConsoleTextAttribute(console,242);
			if( !blink )
				fruit.Draw('#');
			blink = !blink;
			SetConsoleTextAttribute(console,252);

			//Debug();

			Sleep(100);
		}
		int SelfCollision(){
			for(int i=1; i<size; i++)
				if( cell[0]->IsEqual(cell[i]) )
					return 1;
			return 0;
		}
		void Debug(){
			for( int i=0; i<size; i++){
				cell[i]->Debug();
			}
		}
};

void play2(){
//random no generation
	setcursor(0,0);
	srand( (unsigned)time(NULL));

	// Testing snake
	Snake snake;
	char op = 'l';
	do{
		if(kbhit()){
			op = getch();
		}
		switch(op){
			case 'w':
			case 'W':
				snake.TurnUp();
				break;

			case 's':
			case 'S':
				snake.TurnDown();
				break;

			case 'a':
			case 'A':
				snake.TurnLeft();
				break;

			case 'd':
			case 'D':
				snake.TurnRight();
				break;
		}
		snake.Move();
	}while(op != 'e');
	//return 0;
}

//Flappy Bird Game Logic


#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45


int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird1[2][6] = { '/','-','-','o','\\',' ',
					'|','_','_','_',' ','>' };
int birdPos1 = 6;

void drawBorder3(){

	for(int i=0; i<SCREEN_WIDTH; i++){
		gotoxy(i,0); cout<<"�";
		gotoxy(i,SCREEN_HEIGHT); cout<<"�";
	}

	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout<<"�";
		gotoxy(SCREEN_WIDTH,i); cout<<"�";
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(WIN_WIDTH,i); cout<<"�";
	}
}

void genPipe(int ind){
	gapPos[ind] = 3 + rand()%14;
}

void drawPipe(int ind){
	if( pipeFlag[ind] == true ){
		for(int i=0; i<gapPos[ind]; i++){
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"***";
		}
		for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"***";
		}
	}
}

void erasePipe(int ind){
	if( pipeFlag[ind] == true ){
		for(int i=0; i<gapPos[ind]; i++){
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   ";
		}
		for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   ";
		}
	}
}

void drawBird(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<<bird[i][j];
		}
	}
}
void eraseBird(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<<" ";
		}
	}
}

int collision3(){
	if( pipePos[0] >= 61  ){
		if( birdPos<gapPos[0] || birdPos >gapPos[0]+GAP_SIZE ){
//			cout<< " HIT ";
//			getch();
			return 1;
		}
	}
	return 0;
}
void debug(){
//	gotoxy(SCREEN_WIDTH + 3, 4); cout<<"Pipe Pos: "<<pipePos[0];

}

void updateScore3(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void play3(){

	birdPos = 6;
	score = 0;
	pipeFlag[0] = 1;
	pipeFlag[1] = 0;
	pipePos[0] = pipePos[1] = 4;

	system("cls");
	drawBorder();
	genPipe(0);
	updateScore();

	gotoxy(WIN_WIDTH + 5, 2);cout<<"FLAPPY BIRD";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" Spacebar = jump";

	gotoxy(10, 5);cout<<"Press any key to start";
	getch();
	gotoxy(10, 5);cout<<"                      ";

	while(1){

		if(kbhit()){
			char ch = getch();
			if(ch==32){
				if( birdPos > 3 )
					birdPos-=3;
			}
			if(ch==27){
				break;
			}
		}

		drawBird();
		drawPipe(0);
		drawPipe(1);
		debug();
		if( collision() == 1 ){
			gameover3();
			return;
		}
		Sleep(100);
		eraseBird();
		erasePipe(0);
		erasePipe(1);
		birdPos += 1;

		if( birdPos > SCREEN_HEIGHT - 2 ){
			gameover3();
			return;
		}

		if( pipeFlag[0] == 1 )
			pipePos[0] += 2;

		if( pipeFlag[1] == 1 )
			pipePos[1] += 2;

		if( pipePos[0] >= 40 && pipePos[0] < 42 ){
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}
		if( pipePos[0] > 68 ){
			score++;
			updateScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}

	}

}

void drawEnemy1(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<".**.";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"****";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"****";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<".**.";

	}
}

void eraseEnemy1(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    ";
	}
}
void resetEnemy1(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 4;
	genEnemy(ind);
}
void genBullet(){
	bullets[bIndex][0] = 22;
	bullets[bIndex][1] = birdPos;
	bullets[bIndex][2] = 22;
	bullets[bIndex][3] = birdPos+4;
	bIndex++;
	if( bIndex == 20)
		bIndex = 0;
}
void moveBullet(){
	for(int i=0; i<20; i++){
		if( bullets[i][0] > 2 )
			bullets[i][0]--;
		else
			bullets[i][0] = 0;

		if( bullets[i][2] > 2 )
			bullets[i][2]--;
		else
			bullets[i][2] = 0;
	}
}
void drawBullets(){
	for(int i=0; i<20; i++){
		if( bullets[i][0] > 1){
			gotoxy(bullets[i][1],bullets[i][0]); cout<<".";
			gotoxy(bullets[i][3],bullets[i][2]); cout<<".";
		}
	}
}
void eraseBullets(){
	for(int i=0; i<20; i++){
		if( bullets[i][0] >= 1 ){
			gotoxy(bullets[i][1],bullets[i][0]); cout<<" ";
			gotoxy(bullets[i][3],bullets[i][2]); cout<<" ";
		}
	}
}
void eraseBullet(int i){
	gotoxy(bullets[i][1],bullets[i][0]); cout<<" ";
	gotoxy(bullets[i][3],bullets[i][2]); cout<<" ";
}
void drawBird1(){
	for(int i=0; i<3; i++){
		for(int j=0; j<5; j++){
			gotoxy(j+birdPos, i+22); cout<<bird[i][j];
		}
	}
}
void eraseBird1(){
	for(int i=0; i<3; i++){
		for(int j=0; j<5; j++){
			gotoxy(j+birdPos, i+22); cout<<" ";
		}
	}
}

int collision1(){
	if( enemyY[0]+4 >= 23 ){
		if( enemyX[0] + 4 - birdPos >= 0 && enemyX[0] + 4 - birdPos < 8  ){
			return 1;
		}
	}
	return 0;
}
int bulletHit(){
	for(int i=0; i<20; i++){
		for(int j=0; j<4; j+=2){
			if( bullets[i][j] != 0 ){
				if( bullets[i][j] >= enemyY[0] && bullets[i][j] <= enemyY[0]+4 ){
					if( bullets[i][j+1] >= enemyX[0] && bullets[i][j+1] <= enemyX[0]+4 ){
						eraseBullet(i);
						bullets[i][j] = 0;
						resetEnemy(0);
						return 1;
					}
				}
				if( bullets[i][j] >= enemyY[1] && bullets[i][j] <= enemyY[1]+4 ){
					if( bullets[i][j+1] >= enemyX[1] && bullets[i][j+1] <= enemyX[1]+4 ){
						eraseBullet(i);
						resetEnemy(1);
						bullets[i][j] = 0;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

void updateScore1(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void instructions(){

	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Press spacebar to make bird fly";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void play4(){

	birdPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 1;
	enemyY[0] = enemyY[1] = 4;

	for(int i=0; i<20; i++){
		bullets[i][0] = bullets[i][1] = 0;
	}

	system("cls");
	drawBorder();
	genEnemy(0);
	genEnemy(1);
	updateScore();

	gotoxy(WIN_WIDTH + 5, 2);cout<<"Space Shooter";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";
	gotoxy(WIN_WIDTH + 2, 16);cout<<" Spacebar = Shoot";

	gotoxy(10, 5);cout<<"Press any key to start";
	getch();
	gotoxy(10, 5);cout<<"                      ";

	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( birdPos > 2 )
					birdPos -= 2;
			}
			if( ch=='d' || ch=='D' ){
				if( birdPos < WIN_WIDTH-7 )
					birdPos += 2;
			}
			if(ch==32){
				genBullet();
			}
			if(ch==27){
				break;
			}
		}

		drawBird();
		drawEnemy(0);
		drawEnemy(1);
		drawBullets();
		if( collision() == 1  ){
			gameover4();
			return;
		}
		if(  bulletHit() == 1 ){
			score++;
			updateScore();
		}
		Sleep(200);
		eraseBird();
		eraseEnemy(0);
		eraseEnemy(1);
		eraseBullets();
		moveBullet();

		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;

		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;

		if( enemyY[0] > SCREEN_HEIGHT-5 ){
			resetEnemy(0);
		}
		if( enemyY[1] > SCREEN_HEIGHT-5 ){
			resetEnemy(1);
		}
	}
}

#define dinoPos 2
#define hurdlePos 74

void init() {
    system("cls");
    gameover = 0;
    gotoxy(3, 2); cout<<"SCORE : ";
    for (int i = 0; i < 79; i++){
    	gotoxy(1+i, 1); cout<<"�";
    	gotoxy(1+i, 25); cout<<"�";
	}
}

void moveDino(int jump = 0) {
    static int foot = 0;

    if (jump == 0)
        dinoY = 0;
    else if (jump == 2)
        dinoY--;
    else dinoY++;

    gotoxy(dinoPos, 15 - dinoY);cout<<"                 ";
    gotoxy(dinoPos, 16 - dinoY);cout<<"         ��������";
    gotoxy(dinoPos, 17 - dinoY);cout<<"         ��������";
    gotoxy(dinoPos, 18 - dinoY);cout<<"         ��������";
    gotoxy(dinoPos, 19 - dinoY);cout<<" �      �������� ";
    gotoxy(dinoPos, 20 - dinoY);cout<<" ���  ���������� ";
    gotoxy(dinoPos, 21 - dinoY);cout<<" ������������  � ";
    gotoxy(dinoPos, 22 - dinoY);cout<<"   ���������     ";
    gotoxy(dinoPos, 23 - dinoY);

    if (jump == 1 || jump == 2) {
        cout<<"    ��� ��       ";
        gotoxy(2, 24 - dinoY);
        cout<<"    ��   ��      ";
    }
	else if (foot == 0) {
        cout<<"    ����  ���    ";
        gotoxy(2, 24 - dinoY);
        cout<<"      ��         ";
        foot = !foot;
    }
	else if (foot == 1) {
        cout<<"     ��� ��      ";
        gotoxy(2, 24 - dinoY);
        cout<<"          ��     ";
        foot = !foot;
    }

    gotoxy(2, 25 - dinoY);
    if (jump == 0) {
        cout<<"�����������������";
    } else {
        cout<<"                ";
    }
    Sleep(speed);
}
void drawHurdle5() {
    static int plantX = 0;
	static int score = 0;
    if (plantX == 56 && dinoY < 4) {
        score = 0;
        speed = 40;
        gotoxy(36, 8);cout<<"Game Over";
        getch();
        gameover = 1;
    }

    gotoxy(hurdlePos - plantX, 20);cout<<"| | ";
    gotoxy(hurdlePos - plantX, 21);cout<<"| | ";
    gotoxy(hurdlePos - plantX, 22);cout<<"|_| ";
    gotoxy(hurdlePos - plantX, 23);cout<<" |  ";
    gotoxy(hurdlePos - plantX, 24);cout<<" |  ";

    plantX++;

    if (plantX == 73) {
        plantX = 0;
        score++;
        gotoxy(11, 2);cout<<"     ";
        gotoxy(11, 2);cout<<score;
        if (speed > 20)
            speed--;
    }
}
void play5(){
	system("cls");
    char ch;
    int i;
	init();
    while (true) {
        while (!kbhit()) {
            if( gameover==1 ){
            	return;
			}
			moveDino();
            drawHurdle();
        }
        ch = getch();
        if (ch == 32) {
        	i = 0;
            while( i < 12) {
                moveDino(1);
                drawHurdle();
                i++;
            }
            while(i > 0) {
                moveDino(2);
                drawHurdle();
                i--;
        	}
        }
		else if (ch == 'p'||ch=='P')
           getch();
		else if (ch == 27)
           break;
    }
}


int mainmenu()
{
    system("Color F3");

    int game;
    system("cls");
    cout<<"\t\t\t##############################"<<endl;
    cout<<"\t\t\t#"<<endl;
    cout<<"\t\t\t#--**-- Welcome to Con-Games --**--#"<<endl;
    cout<<"\t\t\t#"<<endl;
    cout<<"\t\t\t##############################"<<endl<<endl;

    cout<<"\t\t\t1.Car Game"<<endl;
    cout<<"\t\t\t2.Snake"<<endl;
    cout<<"\t\t\t3.Flappy Bird"<<endl;
    cout<<"\t\t\t4.Space Shooter"<<endl;
    cout<<"\t\t\t5.Dino Run"<<endl;
    cout<<"\t\t\t6.Quit Games"<<endl;
    cout<<"\t\t\t7. Developers Info."<<endl<<endl;

    cout<<"\n\t\t\tSelect Option & Press Enter to Proceed:";
    cin>>game;

    cout<<"\n\t\t\tPlease Wait...........Loading\n\n"<<endl<<endl;
    for(int i=0; i<120; i++)
    {
        Sleep(3);
        printf("%c",219);
    }

    printf("\n\n\t\t\tSuccessfully loaded");
    cout<<"\n\n\t\t\tPress Enter to Exit\n\n";



    if (game == 1) {
        setcursor(0, 0);
        srand((unsigned)time(NULL));
        do {
            system("cls");
            cout << "\t\t\t----------------------------\n";
            cout << "\t\t\t|         Car Game         |\n";
            cout << "\t\t\t----------------------------\n";
            cout << "\t\t\t1. Start Game\n";
            cout << "\t\t\t2. Instructions\n";
            cout << "\t\t\t3. Main Menu\n";
            cout << "\t\t\t4. Quit\n";
            cout << "\t\t\tSelect option: ";
            char op = getche();

            if (op == '1') play1();
            else if (op == '2') instructions1();
            else if (op == '3') mainmenu();
            else if (op == '4') exit(0);
        } while (1);
    }

    else if(game == 2)
    {
    system("Color A4");

    //random no generation
    setcursor(0,0);
    srand((unsigned)time(NULL));
    do {
            system("cls");
            cout << "\t\t\t----------------------------\n";
            cout << "\t\t\t|         Snake Game       |\n";
            cout << "\t\t\t----------------------------\n";
            cout << "\t\t\t1. Start Game\n";
            cout << "\t\t\t2. Instructions\n";
            cout << "\t\t\t3. Main Menu\n";
            cout << "\t\t\t4. Quit\n";
            cout << "\t\t\tSelect option: ";
            char op = getche();

            if (op == '1') play2();
            else if (op == '2') instructions1();
            else if (op == '3') mainmenu();
            else if (op == '4') exit(0);
        } while (1);
    }
    else if (game == 3) {
        system("Color 9F");
        setcursor(0, 0);
        srand((unsigned)time(NULL));
        do {
            system("cls");
            cout << "\t\t\t----------------------------\n";
            cout << "\t\t\t|        Flappy Bird        |\n";
            cout << "\t\t\t----------------------------\n";
            cout << "\t\t\t1. Start Game\n";
            cout << "\t\t\t2. Instructions\n";
            cout << "\t\t\t3. Main Menu\n";
            cout << "\t\t\t4. Quit\n";
            cout << "\t\t\tSelect option: ";
            char op = getche();
            if (op == '1') play3();
            else if (op == '2') instructions3();
            else if (op == '3') mainmenu();
            else if (op == '4') exit(0);
        } while (1);
    }

    else if (game == 4) {
        system("Color E4");
        do {
            system("cls");
            cout << "\t\t\t----------------------------\n";
            cout << "\t\t\t|      Space Shooter       |\n";
            cout << "\t\t\t----------------------------\n";
            cout << "\t\t\t1. Start Game\n";
            cout << "\t\t\t2. Instructions\n";
            cout << "\t\t\t3. Main Menu\n";
            cout << "\t\t\t4. Quit\n";
            cout << "\t\t\tSelect option: ";
            char op = getche();
            if (op == '1') play4();
            else if (op == '2') instructions4();
            else if (op == '3') mainmenu();
            else if (op == '4') exit(0);
        } while (1);
    }

    else if (game == 5) {
        system("Color E4");
        do {
            system("cls");
            cout << "\t\t\t----------------------------\n";
            cout << "\t\t\t|         DINO RUN         |\n";
            cout << "\t\t\t----------------------------\n";
            cout << "\t\t\t1. Start Game\n";
            cout << "\t\t\t2. Instructions\n";
            cout << "\t\t\t3. Main Menu\n";
            cout << "\t\t\t4. Quit\n";
            cout << "\t\t\tSelect option: ";
            char op = getche();
            if (op == '1') play5();
            else if (op == '2') instructions5();
            else if (op == '3') mainmenu();
            else if (op == '4') exit(0);
        } while (1);
    }

    else if (game == 6) {
        exit(0);
    }

    else if (game == 7) {
        system("cls");
        cout << "\n\t\t\t*******************************\n";
        cout << "\t\t\t|      Developed By:       |\n";
        cout << "\t\t\t| Bayzid Simon Sarkar     |\n";
        cout << "\t\t\t*******************************\n";
        cout << "\t\t\tPress any key to go back to main menu.";
        getch();
        mainmenu();
    }
    else {
        system("cls");
        mainmenu();
    }
    return 0;
}






int main()
{
    system("color F4");
    system("cls");
    int cho;

    cout << " \t\t\t\t####################################" << endl;
    cout << " \t\t\t\t#                                  #" << endl;
    cout << " \t\t\t\t#--**-- Welcome to Con-Games --**--#" << endl;
    cout << " \t\t\t\t#                                  #" << endl;
    cout << " \t\t\t\t####################################" << endl << endl;
    cout << " \t\t\t\t1. Register. (For new user)" << endl;
    cout << " \t\t\t\t2. Log In." << endl;
    cout << " \t\t\t\t3. Exit." << endl;
    cout << " \t\t\t\tSelect option :" << endl;
    cin >> cho;

    cout << "\n\t\t\tPlease Wait..........Loading\n\n" << endl << endl;
    for(int i = 0; i < 120; i++)
    {
        Sleep(3);
        printf("%c", 219);
    }

    printf("\n\n\t\t\tSuccessfully loaded");
    cout << "\n\n\t\t\tPress Enter to Exit\n";

    if (cho == 1)
    {
    system("cls");
    string un, pw;
    cout<<"\n\n\t\t\t\tEnter Username :";
    cin>>un;
    cout<<"\t\t\t\tEnter Password :";
    cin>>pw;
    cout<<"\n\t\t\t\tAccount Created Successfully"<<endl<<endl;

    cout<<"\n\t\t\t\tPlease Wait..........Loading\n\n"<<endl<<endl;
    for(int i=0; i<120; i++)
    {
        Sleep(3);
        printf("%c",219);
    }

    cout<<"\n\n\t\t\t\tPress any key to go back."<<endl<<endl;

    ofstream file;
    file.open("database.txt");
    file<< un << endl << pw ;
    file.close();
    getch();
    main();
    }
    else if(cho == 2)
    {
    bool m = loggedin();

    if(!m)
    {
        cout<<"\n\n\t\t\t\tWrong Information or Unregistered User"<<endl;
        cout<<"\n\t\t\t\tPlease Register first and try again!!!"<<endl<<endl;
        cout<<"\n\t\t\t\tPress any key to try again";
        getch();
        main();
    }
    else
    {
    mainmenu();
    }
    }
    else if (cho == 3)
    {
        exit(0);
    }
    else
    {
        main();
    }
}




