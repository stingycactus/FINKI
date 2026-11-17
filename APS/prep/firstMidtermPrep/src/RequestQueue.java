import aps.*;

import java.util.Scanner;

class Request {
    String name;
    int number;

    public Request(String name, int number) {
        this.name = name;
        this.number = number;
    }

    @Override
    public String toString() {
        return name;
    }
}

public class RequestQueue {
    public static void main(String[] args) {
        LinkedQueue<Request> q = new LinkedQueue<>();
        Scanner in = new Scanner(System.in);
        for (int i = 0; i < in.nextInt(); i++) {
            q.enqueue(new Request(in.next(), in.nextInt()));
        }
        while (!q.isEmpty()) {
            Request r = q.dequeue();
            if (r.number == 0) {
                System.out.println(r);
            } else {
                r.number--;
                q.enqueue(r);
            }
        }
    }
}
