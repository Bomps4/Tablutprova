#include <iostream>
#include <string>
#include <vector>
#include <thread>
#define UNDEX -10000
#define MAX_DEPTH 10
char STATO_BASE[][]= {{ 'O', 'O', 'O', 'B', 'B', 'B', 'O', 'O', 'O'},{ 'O', 'O', 'O', 'O', 'B', 'O', 'O', 'O', 'O'},{ 'O', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'O' }, { 'B', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'B'}, { 'B', 'B', 'W', 'W', 'K', 'W', 'W', 'B', 'B'},{'B', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'B'}, { 'O', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'O' } {'O', 'O', 'O', 'O', 'B', 'O', 'O', 'O', 'O' }, { 'O', 'O', 'O', 'B', 'B', 'B', 'O', 'O', 'O' }}
short int PESISTANDARD[][]={{-1000,7,7,-1000,-1000,-1000,7,7,-1000},{7,6,6,5,-1000,5,6,6,7},{7,6,5,4,3,4,5,6,7},{-1000,5,4,3,2,3,5,6,-1000},{-1000,-1000,3,2,1,2,3,-1000,-1000},{-1000,5,4,3,2,3,5,6,-1000},{7,6,5,4,3,4,5,6,7},{7,6,6,5,-1000,5,6,6,7},{-1000,7,7,-1000,-1000,-1000,7,7,-1000}}
// questo è +o- il template da cui pensavo di partire 
using namespace std;
template<typename T> void secure_swap(vector<T>*a,vector<T>& b){b.swap(*a);delete []a;}
struct State {
char status[9][9];
short int weight[9][9];/*per il calcolo dell'euristica io farei quanto segue per il bianco è data dalla minima distanza del re dai punti di fuga che sono fissi per il nero io la calcolerei come la minima distanza dai 4punti attorno al re nemico non occupati otremmo ma ritengo che da fare sia troppo complesso quindi ad ogni spostamento del re calcoliamo una griglia di pesi (per il bianco gradiente verso le uscite per il nero gradiente verso il re) e su questa cosa applichiamo minmax se l'idea ti piace ci sarebbe da pensare per come considerare il movimento per le pedine bianche in questa griglia visto che potrebbe far tendere le pedine bianche ad andare nelle uscite la mia idea sarebbe di appioppare alle mosse delle pedine bianche un valore più alto se lo spostamento le porta verso una zona limitrofa al massimo gradiente così da proteggere il re senza impedirne il movimento*/
State(char stato[9][9],short int pesi[9][9]=PESISTANDARD){
	for (short int i=0;i<9;++i){
		for(short int j=0;j<9;++i){status[i][j]=stato[i][j];};} 
			status[0][3]='c';status[0][4]='c';status[0][5]='c';status[1][4]='c';status[3][0]='c';status[4][0]='c';
			status[5][0]='c';status[4][1]='c';status[8][3]='c';status[8][4]='c';status[8][5]='c';status[7][4]='c';
			status[3][8]='c';status[4][8]='c';status[5][8]='c';status[4][7]='c';status[4][4]='C';
				};
void move(char* iniziale, char* finale){
if(status[iniziale[1]-'a'][iniziale[0]-'0']=='c'or status[iniziale[1]-'a'][iniziale[0]-'0']=='B')
	status[finale[1]-'a'][finale[0]-'0']='B';
else status[finale[1]-'a'][finale[0]-'0']='W';
if([iniziale[1]-'a'][iniziale[0]-'0']!='c')status[iniziale[1]-'a'][iniziale[0]-'0']='B';
}
};


