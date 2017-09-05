#include <cstring>
#include <fstream>
#include <iostream>

#include "nocandidato.h"
class ListaCandidatos{
    public:
    NoCandidato *head;
    int size;

    ListaCandidatos(){
        this->head = NULL;
    }

    ListaCandidatos(string nomeDoArquivo)
    {

        ifstream myfile(nomeDoArquivo.c_str());

        this->head = NULL;

        string dados;
        getline(myfile, dados);
        cout << "nome da regiao: " << dados << endl;
        //cout << "nome da regiao: " << dados << endl;

        while(getline(myfile,dados))
        {
            Candidato *c = new Candidato(dados);
            //cout << "criacao do candidato: " << c.toString() << endl;
            NoCandidato *novoNo = new NoCandidato(c, this->head);
            this->head = novoNo;

        }
    }

    void adicioneComoHead(Candidato* c)
    {
        NoCandidato *noCand = new NoCandidato(c, this->head);
        this->head = noCand;
    }

    bool estaVazia()
    {
        return this->head == NULL;
    }

    int tamanho()
    {
        if(this->estaVazia())
        {
            return 0;
        }
        else{
            int contador = 0;
            NoCandidato *aux = this->head;

            while(aux != NULL)
            {
                aux = aux->next;
                contador++;
            }
            return contador;
        }
    }

    string toString()
    {
        if(this->estaVazia())
        {
            return "0";
        }
        else
        {
            return this->head->toString();
        }
    }

    // Esta errado no pdf, no pdf esta escrito remover
    bool remove(string nome, string sobrenome)
    {
        if(estaVazia())
        {
            return false;
        }
        else
        {
            NoCandidato* it;
            NoCandidato* anterior;
            it = this->head;

            // Trata a cabeca da lista
            if(it->conteudo->nome == nome && it->conteudo->sobrenome == sobrenome)
            {
                this->head = this->head->next;
                delete it;
                return true;
            }

            while(it != NULL)
            {
                if(it->conteudo->nome == nome && it->conteudo->sobrenome == sobrenome)
                {
                    anterior->next = it->next;
                    delete it;
                    return true;
                }
                anterior = it;
                it = it->next;
            }
            return false;
        }

    }

    void filtrarCandidatos(int nota)
    {

        NoCandidato* it;
        NoCandidato* prox;
        it = this->head;

        while(it != NULL)
        {
            if(it->conteudo->nota < nota)
            {
                prox = it->next;
                remove(it->conteudo->nome, it->conteudo->sobrenome);
                it = prox;
            }
            else
            {
                it = it->next;
            }

        }
    }


    void concatena(ListaCandidatos * l)
    {
        NoCandidato * it = head;
        // Trata se a cabeça for NULL
        if (this->head == NULL)
        {
            this->head = l->head;
            return;
        }

        // Percorre a lista toda
        while (it->next != NULL)
        {
            it = it->next;
        }

        // Aponta o ultimo elemento para a cabeça da lista l.
        it->next = l->head;
    }

};
