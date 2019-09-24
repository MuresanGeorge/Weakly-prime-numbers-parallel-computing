import java.util.ArrayList;
import java.util.List;

/**
 * Created by Bianca on 4/5/2019.
 */
public class Main {

    public static void main (String args []) throws InterruptedException {


        int threadNo = 8;
        List<Thread> threadsList = new ArrayList<Thread>();

        long start = System.nanoTime();

        for(int i = 1; i <= threadNo; i++){

            Runnable task = new WeaklyThread(threadNo,i);
            Thread worker = new Thread(task);
            worker.start();
            threadsList.add(worker);
        }
        for(Thread t : threadsList){
            t.join();
            System.out.println(t.getId());
        }

        long end = System.nanoTime();
        long timeElapsed = end - start;

        System.out.println("Execution time in nanoseconds  : " + timeElapsed);

        double elapsedTimeInSecond = (double) timeElapsed / 1_000_000_000;
        System.out.println("Execution time in seconds:" + String.format("%.4f", elapsedTimeInSecond));

    }
}