class Tree{
short int alpha;
short int beta;
short int (*funct)(Status,);
char posizione_re[MAX_DEPTH][2];
short int euristiche;
Status stati[MAX_DEPTH];
vector<Pawn>::iterator iteratori [MAX_DEPTH];
array<vector<Pawn>,MAX_DEPTH> branches;
public:
Pawn deepen(short int depth=0,vector<Pawn> altra_squadra,vector<Pawn> nostra_squadra,short int (*eur_func)(State,char[2])){
	if(depth==0)euristiche=UNDEX;
	static Pawn scelta;
	bool actual_color;
	for(iteratori[depth];iteratori!=breanches[depth].end();iteratori[depth]++)
		{ 	
			actual_color=(*iteratori[depth]).get_lineage()					
			if(depth<MAX_DEPTH-1){
			if((*iteratori[depth]).get_king()){for (short int j=0;j<2;j++){posizione_re[depth+1][j]=i.get_position()[j];};}
			else {for (short int j=0;j<2;j++){posizione_re[depth+1]=posizione_re[depth];}}
			vector<Pawn> futuribili;
			bool precedent_color=(depth==0?altra_squadra[0]:branches[depth-1][0]).get_lineage();
			for (auto i:depth==0?altra_squadra:branches[depth-1]){
				if(euristica!=UNDEX and !precedent_color and alpha>euristica){iteratori[depth-1]++;return deepen(depth-1);}
				if(euristica!=UNDEX and precedent_color and alpha<euristica){iteratori[depth-1]++;return deepen(depth-1);}
				if(i.check_winning(posizione_re[depth])){if(not precedent_color){++iteratori[depth-2];return deepen(depth-2);} return *iteratori[0];}
			
				if(i.eaten(stati[depth])) {if(i.get_king()){++iteratori[depth-2];return deepen(depth-2);} continue;} 

				auto temp=i.detect_moves();
				futuribili.reserve(futuribili.size()+distance((*temp).begin(),(*temp).end()));
				futuribili.insert(futuribili.end(),(*temp).begin(),(*temp).end());
				delete [] temp;
			}
			if(*iteratori[depth])
			stati[depth](*iteratori).get_position()
			branches[depth+1].swap(futuribili);
			iteratori[depth+1]=branches[depth+1].begin();
			if(iteratori[depth]==branches[depth].begin()){
			stati[depth+1]=stati[depth];
			stati[depth+1].move((*iteratori[depth-2]).get_position(),(*iteratori[depth]).get_position())
			}
			else{stati[depth+1]=stati[depth+1].move((*(iteratori[depth]-1)).get_position(),(*iteratori[depth]).get_position())}
			return deepen(depth+1);}
			short int euristica_temp=eur_func(stati[depth])
			if(iteratori[depth]==breanches[depth].begin()){euristiche= euristica_temp;}
			if(actual_color and euristica_temp>alpha and depth!=0){iteratori[depth-1]++;return deepen(depth-1);}
			if(not actual_color and euristica_temp<alpha and depth!=0){iteratori[depth-1]++;return deepen(depth-1);}

			if(actual_color and euristiche>= euristica_temp) {euristiche=euristica_temp;scelta=*iteratori[0];}
			else if(not actual_color and euristiche[depth]<=euristica_temp)euristiche=euristica_temp;scelta=*iteratori[0];}



if(depth!=0){
if(alpha==UNDEX)
	alpha=euristiche;
else if (actual_color and euristiche>=alpha) euristiche=alpha;
else if( !actual_color and euristiche<=alpha )euristiche=alpha;
iteratori[depth-1]++;
return deepen(depth-1);}
return scelta;}
}




