import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

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
        return (double) t / w;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int L = in.nextInt();
        List<Task> tasks = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            long T = in.nextInt();
            long W = in.nextInt();
            tasks.add(new Task(T, W));
        }
        tasks.sort(Comparator.comparing(Task::getRatio));
//        long sum = 0;
        int time = 0;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (time + tasks.get(i).getT() > L) {
                continue;
            }
//            sum += time * tasks.get(i).getW();
            time += tasks.get(i).getT();
            count++;
        }
        List<Task> smallestTasks = tasks.stream().sorted(Comparator.comparing(Task::getT))
                .limit(count)
                .sorted(Comparator.comparing(Task::getRatio))
                .collect(Collectors.toList());
        long sum = 0;
        long T = 0;
        for (Task smallestTask : smallestTasks) {
            if (T + smallestTask.getT() > L) {
                continue;
            }
            sum+=smallestTask.getW() * T;
            T+=smallestTask.getT();
//            System.out.printf("T: %d%n", smallestTask.getT());
        }
        System.out.println(count);
        System.out.println(sum);
    }
}