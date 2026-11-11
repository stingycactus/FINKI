import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

class Task {
    private long t;
    private long w;

    public Task(long t, long w) {
        this.t = t;
        this.w = w;
    }

    public long getT() {
        return t;
    }

    public long getW() {
        return w;
    }

    public double getRatio() {
        return (double) t /w;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        List<Task> tasks = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            long T = in.nextInt();
            long W = in.nextInt();
            tasks.add(new Task(T, W));
        }
        tasks.sort(Comparator.comparing(Task::getRatio));
        long sum = 0;
        int time = 0;
        for (int i = 0; i < n; i++) {
            sum+= time * tasks.get(i).getW();
            time+=tasks.get(i).getT();
        }
        System.out.println(sum);
    }
}
