#include <iostream>
#include <string>
#include <vector>
#include <thread>
#define PESISTANDARD {{}}
// questo è +o- il template da cui pensavo di partire 
using namespace std;
struct State
{char status[9][9];
short int weight[9][9];/*per il calcolo dell'euristica io farei quanto segue per il bianco è data dalla minima distanza del re dai punti di fuga che sono fissi per il nero io la calcolerei come la minima distanza dai 4punti attorno al re nemico non occupati otremmo ma ritengo che da fare sia troppo complesso quindi ad ogni spostamento del re calcoliamo una griglia di pesi (per il bianco gradiente verso le uscite per il nero gradiente verso il re) e su questa cosa applichiamo minmax se l'idea ti piace ci sarebbe da pensare per come considerare il movimento per le pedine bianche in questa griglia visto che potrebbe far tendere le pedine bianche ad andare nelle uscite la mia idea sarebbe di appioppare alle mosse delle pedine bianche un valore più alto se lo spostamento le porta verso una zona limitrofa al massimo gradiente così da proteggere il re senza impedirne il movimento*/
State(char stato[9][9],int pesi[9][9]=PESISTANDARD){for (short int i=0;i<9;++i){for(short int j=0;j<9;++i){status[i][j]=stato[i][j];};};}
};
class Move{
short int eurist;
char begin[2];
char finish[2];
Moves(char primo[2],char secondo[2]){for (short i=0;i<2;++i){finish[i]=primo[i];begin[i]=secondo[i];};}
public:
char* getmossa(){char* uscita=new char[4];for (short i=0;i<2;++i){uscita[i]=begin[i];uscita[i+2]=finish[i];};}
void seteurist(short int euristica){eurist(euristica);}
};

class Pawn 
{
bool king;
bool white;
char position[2]; //position[0]=x-axis position[1] y-axis
public:/* ho inserito le posizioni come dei char per evitare problemi di conversione successivi se vuoi fare altrimenti dimmi pure */
vector<Move> detect_moves(State stato){vector<Move> mosse; 
for (char i=position[0];'0'>i;--i){if(stato.status[position[1]-'a'][i-'0']!='0') break;mosse.pushback(Move({(char)position[1],(char)i},{(char)position[1],(char)position[0]}))}


for (char i=position[0]+1;i<'9';++i){if(stato.status[position[1]-'a'][i-'0']!='0') break;
mosse.pushback(Move({(char)position[1],(char)i},{(char)position[1],(char)position[0]}))} 


for (char i=position[1];'a'>i;--i){if(stato.status[i-'a'][position[0]-'0']!='0') break;
mosse.pushback(Move({(char)position[1],'0'+(char)i},{(char)position[1],(char)position[0]})) }

for (char i=position[1]+1;i<''i';++i){if(stato.status[i-'a'][position[0]-'0']!='0') break;mosse.pushback(Move({(char)position[1],(char)i},{(char)position[1],(char)position[0]}))   } 
}
void setposition(Move mossa) {for(short int=0;i<2;++i)position[i]=mossa.getmossa()[i];}
};

char* execution (char* stato){
State iniziale(stato);

}


