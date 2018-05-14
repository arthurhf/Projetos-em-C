package fibonacci;
import java.util.Scanner;
public class Fibonacci {    
    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
	long n=1;        
        while(n!=0){
        n = teclado.nextLong();
            if(n>47 || n<0){
                System.out.println("Digite um número entre 0 e 47\n");
            } else {                
                for (int i = 0; i < n; i++) {
                    System.out.print(fibo(i));          
                    
                    if((i+2)!=(n+1)){
                        System.out.print(" ");                     
                    }
                }                
                System.out.print("\n");                   
            
            }
        }
    }
    
    static long fibo(long n){        
            
                if(n<2){
                    return n;
                }else{
                    return fibo(n-1)+fibo(n-2);
                }
                
    }       
         
    
}
