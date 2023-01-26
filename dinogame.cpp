#include<iostream>
#include "Header.h"
using namespace std;
int length = 110;
int m = 0;
long long n = 0;
int randomtree=30;
int numberoftrees = 100;
struct toado {
	int x; int y;
}; 
toado dino; 
toado tree[300];
toado ground0[150], ground1[150], ground2[150];
string figure[6] = {
"           0-0 ",
"         /(\\_/)",
".___.---' /`-' ",
" `-._.  )/,,   ",
"     //        ",
"    ^^         ",
};
string figureTree[6]{
"###",
"###",
"###",
"###",
" # ",
" # ",
};
void drawdino(int a , int b) {
	for (int i = 0; i < 6; i++) {
		gotoXY(a, b);
		cout << figure[i];
		b++;
	}
} 
void iniground() {
	for (int i = 1; i < length; i++) {
		ground0[i].y = 23;
		ground0[i].x = i;
		ground1[i].y = 24;
		ground1[i].x = i;
		ground2[i].y = 25;
		ground2[i].x = i;
	}
}
void randomgr() {
	int a = 1 + rand() % (25);
	switch (a) {
	case 1: cout << "."; break;
	case 2: cout << "o"; break;
	case 3: cout << "'"; break;
	case 4: cout << ","; break;
	default: cout << " ";
	}
}
void drawtree(int a, int b) {
	for (int i = 0; i < 6; i++) {
		gotoXY(a, b); SetColor(10);
	cout << figureTree[i];
	b++;
}
	SetColor(0);
} // draw tree in A(a,b)
void drawground() {
	for (int i = 1; i < length; i++) {
		gotoXY(ground0[i].x, ground0[i].y); cout << "_";
		//gotoXY(ground1[i].x, ground1[i].y); randomgr();
		//gotoXY(ground2[i].x, ground2[i].y); randomgr();
	}
}
void moveground() {
	for (int i = 1; i < length - 1; i++) {
		ground0[i - 1] = ground0[i];
	}
}
void deletetree() {
	for (int i = 0; i < 5; i++) {
		for (int j = 17; j < 22; j++) {
			gotoXY(i, j); cout << " ";
		}
	}
}
void treemove(int i) {
	if (tree[i].x > 0) {
		drawtree(tree[i].x, tree[i].y);
		for (int j = 17; j < 23; j++) {
			gotoXY(tree[i].x + 3, j); cout << " ";
		}
		tree[i].x--;
	}
	else (deletetree());
}
void initree() {
	for (int j = 0; j < 200; j++) {
		tree[j].x = 105; tree[j].y = 17;
	}
}
void treei(int i) {
	if (n == (40 + randomtree * m)) {
		m++; randomtree = 60+(3*m*m) % 20;
	}
	if (m == i) {
		drawtree(tree[m].x, tree[m].y);
		treemove(m);
		drawtree(tree[m-1].x, tree[m-1].y);
		treemove(m-1);
		drawtree(tree[m - 2].x, tree[m - 2].y);
		treemove(m - 2);
	}
}
void deleteleg(int a, int b) {
	for (int i = 0; i < 15; i++) {
		gotoXY(a +i, b +5); cout << " ";
		}
}
void deletehead(int a, int b) {
	for (int i = 0; i < 15; i++) {
		gotoXY(a+i, b ); cout << " ";
	}
}
void jumpdino(char *k) {
	if (_kbhit()) {
		char control = _getch();
		if (control == ' '&&dino.y==17) { *k = 'u'; }
	}
	if (*k == 'u') {
		deleteleg(dino.x, dino.y);
		dino.y--;
		drawdino(dino.x, dino.y);
	}
	if (dino.y == 0) {
		*k = 'd';
	}
	if (*k == 'd' && dino.y != 17) {
		deletehead(dino.x, dino.y);
		dino.y++;
		drawdino(dino.x, dino.y);
	}
}
bool gameover() {
	for (int i = 0; i <= numberoftrees; i++) {
		if ((dino.x + 13 >= tree[i].x) && (dino.x <= tree[i].x + 2)) {
			if (dino.y + 4 >= tree[i].y) {
				return 1;
			}
		}
	}
}
void score1(int *score) {
	for (int i = 0; i <= numberoftrees; i++) {
		if (dino.x + 15 == tree[i].x) {
			(*score)++;
		}
	}
	gotoXY(90, 3);
	cout << "Score: " << *score <<" "<< 60 + (7* m * m*m) % 20;
}
int main() {
	ShowCur(0);
	char k = 'a';
	int score = 0;
	dino.x = 15; dino.y = 17;
	tree[0].x = 105; tree[0].y = 17;
	drawdino(dino.x, dino.y);
	iniground();
	drawground();
	initree();
	while (1) { 
		if (n % 2 == 0) {
			gotoXY(dino.x, dino.y + 5); cout << "    ^^^         ";
		}
		score1(&score);
		drawtree(tree[0].x, tree[0].y);
		treemove(0);
		jumpdino(&k);
		n++;
		if (n == 40) {
			 m=1; 
		}
		if(m==1) {
			drawtree(tree[1].x, tree[1].y);
			treemove(1); 
		}
		for (int i = 2; i <= numberoftrees; i++) {
			treei(i);
		}
		if (gameover()==1) {
			break;
	}
		Sleep(5);
	}
	drawdino(dino.x, dino.y);
	gotoXY(dino.x, dino.y); cout << "           x-x ";
	Sleep(10000);
}