class Pawn 
{

unsigned int id:4;
bool king;  
bool white;
char position[2]; //position[0]=x-axis(using numbers) position[1] y-axis(using letters a,b,c,d,e ecc)
public:/* ho inserito le posizioni come dei char per evitare problemi di conversione successivi se vuoi fare altrimenti dimmi pure */
void set_euristica(short int euristic){euristica=euristic;}
bool get_king(){return king;}
bool get_lineage(){return white;}
bool eaten (Status stato){
short int re=0;
for (short int c=0;c<2;++c){
if((stato[position[0]-'a'+c-1][position[1]-'0'+c]==white?'B':'W'or stato[position[0]-'a'+c-1][position[1]-'0'+c]=='c')and (stato[position[0]-'a'-c+1][position[1]-'0'-c]==white?'B':'W' or stato[position[0]-'a'-c+1][position[1]-'0'-c]=='c')){if(stato[position[0]-'a'][position[1]-'0']=='C' and king)++re; else  return true;}//non è stata inserita la condizione re attorno al castello ci sono 3 pedoni nel caso 
;}
return re==2;}
char* get_position(){return position}
bool check_winning (char* king_position){if(white){char vincenti[][2]={"a1","a2","a6","a7","i1","i2","i6","i7","b0","c0","g0","h0","b8","c8","g8","h8"};for(auto u:vincenti){if(u[0]==king_position[0] and u[1]==king_position[1]) return true;};}return false;}//il check per il nero ti sei mosso controlla piuttosto se il re è stato catturato in fin dei conti non ha senso controllare per lui
vector<Pawn>* detect_moves(State stato,short int (*funct)(State,char*,char*),short int & alpha,short int &beta,Pawn king,short int profondita){
non è
	vector<P>* mosse=new vector<Move>[1]; 

for (char i=position[0]-1;'0'>i;--i){
	//char king_position []=king.get_position()
	if((stato[begin[0]-'a'][begin[1]-'0']!='c' and stato[begin[0]-'a'][i-'0']=='c') or stato.status[position[1]-'a'][i-'0']!='O') break;

	//short int euristica=funct(stato,i,position[1])+white?stato[king_position[0]-'a'][king_position[1]-'0']:stato[king_position[0]-'a'][king_position[1]-'0']?7-stato[king_position[0]-'a'][king_position[1]-'0']:1
	
	char partenza[]={begin[1],begin[0]}
	
	char arrivo[]={begin[1],i}
	
	*mosse.pushback(Move(arrivo,partenza,euristica));}


for (char i=position[0]+1;i<'9';++i){

	if((stato[begin[0]-'a'][begin[1]-'0']!='c' and stato[begin[0]-'a'][i-'0']=='c') or stato.status[position[1]-'a'][i-'0']!='O') break; 
	
	char partenza[]={begin[1],begin[0]}
	
	char arrivo[]={begin[1],i}

	*mosse.pushback(Move(arrivo,partenza);} 


for (char i=position[1]-1;'a'>i;--i){
	if((stato[begin[0]-'a'][begin[1]-'0']!='c' and stato[begin[0]-'a'][i-'0']=='c') or stato.status[position[1]-'a'][i-'0']!='O') break;
	char partenza[]={begin[1],begin[0]}
	
	char arrivo[]={i,begin[0]}

	*mosse.pushback(Move(partenza,arrivo);}

for (char i=position[1]+1;i<''i';++i){
	if((stato[begin[0]-'a'][begin[1]-'0']!='c' and stato[begin[0]-'a'][i-'0']=='c') or stato.status[position[1]-'a'][i-'0']!='O') break;
	
	char partenza[]={begin[1],begin[0]}
	
	char arrivo[]={i,begin[0]}

	*mosse.pushback(Move(partenza,arrivo);}
return mosse;}
Pawn(char start[2],int id_0,bool lineage=false,bool king=false):white(lineage),id(id_0)
{for (short i;i<2;++i)position[i]=start[i];uscita=false;}
;};


char* execution (char** stato){
vector<Pawn> WPawn;
vector<Pawn> BPawn;
	for (short int i=0;i<9;++i){
		for (short int j=0;j<9;++j) {
			
			if(stato[i][j]!='O')
				{char posizione[2]={i+'a',j+'0'};
				if(stato[i][j]=='W')WPawn.pusback(Pawn(posizione,WPawn.size(),true))
				(stato[i][j]=='K') WPawn.pusback((posizione,WPawn.size(),true,true))
				else BPawn.pushback(Pawn(posizione,WPawn.size()));};};}
State current(stato);

for (short int i=0;i<=MAX_DEPTH;++i){
	for (auto u:WPawn){u.detect_moves()}

;}
}


