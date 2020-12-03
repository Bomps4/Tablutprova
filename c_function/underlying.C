#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>
#include <chrono>
#define UNDEX -10000
#define MAX_DEPTH 3


char STATO_BASE[][9]= {{ 'O', 'O', 'O', 'B', 'B', 'B', 'O', 'O', 'O'},{ 'O', 'O', 'O', 'O', 'B', 'O', 'O', 'O', 'O'},{ 'O', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'O' }, { 'B', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'B'}, { 'B', 'B', 'W', 'W', 'K', 'W', 'W', 'B', 'B'},{'B', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'B'}, { 'O', 'O', 'O', 'O', 'W', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'B', 'O', 'O', 'O', 'O' }, { 'O', 'O', 'O', 'B','B', 'B', 'O', 'O', 'O' }};
short int PESISTANDARD[][9]={{-1000,7,7,-1000,-1000,-1000,7,7,-1000},{7,6,6,5,-1000,5,6,6,7},{7,6,5,4,3,4,5,6,7},{-1000,5,4,3,2,3,5,6,-1000},{-1000,-1000,3,2,1,2,3,-1000,-1000},{-1000,5,4,3,2,3,5,6,-1000},{7,6,5,4,3,4,5,6,7},{7,6,6,5,-1000,5,6,6,7},{-1000,7,7,-1000,-1000,-1000,7,7,-1000}};

std::atomic<bool> exit_thread_flag{false};
using namespace std;
template<typename T> void secure_swap(vector<T>*a,vector<T>& b){b.swap(*a);delete []a;}
struct State {
char status[9][9];
short int weight[9][9];
State(char stato[9][9],short int pesi[9][9]=PESISTANDARD){
	for (short int i=0;i<9;++i){
		for(short int j=0;j<9;++j){

status[i][j]=stato[i][j];};} 
			status[0][3]='c';status[0][4]='c';status[0][5]='c';status[1][4]='c';status[3][0]='c';status[4][0]='c';
			status[5][0]='c';status[4][1]='c';status[8][3]='c';status[8][4]='c';status[8][5]='c';status[7][4]='c';
			status[3][8]='c';status[4][8]='c';status[5][8]='c';status[4][7]='c';status[4][4]='C';
			};

void move(char* iniziale, char* finale){

if((status[iniziale[0]-'a'][iniziale[1]-'0']=='c')or (status[iniziale[0]-'a'][iniziale[1]-'0']=='B'))
	if(status[finale[0]-'a'][finale[1]-'0']=='c')status[finale[0]-'a'][finale[1]-'0']='c';
	else status[finale[0]-'a'][finale[1]-'0']='B';

else if((status[iniziale[0]-'a'][iniziale[1]-'0']=='C')or (status[iniziale[0]-'a'][iniziale[1]-'0']=='K'))
	status[finale[0]-'a'][finale[1]-'0']='K';

else status[finale[0]-'a'][finale[1]-'0']='W';

if((status[iniziale[0]-'a'][iniziale[1]-'0']!='c')and(status[iniziale[0]-'a'][iniziale[1]-'0']!='C'))status[iniziale[0]-'a'][iniziale[1]-'0']='O';};

State (State const&other){for (int i=0;i<9;++i){for(int j=0;j<9;++j){status[i][j]=other.status[i][j];weight[i][j]=other.weight[i][j];};};}
void spara(){for (int i=0;i<9;++i){for (int j=0;j<9;++j)cout<<status[i][j]<<' ';}cout<<'\n'<<endl;}
State(){};

};


