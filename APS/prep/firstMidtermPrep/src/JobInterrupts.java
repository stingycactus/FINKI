import aps.*;

import java.util.Scanner;

class Job {
    String name;
    int time;

    public Job(String name, int time) {
        this.name = name;
        this.time = time;
    }
}

public class JobInterrupts {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        LinkedStack<Job> jobs = new LinkedStack<>();
        LinkedStack<Job> finished = new LinkedStack<>();
        int n = in.nextInt();
        int last = 0;
        for (int i = 0; i < n; i++) {
            String name = in.next();
            String command = in.next();
            int t = in.nextInt();

            if (!jobs.isEmpty()) {
                jobs.peek().time += t - last;    // running job gets the time since last log
            }

            if (command.equals("start") || command.equals("interrupt")) {
                jobs.push(new Job(name, 0));     // new job runs now
            } else {
                finished.push(jobs.pop());       // done; the one below resumes
            }
            last = t;
        }
        while (!finished.isEmpty()) {
            Job j = finished.pop();
            System.out.println(j.name + " " + j.time);
        }
    }
}
