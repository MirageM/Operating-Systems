import java.util.Random;

public class Student extends Thread{
    //Initializing the student class
    private String studentID;
    private Office taOffice;
    private Random generator;
    private boolean needsHelp;

    //Constructor
    public Student(Office taOffice, String studentID){
        this.taOffice = taOffice;
        this.studentID = studentID;
        generator = new Random();
        needsHelp = true;

    }

    public void run(){
        napTime();
        taOffice.studentIsReady(this);
    }

    //checks if student needs help
    public boolean requestHelp(){
        return needsHelp;
    }
    //Otherwise student leaves
    public void leaves(){
        needsHelp = false;
    }
    public void napTime(){
        try{
            this.sleep(Math.abs(generator.nextInt(99999)));
        }catch(InterruptedException e){
            e.printStackTrace();
        }
    }

    //String representation returns student id

    public String toString(){
        return studentID;
    }


}
