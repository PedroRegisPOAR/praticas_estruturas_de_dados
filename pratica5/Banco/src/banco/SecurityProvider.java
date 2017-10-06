/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package banco;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author PC11
 */
public class SecurityProvider {
    public static String salt = "5a1t";
    public static String md5(String stringToConvert)
    {
        String hashtext="";
        stringToConvert +=salt;
        MessageDigest m;

        try
        {
            m = MessageDigest.getInstance("MD5");
            m.reset();
            m.update(stringToConvert.getBytes());
            byte[] digest = m.digest();
            BigInteger bigInt = new BigInteger(1,digest);
            hashtext = bigInt.toString(16);
        }
        catch (NoSuchAlgorithmException ex)
        {
            Logger.getLogger(SecurityProvider.class.getName()).
            log(Level.SEVERE, null, ex);
        }
        return hashtext;
    }
    public static String md5ToServer(Conta conta)
    {
        String s = "";
        s += conta.getAgencia() + conta.getNumero() + conta.getSenha() + SecurityProvider.salt;
        return md5(s);
    }
    public static void test1()
    {
        System.out.println(SecurityProvider.md5("teste"));
    }
    
    public static void test2()
    {
        Conta c = new Conta("1234", "2222","1245");
        
        String s = "245e43ed3a0d09deac1c8beb52c5e049";
        System.out.println(SecurityProvider.md5ToServer(c));

        // Modificado para facilitar a visualização.
        System.out.println(s.equals(SecurityProvider.md5ToServer(c)));
    }

    
    public static void main(String[] args) {
        String s1 = "66e23b3b8413d2e219536d909eb320dc";
        System.out.println(s1.equals(SecurityProvider.md5("teste")));
        
        SecurityProvider.test2();
        
    }
}

