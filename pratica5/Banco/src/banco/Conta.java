/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banco;

/**
 *
 * @author PC11
 */
public class Conta {

    private String nomeCliente;
    private String saldo;
    private String agencia;
    private String numero;
    private String senha;
    private String md5;

    public Conta(String agencia, String numero, String senha) {
        this.agencia = agencia;
        this.numero = numero;
        this.senha = senha;
        this.md5 = SecurityProvider.md5ToServer(this);
    }

    public Conta(String agencia, String numero, String senha, String saldo, String nomeCliente) {
        this.nomeCliente = nomeCliente;
        this.saldo = saldo;
        this.agencia = agencia;
        this.numero = numero;
        this.senha = senha;
        this.md5 = SecurityProvider.md5ToServer(this);
    }

    public Conta(String nomeCliente, String saldo) {
        this.nomeCliente = nomeCliente;
        this.saldo = saldo;
    }

    public String getNomeCliente() {
        return nomeCliente;
    }

    public void setNomeCliente(String nomeCliente) {
        this.nomeCliente = nomeCliente;
    }

    public String getSaldo() {
        return saldo;
    }

    public void setSaldo(String saldo) {
        this.saldo = saldo;
    }

    public String getAgencia() {
        return agencia;
    }

    public void setAgencia(String agencia) {
        this.agencia = agencia;
    }

    public String getNumero() {
        return numero;
    }

    public void setNumero(String numero) {
        this.numero = numero;
    }

    public String getSenha() {
        return senha;
    }

    public void setSenha(String senha) {
        this.senha = senha;
    }

    public String getMd5() {
        return md5;
    }

    public void setMd5(String md5) {
        this.md5 = md5;
    }

    @Override
    public String toString() {
        String saida = "";
        saida += "AGENCIA: " + this.agencia;
        saida += "\nCONTA: " + this.numero;
        saida += "\nSENHA: " + this.senha;
        saida += "\nNOME CLIENTE: " + this.nomeCliente;  
        saida += "\nSALDO: " + this.saldo;
        saida += "\nMD5: " + this.md5;
        
        return saida;
    }
    
    
    public static void main(String[] args) {
        Conta c1 = new Conta("Allan", "10");
        
        System.out.println(c1);
    }
}