class Pawn 
{
unsigned short int id=-1;
bool king;  
bool white;
char genitore[2];
char position[2]; //position[0]=x-axis(using numbers) position[1] y-axis(using letters a,b,c,d,e ecc)
public:/* ho inserito le posizioni come dei char per evitare problemi di conversione successivi se vuoi fare altrimenti dimmi pure */
//void set_euristica(short int euristic){euristica=euristic;}
Pawn(Pawn const&other){id=other.id;white=other.white;king=other.king;
for (int i=0;i<2;++i)position[i]=other.position[i];for (int i=0;i<2;++i)genitore[i]=other.genitore[i];};
Pawn & operator=(Pawn const&other){Pawn copy(other);myswap(*this,copy);return *this;}
Pawn(Pawn&& that)noexcept:king(false),white(false){myswap(*this,that);}
Pawn& operator=(Pawn&& that)noexcept{myswap(*this,that);return *this;}

friend void myswap(Pawn& lhs,Pawn& rhs)noexcept{
swap(lhs.id,rhs.id);
swap(lhs.genitore,rhs.genitore);
swap(lhs.king,rhs.king);
swap(lhs.white,rhs.white);
swap(lhs.position,rhs.position);}
void set_genitore(char c[2]){for (int i=0;i<2;++i){genitore[i]=c[i];}}
char* get_genitore(){return genitore;}
bool get_king(){return king;}
unsigned int get_id(){return id;}
void set_id(unsigned short int i){id=i;}
bool get_lineage(){return white;}
bool eaten (State stato){
short int re=0;
for (short int c=0;c<2;++c){
if(((stato.status[position[0]-'a'+c-1][position[1]-'0'+c]==(white?'B':'W'))or (stato.status[position[0]-'a'+c-1][position[1]-'0'+c]=='c'))and ((stato.status[position[0]-'a'-c+1][position[1]-'0'-c]==(white?'B':'W')) or (stato.status[position[0]-'a'-c+1][position[1]-'0'-c]=='c'))){if(stato.status[position[0]-'a'][position[1]-'0']=='C' and king)++re; else  return true;}
;}
return re==2;}
char* get_position(){return position;}

bool check_winning (char* king_position){if(white){
char vincenti[][2]={{'a','1'},{'a','2'},{'a','6'},{'a','7'},{'i','1'},{'i','2'},{'i','6'},{'i','7'},{'b','0'},{'c','0'},{'g','0'},{'h','0'},{'b','8'},{'c','8'},{'g','8'},{'h','8'}};for(auto u:vincenti){if(u[0]==king_position[0] and u[1]==king_position[1]) return true;};}return false;}

vector<Pawn> detect_moves(State stato,int ids=-1){

	vector<Pawn> mosse; 
for (char i=position[1]-1;i>'0';--i){
	//char king_position []=king.get_position()
	if((stato.status[position[0]-'a'][position[1]-'0']!='c' and stato.status[position[0]-'a'][i-'0']=='c') or stato.status[position[0]-'a'][i-'0']!='O') {break;}

	//short int euristica=funct(stato,i,position[1])+white?stato[king_position[0]-'a'][king_position[1]-'0']:stato[king_position[0]-'a'][king_position[1]-'0']?7-stato[king_position[0]-'a'][king_position[1]-'0']:1
	
	
	char arrivo[]={position[0],i};
	if(ids!=-1) (mosse).push_back(Pawn(arrivo,id,genitore,white,king));
	else (mosse).push_back(Pawn(arrivo,id,arrivo,white,king)); }


for (char i=position[1]+1;i!='9';++i){

	if((stato.status[position[0]-'a'][position[1]-'0']!='c' and stato.status[position[0]-'a'][i-'0']=='c') or stato.status[position[0]-'a'][i-'0']!='O') {break;} 
	
	
	
	char arrivo[]={position[0],i};

	if(ids!=-1) (mosse).push_back(Pawn(arrivo,id,genitore,white,king));
	else (mosse).push_back(Pawn(arrivo,id,arrivo,white,king)); } 


for (char i=position[0]-1;i>'a';--i){
	if((stato.status[position[0]-'a'][position[1]-'0']!='c' and stato.status[i-'a'][position[1]-'0']=='c') or stato.status[i-'a'][position[1]-'0']!='O') break;
	
	
	char arrivo[]={i,position[1]};

	if(ids!=-1) (mosse).push_back(Pawn(arrivo,id,genitore,white,king));
	else (mosse).push_back(Pawn(arrivo,id,arrivo,white,king)); }

for (char i=position[0]+1;i<'i';++i){
	if((stato.status[position[0]-'a'][position[1]-'0']!='c' and stato.status[i-'a'][position[1]-'0']=='c') or stato.status[i-'a'][position[1]-'0']!='O') break;
	
	
	
	char arrivo[]={i,position[1]};
	
	if(ids!=-1) (mosse).push_back(Pawn(arrivo,id,genitore,white,king));
	else (mosse).push_back(Pawn(arrivo,id,arrivo,white,king)); }
return mosse;}

Pawn(char start[2],int id_0,char* pgenitore ,bool lineage=false,bool re=false):white(lineage),id(id_0),king(re)
{for (short i;i<2;++i){position[i]=start[i];genitore[i]=pgenitore[i];};}
Pawn(char start[2],int id_0,bool lineage=false,bool re=false):white(lineage),id(id_0),king(re)
{for (short i;i<2;++i){position[i]=start[i];genitore[i]=' ';};}
Pawn(){};};

