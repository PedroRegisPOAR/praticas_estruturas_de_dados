#include "candidato.h"

class NoCandidato{

    public:
        Candidato *conteudo;
        NoCandidato *next;

    NoCandidato(Candidato *c, NoCandidato *n){
        this->conteudo = c;
        this->next = n;
    }

    string toString() {
        stringstream stream;

        stream << conteudo->toString();

        if (next == NULL) {
            stream << " -> 0";
        }
        else
        {
            stream << " -> " << next->toString();
        }

        return stream.str();
    }
};
