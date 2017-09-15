/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package projeto_pratica4;

import java.util.LinkedList;

/**
 *
 * @author 4E3-01
 */
public class Pilha <T>
{
    LinkedList<T> conteudo;
    
    public Pilha()
    {
        this.conteudo = new LinkedList<>(); // 
    }
    
    void empilha(T novoElemento)
    {
        this.conteudo.addFirst(novoElemento);
    }
    
    T desempilha()
    {
        return this.conteudo.removeFirst();
    }
    
    T topo()
    {
        return this.conteudo.getFirst();
    }

    
    boolean estaVazia()
    {
        return this.conteudo.isEmpty();
    }
}