float eur_function(short int* uccisioni,char* re_pos,char* pawn_pos,bool lineage){
short int presa=0;
for (int i=0;i<MAX_DEPTH;++i)presa+=uccisioni[i];
short int distanza=0;
for (int i=0;i<2;++i){short int temp=(short int)(pawn_pos[i]-re_pos[i]);if(temp>=0)distanza+=temp; else distanza-=temp;}
float eur1=presa+0.1*PESISTANDARD[re_pos[0]-'a'][re_pos[1]-'0'];
if(lineage){

short int eur2=distanza*(-distanza+4)+2*PESISTANDARD[re_pos[0]-'a'][re_pos[1]-'0'];
if(eur2>eur1){return eur2;}
else return eur1;
}
else {
short int eur2=distanza*(1*distanza-2)+2*PESISTANDARD[re_pos[0]-'a'][re_pos[1]-'0']-15;
if(eur2<eur1){return eur2;}
else return eur1;
}
}

class Tree{
int bianca[MAX_DEPTH];
int nera[MAX_DEPTH];
float alpha;
float euristiche;
short int uccisioni[MAX_DEPTH];
char posizione_re[MAX_DEPTH][2];
State stati[MAX_DEPTH];
vector<Pawn>::iterator Biterator;
vector<Pawn>::iterator Witerator;
vector<Pawn>::iterator iteratori [MAX_DEPTH];
array<vector<Pawn>,MAX_DEPTH> branches;
public:
Pawn scelta;
Pawn deepen(vector<Pawn> altra_squadra,vector<Pawn> nostra_squadra,short int piuprof=0,short int depth=0){
	bool nostro_colore=nostra_squadra[0].get_lineage();
	if(exit_thread_flag)throw 0;
	if(depth==0)euristiche=UNDEX;

	bool actual_color;
	for(iteratori[depth];iteratori[depth]<branches[depth].end();iteratori[depth]++)
{ 			if(exit_thread_flag)throw 0;
			
			actual_color=(*iteratori[depth]).get_lineage();	
						
			if(depth<(MAX_DEPTH-1)){
			
			
			if((*iteratori[depth]).get_king()){for (short int j=0;j<2;j++){posizione_re[depth+1][j]=(*iteratori[depth]).get_position()[j];};}
			else {for (short int j=0;j<2;j++){posizione_re[depth+1][j]=posizione_re[depth][j];}}
			
			vector<Pawn> futuribili;
			bool precedent_color=(depth==0?altra_squadra[0]:branches[depth-1][0]).get_lineage();
			
			for (auto i:depth==0?altra_squadra:branches[depth-1]){
				if(exit_thread_flag) throw 0;
				if(euristiche!=UNDEX and !precedent_color and alpha>euristiche){iteratori[depth-1]++;return deepen(altra_squadra,nostra_squadra,piuprof,depth-1);}
				if(euristiche!=UNDEX and precedent_color and alpha<euristiche){iteratori[depth-1]++;return deepen(altra_squadra,nostra_squadra,piuprof,depth-1);}
				if(i.check_winning(posizione_re[depth])){if(not nostro_colore){++iteratori[depth-2];return deepen(altra_squadra,nostra_squadra,depth-2);} return *iteratori[0];}
			
				if(i.eaten(stati[depth])) {if(i.get_lineage()){--(uccisioni[depth]);}else{++(uccisioni[depth]);}if(i.get_king()){++iteratori[depth-2];return deepen(altra_squadra,nostra_squadra,depth-2);} continue;} 
				
				vector<Pawn> temp=i.detect_moves(stati[depth],1);
				
				futuribili.reserve(futuribili.size()+distance((temp).begin(),(temp).end()));
				
				futuribili.insert(futuribili.end(),(temp).begin(),(temp).end());
				
				
			}
			//if(*iteratori[depth])
			//stati[depth](*iteratori).get_position()
			
			branches[depth+1].swap(futuribili);
			
			iteratori[depth+1]=branches[depth+1].begin();
			
			
			stati[depth+1]=stati[depth];
			
			
			vector<Pawn>::iterator novita=depth<=1?(nostro_colore?Biterator:Witerator):iteratori[depth-1];
			if((*iteratori[depth]).get_id()==bianca[depth]){
				stati[depth+1].move((*novita).get_position(),(*iteratori[depth]).get_position());++nera[depth];}
			else{bianca[depth]=(*iteratori[depth]).get_id();++(depth==1?(nostro_colore?Biterator:Witerator):iteratori[depth-1]);
					novita=(depth==1?(nostro_colore?Biterator:Witerator):iteratori[depth-1]);
					stati[depth+1].move((*novita).get_position(),(*iteratori[depth]).get_position());++nera[depth];
					if(nera[depth]==(depth==1?(nostro_colore?nostra_squadra:altra_squadra):branches[depth-1]).size()){(depth==1?(nostro_colore?Biterator:Witerator):iteratori[depth-1])-=nera[depth];nera[depth]=0;}
					;}
			
			return deepen(altra_squadra,nostra_squadra,piuprof,depth+1);}
			
			float euristica_temp=eur_function(uccisioni,posizione_re[depth],(*iteratori[depth]).get_position(),(*iteratori[depth]).get_lineage());//stati[depth]);
			
			if(iteratori[depth]==branches[depth].begin()){euristiche= euristica_temp;}
			
			if(alpha!=UNDEX and actual_color and euristica_temp>alpha and depth!=0){iteratori[depth-1]++;return deepen(altra_squadra,nostra_squadra,piuprof,depth-1);}
			
			if(alpha!=UNDEX and not actual_color and euristica_temp<alpha and depth!=0){iteratori[depth-1]++;return deepen(altra_squadra,nostra_squadra,piuprof,depth-1);}
			
			if(actual_color and euristiche>= euristica_temp) {euristiche=euristica_temp;scelta=*(iteratori[0]);}
			else if(not actual_color and euristiche<=euristica_temp){euristiche=euristica_temp;scelta=*(iteratori[0]);}
			if(exit_thread_flag) throw 0;
			}



if(depth!=0){
if(alpha==UNDEX)
	alpha=euristiche;
else if (nostro_colore and euristiche>alpha) alpha=euristiche;
else if (!nostro_colore and euristiche<alpha) alpha=euristiche;
uccisioni[depth]=0;
if(iteratori[depth-1]!=branches[depth-1].end())iteratori[depth-1]++;
return deepen(altra_squadra,nostra_squadra,piuprof,depth-1);}
return scelta;};

void super_deepen(vector<Pawn> altra_squadra,vector<Pawn> nostra_squadra,short int depth=0){
try{
scelta=deepen(altra_squadra,nostra_squadra,0,0);
auto ricordo=branches[MAX_DEPTH-3];
auto ricordo2=branches[MAX_DEPTH-2];
if(branches[MAX_DEPTH-1][0].get_lineage()){Biterator=ricordo2.begin();Witerator=ricordo.begin();}
else {Witerator=ricordo2.begin();Biterator=ricordo.begin();}
branches[0].swap(branches[MAX_DEPTH-1]);
iteratori[0]=branches[0].begin();
stati[0]=stati[MAX_DEPTH-1];
scelta=deepen(branches[MAX_DEPTH-2],branches[MAX_DEPTH-1],1);
}
catch(...){}
;}

Tree (State stato,vector<Pawn> primo_muovere,vector<Pawn> secondo,char king[2],char presente):alpha(UNDEX),euristiche(UNDEX){
for(short int i=0;i<2;++i) posizione_re[0][i]=king[i];
if(presente=='B'){Biterator=primo_muovere.begin();Witerator=secondo.begin();}
if(presente=='W'){Witerator=primo_muovere.begin();Biterator=secondo.begin();}

stati[0]=stato;

vector<Pawn> futuribili;
for (auto i:primo_muovere){		
	auto temp=i.detect_moves(stato);
	futuribili.reserve(futuribili.size()+distance((temp).begin(),(temp).end()));
	futuribili.insert(futuribili.end(),(temp).begin(),(temp).end());

	}
//for (auto u:futuribili){cout<<"iniziale "<<primo_muovere[u.get_id()].get_position()[0]<<primo_muovere[u.get_id()].get_position()[1]<<" siamo nelle  prima futuribile"<<u.get_position()[0]<<u.get_position()[1]<<endl;}


branches[0].swap(futuribili);
iteratori[0]=branches[0].begin();
for (int i=0;i<MAX_DEPTH;++i){uccisioni[i]=0;bianca[i]=0;nera[i]=0;}
}

};




