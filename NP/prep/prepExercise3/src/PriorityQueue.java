import java.util.ArrayList;

public class PriorityQueue<T> {
    private ArrayList<T> queue = new ArrayList<>();
    private ArrayList<Integer> priorities = new ArrayList<>();

    public void add(T item, int priority) {
        for (int i = 0; i < queue.size(); i++) {
            if (priorities.get(i) < priority) {
                queue.add(i, item);
                priorities.add(i, priority);
                return;
            }
        }
        queue.add(item);
        priorities.add(priority);
    }

    public T remove() {
        if (queue.isEmpty()) {
            return null;
        }
        priorities.remove(0);
        return queue.remove(0);
    }

    public static void main(String[] args) {
        PriorityQueue<String> q = new PriorityQueue<>();
        q.add("X", 10);
        q.add("Y", 1);
        q.add("Z", 3);
        System.out.println(q.remove() + " " + q.remove() + " " + q.remove() + " " + q.remove());   // X Z Y null

        q.add("A", 1);
        q.add("B", 2);
        q.add("C", 3);
        System.out.println(q.remove() + " " + q.remove() + " " + q.remove());                      // C B A

        q.add("C", 3);
        q.add("B", 2);
        q.add("A", 1);
        System.out.println(q.remove() + " " + q.remove() + " " + q.remove());                      // C B A

        q.add("first", 5);
        q.add("second", 5);
        q.add("low", 1);
        q.add("third", 5);
        System.out.println(q.remove() + " " + q.remove() + " " + q.remove() + " " + q.remove());   // first second third low

        PriorityQueue<Integer> nums = new PriorityQueue<>();
        nums.add(100, 2);
        nums.add(200, 9);
        System.out.println(nums.remove() + " " + nums.remove());
    }
}
