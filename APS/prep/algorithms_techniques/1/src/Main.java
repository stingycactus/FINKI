import java.util.Scanner;
import java.util.NoSuchElementException;

class SLLNode<E> {
    protected E element;
    protected SLLNode<E> succ;

    public SLLNode(E elem, SLLNode<E> succ) {
        this.element = elem;
        this.succ = succ;
    }

    @Override
    public String toString() {
        return element.toString();
    }
}


interface Queue<E> {
    // Elementi na redicata se objekti od proizvolen tip.
    // Metodi za pristap:
    public boolean isEmpty();
    // Vrakja true ako i samo ako redicata e prazena.

    public int size();
    // Ja vrakja dolzinata na redicata.

    public E peek();
    // Go vrakja elementot na vrvot t.e. pocetokot od redicata.

    // Metodi za transformacija:

    public void clear();
    // Ja prazni redicata.

    public void enqueue(E x);
    // Go dodava x na kraj od redicata.

    public E dequeue();
    // Go otstranuva i vrakja pochetniot element na redicata.
}

class PriorityQueue<E extends Comparable<E>> implements Queue<E> {

    // Redicata e pretstavena na sledniot nacin:
    // length go sodrzi brojot na elementi.
    // Elementite se zachuvuvaat vo jazli dod SLL
    // front i rear se linkovi do prviot i posledniot jazel soodvetno.
    SLLNode<E> front, rear;
    int length;

    // Konstruktor ...

    public PriorityQueue() {
        clear();
    }

    public boolean isEmpty() {
        // Vrakja true ako i samo ako redicata e prazena.
        return (length == 0);
    }

    public int size() {
        // Ja vrakja dolzinata na redicata.
        return length;
    }

    public E peek() {
        // Go vrakja elementot na vrvot t.e. pocetokot od redicata.
        if (front == null)
            throw new NoSuchElementException();
        return front.element;
    }

    public void clear() {
        // Ja prazni redicata.
        front = rear = null;
        length = 0;
    }
// 1 2 3 (front->1, rear->3)
// latest.info<-4
// rear.succ->latest
// 1 2 3 4 (front->1, rear->3)
// rear = latest;
// 1 2 3 4 (front->1, rear->4)

    public void enqueue(E x) {
        // Go dodava x na kraj od redicata.
        SLLNode<E> latest = new SLLNode<E>(x, null);
        SLLNode<E> previous = front;
        if (isEmpty()) {
            front = rear = latest;
        } else if (latest.element.compareTo(front.element) > 0) {
            latest.succ = front;
            front = latest;
        } else {
            boolean is_latest_max=true;
            while(previous.succ !=null){
                if (latest.element.compareTo(previous.succ.element) > 0) {
                    latest.succ = previous.succ;
                    previous.succ = latest;
                    is_latest_max = false;
                    break;
                }
                else{
                    previous = previous.succ;
                }
            }
            if (is_latest_max){
                rear.succ = latest;
                rear = latest;
            }
        }
        length++;
    }

    public E dequeue() {
        // Go otstranuva i vrakja pochetniot element na redicata.
        if (front != null) {
            E frontmost = front.element;
            front = front.succ;
            if (front == null) rear = null;
            length--;
            return frontmost;
        } else
            throw new NoSuchElementException();
    }

    public String toString() {
        SLLNode<E> current = front;
        StringBuilder s = new StringBuilder();
        while (current != null) {
            s.append(current.element);
            s.append(" ");
            current = current.succ;
        }
        return s.toString();
    }
}



public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int i = 0; i < n; i++) {
            int num = in.nextInt();
            pq.enqueue(num);
        }
        long number = 0;
        while (!pq.isEmpty()) {
            number = number * 10 + pq.dequeue();
        }
        System.out.println(number);
    }
}