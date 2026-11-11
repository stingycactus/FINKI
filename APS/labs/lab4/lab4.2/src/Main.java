import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

class Task {
    private long t;
    private long w;
    private int id;

    public Task(long t, long w, int id) {
        this.t = t;
        this.w = w;
        this.id = id;
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

    public int getId() {
        return id;
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
            tasks.add(new Task(T, W, i+1));
        }
        tasks.sort(Comparator.comparing(Task::getRatio));
        long sum = 0;
        long time = 0;
        for (int i = 0; i < n; i++) {
            time+=tasks.get(i).getT();
            sum+= time * tasks.get(i).getW();
        }
        System.out.println(sum);
        for (Task task : tasks) {
            System.out.printf("%d ", task.getId());
        }
    }
}
