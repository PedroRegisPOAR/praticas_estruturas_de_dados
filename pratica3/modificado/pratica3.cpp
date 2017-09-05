//#include <boost/assign/std/vector.hpp>
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <hash_set>

#include <list>


#include <vector>

using namespace std;

// Necessário para inicialização de vectors
using __gnu_cxx::hash_set;

//using namespace boost::assign;
using namespace std;
class State
{

   public:
    /*
     * o estado fornece a posição de cada veículo, utilizando a seguinte convenção :
     * para um veículo horizontal é a coluna da casa mais à esquerda
     * para um veículo vertical é a coluna da casa mais acima
     * (lembrete: a coluna mais à esquerda é 0, e a linha mais alta é 0)
     */
    vector<int> pos;

    /*
     * nós guardamos qual o deslocamento levou a este estado
     */
    int c;
    int d;
    State* prev;

    /*
     * constrói um estado inicial (c e d recebem qualquer valor = lixo)
     */
    State(vector<int>& p) {
        //pos = new int[p.size()];
        int tam = p.size();
        for (int i = 0; i < tam; i++)
            pos.push_back(p[i]);
        prev = NULL;
    }

    /*
     * constrói um estado obtido a partir de s deslocando-se o veículo c de d (-1 ou +1)
     */
    State(State* s, int c, int d) {

        // Salva o estado anteriror
        prev = s;

        this->c = c;
        this->d = d;

        // Copia de um vetor para outro
        for(int i = 0; i< s->pos.size(); i++)
        {
            pos.push_back(s->pos[i]);
        }

        pos[c] += d;

    }

    // nós ganhamos?
    bool success()
    {
        return pos[0] == 4;
    }

    bool equals(State* s)
    {
        if (s->pos.size() != pos.size())
        {
            cerr << "Estados de comprimento diferentes" << endl;
            exit(1);
        }
        int tamanho = pos.size();

        for (int i = 0; i < tamanho; i++)
            if (pos[i] != s->pos[i]) return false;
        return true;
    }
};

//necessário para uso de hash_set

//função hash
struct hash_state
{
   size_t operator()(const State* t) const
   {
     int h = 0;

     for (int i = 0; i < t->pos.size(); i++)
            h = 37 * h + t->pos[i];

     return h;
   }
};

//função igualdade para hash_set
struct eq_state
{
   bool operator()(const State* t1, const State* t2) const {

       if(t1->pos.size() != t2->pos.size()) return false;
       for(int i=0; i < t1->pos.size(); i++){
               if(t1->pos[i] != t2->pos[i]) return false;

       }
	  return true;
   }
};

class RushHour {

      public:

    /*
     * a representação do problema é :
     * a grade tem 6 colunas, numeradas 0 a 5 de esquerda para direita
     * e 6 linhas, numeradas de 0 a  5 de cima para baixo
     *
     * existem nbcars carros, numerados de 0 a  nbcars-1
     * para cada veículo i :
     * - color[i] fornece sua cor
     * - horiz[i] indica se temos um carro na horizontal
     * - len[i] fornece o seu comprimento (2 ou 3)
     * - moveon[i] indica em qual linha o carro se desloca para um carro horizontal
     *   e em qual coluna para um carro vertical
     *
     * o veiculo de indice 0 é o que tem que sair, temos então
     * horiz[0]==true, len[0]==2, moveon[0]==2
     */

    int nbcars;
    vector<string> color;
    vector<bool> horiz;
    vector<int> len;
    vector<int> moveon;

    int nbMoves;
    /*
     * a matriz free é utilizada em moves para determinar rapidamente se a casa (i,j) está livre
     */
    bool free[6][6];
/*
    Se horizontal true
    moveon representa a linha
    e pos a coluna

*/
    void initFree(State* s)
    {
        // Primeiro inicializa-se a matriz com todos os valores com true.
        for(int i = 0; i < 6; i++)
        {
            for(int j = 0;  j< 6; j++)
            {
                free[i][j] = true;
            }
        }

        // Marca as posiçoes que estao com carros  com false
        // Notar que eh necessario verificar se o carro esta na vertical ou na horizontal.
        for(int i = 0; i < s->pos.size(); i++)
        {
            for(int j = 0; j < len[i]; j++)
            {
                if(horiz[i] == true)
                {
                    free[moveon[i]][s->pos[i] + j] = false;
                }
                else
                {
                    free[s->pos[i] + j ][moveon[i]]= false;

                }
            }
        }

    }

