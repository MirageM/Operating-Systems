import java.util.InputMismatchException;
import java.util.Scanner;
//Catalan Sequence
public class Q3Catalan {


    public static void main(String args[]){
        try {
            //initializing the catalan x and y axis
            int numerator;
            int denominator;
            int x, y;
            int Cn;

            System.out.print("Enter the Catalan Number: ");
            Scanner scanner = new Scanner(System.in);
            int userInput = scanner.nextInt();
            for (int n = 0; n <= userInput; n++) {
                x = factorial(n + 1);
                y = factorial(n);
                numerator = factorial(2 * n);
                denominator = x * y;
                Cn = numerator / denominator;
                System.out.println(Cn);


            }
        }catch(InputMismatchException e){
            System.err.println("INVALID INTEGER: Specify a valid integer" );
        }



    }

    //Recursive Factorial Method
    public static int factorial(int num){
        if(num == 0 || num == 1){
            return 1;
        }
        return factorial(num-1)*num;
    }


}
