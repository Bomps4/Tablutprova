#include <iostream>
#include <string>
#include <vector>
// questo è +o- il template da cui pensavo di partire 
using namespace std;
struct State
{char status[9][9];
short weight[9][9];/* per il calcolo dell'euristica io farei quanto segue per il bianco è data dalla minima distanza del re dai punti di fuga che sono fissi per il nero io la calcolerei come la minima distanza dai 4punti attorno al re nemico non occupati otremmo ma ritengo che da fare sia troppo complesso quindi ad ogni spostamento del re calcoliamo una griglia di pesi (per il bianco gradiente verso le uscite per il nero gradiente verso il re) e su questa cosa applichiamo minmax se l'idea ti piace ci sarebbe da pensare per come considerare il movimento per le pedine bianche in questa griglia visto che potrebbe far tendere le pedine bianche ad andare nelle uscite la mia idea sarebbe di appioppare alle mosse delle pedine bianche un valore più alto se lo spostamento le porta verso una zona limitrofa al massimo gradiente così da proteggere il re senza impedirne il movimento  */
State(char stato[9][9],int pesi[9][9]){}
};
class Move{
short eurist;
char finish[2];
Moves(char primo[2]){for (int i=0;i<2;++i)finish[i]=secondo[i];}
public:
char* getmossa(){return finish}
void seteurist(int euristica){eurist(euristica);}
};

class Pawn 
{
bool king;
bool white;
char position[2]; //position[0]=x-axis position[1] y-axis
public:/* ho inserito le posizioni come dei char per evitare problemi di conversione successivi se vuoi fare altrimenti dimmi pure */
vector<Move> detect_moves(State stato){vector<Move> mosse; 
for (char i=position[0]-'0'-1;position[0]-'0'>i;--i){if(stato.status[position[1]-'a'][i-'0']!='0') break;mosse.pushback(Move({'a'+(char)position[1],'0'+(char)i}))}


for (char i=position[0]-'0'+1;i<9;++i){if(stato.status[position[1]-'a'][i-'0']!='0') break;mosse.pushback(Move({'a'+(char)position[1],+(char)i}))} 


for (char i=position[1]-'a'-1;position[1]-'a'>i;--i){if(stato.status[i-'a'][position[0]-'0']!='0') break;mosse.pushback(Move({'a'+(char)position[1],'0'+(char)i})) }

for (char i=position[1]-'a'+1;i<9;++i){if(stato.status[i-'a'][position[0]-'0']!='0') break;mosse.pushback(Move({'a'+(char)position[1],'0'+(char)i}))   } 
}
void setposition(Move mossa) {for(short int=0;i<2;++i)position[i]=mossa.getmossa()[i];}
};