    /*
     * retorna a lista de deslocamentos a partir de s
     */
    list<State*> moves(State* s) {
        initFree(s);
        list<State*> l;

        for(int i = 0; i< s->pos.size(); i++)
        {
            if(horiz[i] == true)
            {
                // Guarda o estado
                if(s->pos[i] + len[i] < 6 && free[moveon[i]][s->pos[i] + len[i]] == true)
                {
                    l.push_back(new State(s, i, +1));
                }
                if(s->pos[i] - 1 >= 0 && free[moveon[i]][s->pos[i] - 1] == true)
                {
                    l.push_back(new State(s, i, -1));
                }
            }
            else
            {
                if(s->pos[i] + len[i] < 6 && free[s->pos[i] + len[i]][moveon[i]] == true)
                {
                    l.push_back(new State(s, i, +1));
                }
                if(s->pos[i] - 1 >= 0 && free[s->pos[i] - 1][moveon[i]] == true)
                {
                    l.push_back(new State(s, i, -1));
                }
            }
        }

        return l;
    }

    /*
     * procura uma solução a partir de s
     */
    State* solve(State* s)
    {
        /*
            Atençao: Esse código foi desenvolvido em parceiria com
            Eduardo Jose Tome de Macedo
        */

        hash_set<State*,hash_state,eq_state> visited;
        visited.insert(s);
        queue<State*> Q;
        Q.push(s);
        while (!Q.empty())
        {
            State *atual = Q.front();
            Q.pop();
            list<State*> novos_estados = moves(atual);

            for(list<State*>::iterator it = novos_estados.begin(); it != novos_estados.end(); it++)
            {
                if(visited.count(*it) > 0)
                {
                    continue;
                }
                if((*it)->success())
                {
                    return *it;
                }
                Q.push(*it);
                visited.insert(*it);
            }
        }

        cerr << "sem solução" << endl; exit(1);

        // Ideia exposta em sala de aula
        /*
        hash_set<State*,hash_state,eq_state> visited;
        visited.insert(s);
        queue<State*> Q;
        Q.push(s);

        while (!Q.empty()) {
            State *atual = Q.pop_back();
            list<State*> novos_estados = moves(atual);
            for(int i=0; i < ; i++)
            {
                if(visited.count(novos_estados[i]) > 0 )
                {
                    continue;
                }
                if(novos_estados[i].success)
                {
                    return novos_estados[i];
                }
                Q.push(novos_estados[i]);
                visited.insert(novos_estados[i]);
            }
        }

        cerr << "sem solução" << endl; exit(1);
        */

    }

    /*
     * imprime uma solução
     */
    void printSolution(State* s) {
        /*
            Atençao: Esse código foi desenvolvido em parceiria com
            Eduardo Jose Tome de Macedo
        */

        vector<State*> pilha;
        nbMoves = 0;
        while (s->prev != NULL) {
            pilha.push_back(s);
            s = s->prev;
            nbMoves++;
        }
        cout << nbMoves << " deslocamentos" << endl;

        int fim = pilha.size() - 1;

        while (fim >= 0) {
            State * estado = pilha[fim];
            int veiculo = estado->c;

            if (horiz[veiculo] == true)
            {
                cout << "veiculo " << color[veiculo] << " para a" << (estado->d == 1 ? " direita" : " esquerda") << endl;
            }
            else
            {
                cout << "veiculo " << color[veiculo] << " para" << (estado->d == 1 ? " baixo" : " cima") << endl;
            }

            fim--;
        }
    }

    void test1()
    {

        int positioning[] = {1,0,1,4,2,4,0,1};
        vector<int> start(positioning, positioning+8);
        State* s0 = new State(start);
        cout << (!s0->success()) << endl;
        State* s = new State(s0, 1, 1);

        cout << (s->prev == s0) << endl;
        cout << s0->pos[1] << " " << s->pos[1] << endl;

        s = new State(s,6,1);
        s = new State(s,1,-1);
        s = new State(s,6,-1);

        cout << s->equals(s0) << endl;

        s = new State(s0,1,1);
        s = new State(s,2,-1);
        s = new State(s,3,-1);
        s = new State(s,4,-1);
        s = new State(s, 4, -1);
        s = new State(s,5,-1);
        s = new State(s,5,-1);
        s = new State(s,5,-1);
        s = new State(s,6,1);
        s = new State(s, 6, 1);
        s = new State(s, 6, 1);
        s = new State(s,7,1);
        s = new State(s, 7, 1);
        s = new State(s,0,1);
        s = new State(s,0,1);
        s = new State(s,0,1);

        cout << (s->success()) << endl;
    }

