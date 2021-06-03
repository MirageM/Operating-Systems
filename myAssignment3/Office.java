import java.util.concurrent.Semaphore;
import java.util.Scanner;

/*
void release()
releases a permit, returning it to the semaphore and
increasing the number of available permits by one.
If permit is acquired then it is given the one that is released.
 */

/*
int availablePermits()
returns the current number of permits available in the semaphore
 */
//Mirage Mohammad


//Mutex is an object owned by thread, so there is an ownership in mutex. Mutex allow one thread to access resource
//Semaphore is a signaling mechanism. It allows a number of thread to access shared resources

//Mutex -> Lock
//Semaphore -> Traffic Light

public class Office {



    //Semaphore is a signaling mechanism
    //Initializing the semaphores

    private Semaphore ta;
    private Semaphore desk;
    private Semaphore chairs;

    private int waitingStudent;
    private final int numberOfChairs ;
    private static final int OFFICE_TIME = 999;


    //Constructor

    public Office(int chairInput){
        ta = new Semaphore(0, true);
        desk = new Semaphore(1,true);
        chairs = new Semaphore(0,true);


        waitingStudent = 0;
        numberOfChairs = chairInput;


        taIsReady();



    }

    //TA is ready and available to help the student
    public void taIsReady(){
        System.out.println("\nThe teaching assistant is now available to help ");
        ta.release();
        chairs.release();
        System.out.println("Available Chair Permit: " + chairs.availablePermits() + ", Available Desk With Chair: "+desk.availablePermits());

    }

    //Student is ready to request for help
    public void studentIsReady(Student student){
        //New student is requesting help
        System.out.println("Student #" + student+" is requesting help");
        //The student gets help if the ta is available
        //Otherwise if the ta is occupied with a student then student has to wait and sit down
        if(desk.availablePermits() <= 0){
            studentWaits(student); //student sits down on a chair and waits
        }
        //TA becomes available and helps the student
        //Exception Handling
        if(student.requestHelp()){
            try{
                desk.acquire();
                help(student);
            }catch(InterruptedException e){ // interrupted exception is thrown when a thread is waiting, sleeping or occupied
                e.printStackTrace();
            }
        }

    }


    //Creating the method student waits for student to sit down on a chair and wait
    public void studentWaits(Student student){
        //In case the hallway is full the student leaves
        //3 number of threads (chairs) can access the shared resource
        if(waitingStudent <= numberOfChairs) {
            try {
                waitingStudent++;
                System.out.println("Student #" + student + " takes a seat in the hallway and waits "
                        + " ,Number of waiting students = " + waitingStudent);
                //The threads will not be accessible unless the method taIsReady is releases a chair semaphore
                chairs.acquire();
            } catch (InterruptedException e) { // interrupted exception is thrown when a thread is waiting, sleeping, or occupied
                e.printStackTrace();
            }
        }
        else{
            System.out.println("Student #"+student + " notices no chair is available and will come back at a later time");
            System.out.println("Student #" +student+" resumes programming");
            student.leaves();
        }
        }

    //Creating the method help where the ta helps the student
    //This causes the student to no longer need help
    public void help(Student student){
        if(waitingStudent > 0)
            waitingStudent = waitingStudent-1;
        try{
            ta.acquire(); //gets a hold of the ta
            System.out.println("Student #"+student+" is receiving help from the ta");
            Thread.sleep(OFFICE_TIME);
        }catch(InterruptedException e){
            e.printStackTrace();
        }
        System.out.println("Student #"+student+" is finished");
        desk.release(); // releases the desk and chair for availability
        taIsReady(); // this release a chair in the hallway allowing for another waiting chair to become available
    }

    //Main Method FOr Execution
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        System.out.print("Enter the number of students: ");
        int userInput = input.nextInt();

        int numberOfStudent = userInput;
        int numberOfWaitingChairs = 3;
        int pointer1 = 0;
        int pointer2 = 0;



        Office hour = new Office(numberOfWaitingChairs);
        //creating an array of threads to help student
        Thread[] threads = new Thread[numberOfStudent];
        while(pointer1 < numberOfStudent){
            //Student takes in type office and string
            threads[pointer1] = new Student(hour, pointer1+"");
            pointer1++;
        }
        while(pointer2 < numberOfStudent){
            threads[pointer2].start();
            pointer2++;
        }
    }


}
