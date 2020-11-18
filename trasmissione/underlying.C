#include <iostream>
#include <string>
#include <vector>
#include <thread>
 
#define MAX_DEPTH 10
char STATO_BASE[][]= {{ 'O', 'O', 'O', 'B', 'B', 'B', 'O', 'O', 'O'},{ 'O', 'O', 'O', 'O', 'B', 'O', 'O', 'O', 'O'},{ 'O', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'O' }, { 'B', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'B'}, { 'B', 'B', 'W', 'W', 'K', 'W', 'W', 'B', 'B'},{'B', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'B'}, { 'O', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'O' } {'O', 'O', 'O', 'O', 'B', 'O', 'O', 'O', 'O' }, { 'O', 'O', 'O', 'B', 'B', 'B', 'O', 'O', 'O' }}
short int PESISTANDARD[][]={{-1000,7,7,-1000,-1000,-1000,7,7,-1000},{7,6,6,5,-1000,5,6,6,7},{7,6,5,4,3,4,5,6,7},{-1000,5,4,3,2,3,5,6,-1000},{-1000,-1000,3,2,1,2,3,-1000,-1000},{-1000,5,4,3,2,3,5,6,-1000},{7,6,5,4,3,4,5,6,7},{7,6,6,5,-1000,5,6,6,7},{-1000,7,7,-1000,-1000,-1000,7,7,-1000}}
// questo è +o- il template da cui pensavo di partire 
using namespace std;
struct State {
char status[9][9];
short int weight[9][9];/*per il calcolo dell'euristica io farei quanto segue per il bianco è data dalla minima distanza del re dai punti di fuga che sono fissi per il nero io la calcolerei come la minima distanza dai 4punti attorno al re nemico non occupati otremmo ma ritengo che da fare sia troppo complesso quindi ad ogni spostamento del re calcoliamo una griglia di pesi (per il bianco gradiente verso le uscite per il nero gradiente verso il re) e su questa cosa applichiamo minmax se l'idea ti piace ci sarebbe da pensare per come considerare il movimento per le pedine bianche in questa griglia visto che potrebbe far tendere le pedine bianche ad andare nelle uscite la mia idea sarebbe di appioppare alle mosse delle pedine bianche un valore più alto se lo spostamento le porta verso una zona limitrofa al massimo gradiente così da proteggere il re senza impedirne il movimento*/
State(char stato[9][9],short int pesi[9][9]=PESISTANDARD){
for (short int i=0;i<9;++i){
	for(short int j=0;j<9;++i){status[i][j]=stato[i][j];};} 
		status[0][3]='c';status[0][4]='c';status[0][5]='c';status[1][4]='c';status[3][0]='c';status[4][0]='c';
		status[5][0]='c';status[4][1]='c';status[8][3]='c';status[8][4]='c';status[8][5]='c';status[7][4]='c';
		status[3][8]='c';status[4][8]='c';status[5][8]='c';status[4][7]='c';status[4][4]='C';
				};};
class Move{
char begin[2];
char finish[2];
short int euristica;
public:
Moves(char primo[2],char secondo[2],euristica){for (short i=0;i<2;++i){finish[i]=primo[i];begin[i]=secondo[i];};}
char* getmossa(){char* uscita=new char[4];for (short i=0;i<2;++i){uscita[i]=begin[i];uscita[i+2]=finish[i];};}
void seteurist(short int euristica){eurist(euristica);}
};

class Pawn 
{
bool uscita;
bool king;
bool white;
char position[2]; //position[0]=x-axis(using numbers) position[1] y-axis(using letters a,b,c,d,e ecc)
public:/* ho inserito le posizioni come dei char per evitare problemi di conversione successivi se vuoi fare altrimenti dimmi pure */
char* get_position(){return position}
vector<Move> detect_moves(State stato,short int (*funct)(State,char,char),short int & alpha,short int &beta,Pawn king,short int profondita){vector<Move> mosse; 

for (char i=position[0]-1;'0'>i;--i){
	char king_position []=king.get_position()
	if(stato.status[position[1]-'a'][i-'0']!='O'){
		if(uscita or white or stato.status[position[1]-'a'][i-'0']!='c') break;} 
	short int euristica=funct(stato,i,position[1])+white?stato[king_position[0]-'a'][king_position[1]-'0']:stato[king_position[0]-'a'][king_position[1]-'0']?7-stato[king_position[0]-'a'][king_position[1]-'0']:1
	if(white and profondita){
	if(euristica<*alpha)break;
	alpha=euristica;}
	else if(profondita){if(euristica>*beta)break;
	beta=euristica;}
	char partenza[]={position[1],position[0]}
	char arrivo[]={position[1],i}
	
	mosse.pushback(Move(arrivo,partenza,euristica));}


for (char i=position[0]+1;i<'9';++i){

	if(stato.status[position[1]-'a'][i-'0']!='O');
		{if(uscita or white or stato.status[position[1]-'a'][i-'0']!='c') break;} 

	mosse.pushback(Move({(char)position[1],(char)i},{(char)position[1],(char)position[0]}));} 


for (char i=position[1]-1;'a'>i;--i){
	if(stato.status[position[1]-'a'][i-'0']!='O');
		{if(uscita or white or stato.status[position[1]-'a'][i-'0']!='c') break;} 
	mosse.pushback(Move({(char)position[1],'0'+(char)i},{(char)position[1],(char)position[0]}));}

for (char i=position[1]+1;i<''i';++i){
	if(stato.status[position[1]-'a'][i-'0']!='O');
		{if(uscita or white or stato.status[position[1]-'a'][i-'0']!='c') break;} 
	mosse.pushback(Move({(char)position[1],(char)i},{(char)position[1],(char)position[0]}));} 
return mosse;}
void setposition(Move mossa) {
	for(short int=0;i<2;++i)position[i]=mossa.getmossa()[i+2];}

bool checkeaten(State stato,Move mossa){
	char arrivo[2]={mossa.getmossa()[2],mossa.getmossa()[3]}
	for (char a=arrivo[0]-1;a<=arrivo[0]+1;++a){
		for (char b=arrivo[1]-1;b<=arrivo[1]+1;b+2)
			{if(stato.status[a-'0'][b-'a']== white?'B':'W' or stato.status[a-'0'][b-'a']=='C'or stato.status[a-'0'][b-'a']=='c') return true;};}
	return false;}
Pawn(char start[2],bool lineage=false,bool king=false):white(lineage)
{for (short i;i<2;++i)position[i]=start[i];uscita=false;}
;};


char* execution (char** stato){
vector<Pawn> WPawn;
Pawn king;
vector<Pawn> BPawn;
	for (short int i=0;i<9;++i){
		for (short int j=0;j<9;++j) {
			
			if(stato[i][j]!='O')
				{char posizione[2]={i+'a',j+'0'};
				if(stato[i][j]=='W')WPawn.pusback(Pawn(posizione))
				else if(stato[i][j]=='K') king=Pawn(posizione,true,true)
				else BPawn.pushback(Pawn(posizione));};};}
State current(stato);

for (short int i=0;i<=MAX_DEPTH;++i){
	for (auto u:WPawn){u.detect_moves()}

;}
}