    void test2()
    {
        nbcars = 8;
        bool horiz1[] = {true, true, false, false, true, true, false, false};
        horiz.assign(horiz1, horiz1+8);
        int len1[] = {2,2,3,2,3,2,3,3};
        len.assign(len1,len1+8);
        int moveon1[] = {2,0,0,0,5,4,5,3};
        moveon.assign(moveon1, moveon1+8);
        int start1[] = {1,0,1,4,2,4,0,1};
        vector<int> start(start1,start1+8);
        State* s = new State(start);
        initFree(s);
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
                cout << free[i][j] << "\t";
            cout << endl;
        }
    }

    void test3()
    {
        nbcars = 12;
        bool horiz1[] = {
            true, false, true, false, false, true, false, true,
            false, true, false, true
        };
        horiz.assign(horiz1, horiz1+nbcars);
        int len1[] = {2,2,3,2,3,2,2,2,2,2,2,3};
        len.assign(len1,len1+12);
        int moveon1[] = {2,2,0,0,3,1,1,3,0,4,5,5};
        moveon.assign(moveon1,moveon1+nbcars);
        int start1[] = {1,0,3,1,1,4,3,4,4,2,4,1};
        vector<int> start(start1,start1+nbcars);
        State* s = new State(start);
        int start02[] = {1,0,3,1,1,4,3,4,4,2,4,2};
        vector<int> start2(start02,start02+nbcars);
        State* s2 = new State(start2);
        int n = 0;
        for (list<State*> L = moves(s); !L.empty(); n++) L.pop_front();
        cout << n << endl;
        n = 0;
        for (list<State*> L = moves(s2); !L.empty(); n++) L.pop_front();
        cout << n << endl;
    }

    void test4()
    {
        nbcars = 12;
        string color1[] = {"vermelho","verde claro","amarelo","laranja",
            "violeta claro","azul ceu","rosa","violeta","verde","preto","bege","azul"
        };
        color.assign(color1, color1+nbcars);
        bool horiz1[] = {true, false, true, false, false, true, false,
                         true, false, true, false, true
                        };
        horiz.assign(horiz1, horiz1+nbcars);
        int len1[] = {2,2,3,2,3,2,2,2,2,2,2,3};
        len.assign(len1,len1+nbcars);
        int moveon1[] = {2,2,0,0,3,1,1,3,0,4,5,5};
        moveon.assign(moveon1,moveon1+nbcars);
        int start1[] = {1,0,3,1,1,4,3,4,4,2,4,1};
        vector<int> start(start1,start1+nbcars);
        State* s = new State(start);
        int n = 0;
        for (s = solve(s); s->prev != NULL; s = s->prev) n++;
        cout << n << endl;
    }

    void solve22()
    {
        nbcars = 12;
        string color1[] = {"vermelho","verde claro","amarelo","laranja",
            "violeta claro","azul ceu","rosa","violeta","verde","preto","bege","azul"
        };
        color.assign(color1, color1+nbcars);
        bool horiz1[] = {true, false, true, false, false, true, false,
                         true, false, true, false, true
                        };
        horiz.assign(horiz1, horiz1+nbcars);
        int len1[] = {2,2,3,2,3,2,2,2,2,2,2,3};
        len.assign(len1,len1+nbcars);
        int moveon1[] = {2,2,0,0,3,1,1,3,0,4,5,5};
        moveon.assign(moveon1,moveon1+nbcars);
        int start1[] = {1,0,3,1,1,4,3,4,4,2,4,1};
        vector<int> start(start1,start1+nbcars);
        State* s = new State(start);
        s = solve(s);
        printSolution(s);
    }

    void solve1()
    {
        nbcars = 8;
        string color1[] = {
                            "vermelho","verde claro","violeta","laranja",
                            "verde","azul ceu","amarelo","azul"
                          };
        color.assign(color1, color1+nbcars);
        bool horiz1[] = {
                         true, true, false, false,
                         true, true, false, false
                        };
        horiz.assign(horiz1, horiz1+nbcars);
        int len1[] = {2,2,3,2,3,2,3,3};
        len.assign(len1,len1+nbcars);
        int moveon1[] = {2,0,0,0,5,4,5,3};
        moveon.assign(moveon1,moveon1+nbcars);
        int start1[] = {1,0,1,4,2,4,0,1};
        vector<int> start(start1,start1+nbcars);
        State* s = new State(start);
        s = solve(s);
        printSolution(s);
    }

    void solve40()
    {
        nbcars = 13;
        string color1[] = {
                            "vermelho","amarelo","verde claro","laranja","azul claro","rosa",
                            "violeta claro","azul","violeta","verde","preto","bege","amarelo claro"
                          };
        color.assign(color1, color1+nbcars);
        bool horiz1[] = {
                        true, false, true, false, false, false, false,
                         true, false, false, true, true, true
                        };
        horiz.assign(horiz1, horiz1+nbcars);
        int len1[] = {2,3,2,2,2,2,3,3,2,2,2,2,2};
        len.assign(len1,len1+nbcars);
        int moveon1[] = {2,0,0,4,1,2,5,3,3,2,4,5,5};
        moveon.assign(moveon1,moveon1+nbcars);
        int start1[] = {3,0,1,0,1,1,1,0,3,4,4,0,3};
        vector<int> start(start1,start1+nbcars);
        State* s = new State(start);
        s = solve(s);
        printSolution(s);
    }
};


int main(){

    // Para rodar os testes basta descomentar as linhas abaixo.
    // Todos os testes estao funcionando.

    RushHour rush;

    //rush.test1();
    //rush.test2();
    //rush.test3();
    //rush.test4();
    //rush.solve1();
    //rush.solve22();
    rush.solve40();

	return 0;
}
