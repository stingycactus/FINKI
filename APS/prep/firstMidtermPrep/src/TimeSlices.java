import aps.LinkedQueue;

import java.util.Scanner;

class Process {
    String name;
    int time;

    public Process(String name, int time) {
        this.name = name;
        this.time = time;
    }

    @Override
    public String toString() {
        return name;
    }
}

public class TimeSlices {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int q = in.nextInt();
        LinkedQueue<Process> queue = new LinkedQueue<>();
        for (int i = 0; i < n; i++) {
            queue.enqueue(new Process(in.next(), in.nextInt()));
        }
        int time = 0;
        while (!queue.isEmpty()) {
            Process p = queue.dequeue();
            if (p.time > q) {
                p.time-=q;
                time+=q;
                queue.enqueue(p);
            } else {
                time+=p.time;
                System.out.printf("%s %d%n", p, time);
            }
        }
    }
}
