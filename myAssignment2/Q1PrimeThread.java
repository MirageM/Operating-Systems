/*
Question 1
Student: Mirage Mohammad

 */
//Using Scanner for user interface
import java.util.*;
import java.util.Scanner;

public class Q1PrimeThread implements Runnable {
    //instance variable ascendingToPrimeNumber
    private int ascendingToPrimeNumber;

    //Constructor to initialize the number on the command line
    Q1PrimeThread(int ascendingToPrimeNumber){
            this.ascendingToPrimeNumber = ascendingToPrimeNumber;
    }
    //Overriding the method run() from class Runnable
    @Override
    //Method run() prints the prime numbers in ascending order
    public void run() {
            System.out.println(" ");
            System.out.print("Primes numbers are: ");
            int mirage1 = 1;
            while (mirage1 < ascendingToPrimeNumber + 1) {
                //initializing counter to zero
                int programCounter = 0;
                //this loop checks if the number is prime number or not
                for (int mirage2 = 1; mirage2< mirage1 + 1; mirage2++) {
                    if (mirage1 % mirage2 == 0) {
                        programCounter++;
                    }
                }
                if (programCounter == 2) {
                        System.out.print(mirage1 + " ");

                }
                mirage1++;
            }
            System.out.println(" ");

        }


    public static void main(String[] args) {

        try {
            Scanner input = new Scanner(System.in);
            System.out.print("Enter the Number: ");
            int userInput = input.nextInt();

            Q1PrimeThread pThreads = new Q1PrimeThread(userInput);

            Thread pThread = new Thread(pThreads);
            //start() method of thread class is used to begin the execution of threads
            //Returns the values of two threads running concurrently
            pThread.start(); //start() calls the method run()
            //returns all the prime numbers in ascending order

            //In case an invalid integer  isn't entered so exception handling is used
        } catch (InputMismatchException e) {
            System.err.println("Invalid Integer, Please Enter An Integer ");
        }
    }
}