extern "C" void deletare(char* c){delete[] c;}



extern "C" char* execution (char stato[9][9],char presente='W',int time=57){

vector<Pawn> WPawn;
vector<Pawn> BPawn;

char king_position[2];
	for (short int i=0;i<9;++i){
		for (short int j=0;j<9;++j) {
			if(stato[i][j]!='O')
				{char posizione[2]={i+'a',j+'0'};
				if((stato[i][j]=='W')) {WPawn.push_back(Pawn(posizione,WPawn.size(),true,false));}
				else if(stato[i][j]=='K'){WPawn.push_back(Pawn(posizione,WPawn.size(),true,true));king_position[0]=(char)i+'a';king_position[1]=(char)i+'0';}
				else BPawn.push_back(Pawn(posizione,BPawn.size(),false,false));};};}

State current(stato);


Tree albero(current,WPawn,BPawn,king_position,presente);
try{
thread t;
if(presente=='W')t=thread(&Tree::super_deepen,&albero,BPawn,WPawn,0);
else t=thread(&Tree::super_deepen,&albero,WPawn,BPawn,0);

this_thread::sleep_for(std::chrono::seconds(time));

exit_thread_flag = true;
t.join();}
catch(...){};
exit_thread_flag = false;
Pawn scelta=albero.scelta;
char* uscita=new char [6];
for (int i=4;i<6;++i){uscita[i]=scelta.get_genitore()[i-4];};
for (int i=0;i<2;++i){if(presente=='W')uscita[i]=WPawn[scelta.get_id()].get_position()[i]; else if(presente=='B')uscita[i]=BPawn[scelta.get_id()].get_position()[i];}

uscita[2]='-';
uscita[3]='>';
cout<<uscita<<endl;

return uscita;

;}



