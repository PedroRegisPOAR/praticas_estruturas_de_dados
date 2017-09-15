/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package projeto_pratica4;

/**
 *
 * @author 4E3-01
 */
public class CalcRPN 
{
    Pilha<Double> aPilha;
    Pilha<Double> hist;
    
    private CalcRPN()
    {
        this.aPilha = new Pilha<>();
    }
    
    
    
    public void exec(String cmd)
    {
        try
        {
            Double valor = Double.parseDouble(cmd);
            this.aPilha.empilha(valor);
            this.hist.empilha(new Operacao(valor)); // Verificar como funciona.
        }
        catch(Exception e)
        {
            if(cmd.equals("+"))
            {
                this.mais();
                this.hist.empilha(new Operacao("+", a, b));
            }
            else if (cmd.equals("-"))
            {
                this.menos();
                this.hist.empilha(new Operacao("-", a, b));
            }
            else if (cmd.equals("clear"))
            {
                this.aPilha.apagar();
            }
            else if (cmd.equals("undo"))
            {
                //
            }
        }
    }
}
