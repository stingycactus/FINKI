import java.util.NoSuchElementException;
import java.util.Scanner;

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

interface Stack<E> {
    // Elementi na stekot se objekti od proizvolen tip.
    // Metodi za pristap:

    public boolean isEmpty();
    // Vrakja true ako i samo ako stekot e prazen.

    public E peek();
    // Go vrakja elementot na vrvot od stekot.

    // Metodi za transformacija:
    public void clear();
    // Go prazni stekot.

    public void push(E x);
    // Go dodava x na vrvot na stekot.

    public E pop();
    // Go otstranuva i vrakja elementot shto e na vrvot na stekot.
}

class ArrayStack<E> implements Stack<E> {
    private E[] elems; //elems[0...depth-1] se negovite elementi.
    private int depth; //depth e dlabochinata na stekot

    @SuppressWarnings("unchecked")
    public ArrayStack(int maxDepth) {
        // Konstrukcija na nov, prazen stek.
        elems = (E[]) new Object[maxDepth];
        depth = 0;
    }

    public boolean isEmpty() {
        // Vrakja true ako i samo ako stekot e prazen.
        return (depth == 0);
    }

    public E peek() {
        // Go vrakja elementot na vrvot od stekot.
        if (depth == 0)
            throw new NoSuchElementException();
        return elems[depth - 1];
    }

    public void clear() {
        // Go prazni stekot.
        for (int i = 0; i < depth; i++) elems[i] = null;
        depth = 0;
    }

    public void push(E x) {
        // Go dodava x na vrvot na stekot.
        elems[depth++] = x;
    }

    public int size() {
        // Ja vrakja dolzinata na stack-ot.
        return depth;
    }

    public E pop() {
        // Go otstranuva i vrakja elementot shto e na vrvot na stekot.
        if (depth == 0)
            throw new NoSuchElementException();
        E topmost = elems[--depth];
        elems[depth] = null;
        return topmost;
    }
}


class LinkedStack<E> implements Stack<E> {
    // top e link do prviot jazol ednostrano-povrzanata lista koja sodrzi gi elementite na stekot .
    private SLLNode<E> top;
    int size;

    public LinkedStack() {
        // Konstrukcija na nov, prazen stek.
        top = null;
        size = 0;
    }

    public String toString() {
        SLLNode<E> current = top;
        StringBuilder s = new StringBuilder();
        while (current != null) {
            s.append(current.element);
            s.append(" ");
            current = current.succ;
        }
        return s.toString();
    }

    public boolean isEmpty() {
        // Vrakja true ako i samo ako stekot e prazen.
        return (top == null);
    }

    public void clear() {
        // Go prazni stekot.
        top = null;
        size = 0;
    }

    public E peek() {
        // Go vrakja elementot na vrvot od stekot.
        if (top == null)
            throw new NoSuchElementException();
        return top.element;
    }

    public void push(E x) {
        // Go dodava x na vrvot na stekot.
        top = new SLLNode<E>(x, top);
        size++;
    }

    public int size() {
        // Ja vrakja dolzinata na stekot.
        return size;
    }

    public E pop() {
        // Go otstranuva i vrakja elementot shto e na vrvot na stekot.
        if (top == null)
            throw new NoSuchElementException();
        E topElem = top.element;
        size--;
        top = top.succ;
        return topElem;
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


class LinkedQueue<E> implements Queue<E> {

    // Redicata e pretstavena na sledniot nacin:
    // length go sodrzi brojot na elementi.
    // Elementite se zachuvuvaat vo jazli dod SLL
    // front i rear se linkovi do prviot i posledniot jazel soodvetno.
    SLLNode<E> front, rear;
    int length;

    // Konstruktor ...

    public LinkedQueue () {
        clear();
    }

    public boolean isEmpty () {
        // Vrakja true ako i samo ako redicata e prazena.
        return (length == 0);
    }

    public int size () {
        // Ja vrakja dolzinata na redicata.
        return length;
    }

    public E peek () {
        // Go vrakja elementot na vrvot t.e. pocetokot od redicata.
        if (front == null)
            throw new NoSuchElementException();
        return front.element;
    }

    public void clear () {
        // Ja prazni redicata.
        front = rear = null;
        length = 0;
    }

    public void enqueue (E x) {
        // Go dodava x na kraj od redicata.
        SLLNode<E> latest = new SLLNode<E>(x, null);
        if (rear != null) {
            rear.succ = latest;
            rear = latest;
        } else
            front = rear = latest;
        length++;
    }

    public E dequeue () {
        // Go otstranuva i vrakja pochetniot element na redicata.
        if (front != null) {
            E frontmost = front.element;
            front = front.succ;
            if (front == null)  rear = null;
            length--;
            return frontmost;
        } else
            throw new NoSuchElementException();
    }

}




class Job {
    String name;
    LinkedStack<Doc> pile = new LinkedStack<>();
    Job(String name) { this.name = name;}
    @Override
    public String toString() {
        return name;
    }
}

class Doc {
    String name;
    int pages;

    public Doc(String name, int pages) {
        this.name = name;
        this.pages = pages;
    }

    public String getName() {
        return name;
    }

    public int getPages() {
        return pages;
    }

    @Override
    public String toString() {
        return name;
    }
}

class Task {
    String name;
    int pages;
    Task(String name, int pages) { this.name = name; this.pages = pages; }
    @Override
    public String toString() { return name; }
}

public class Main {
    public static void main(String[] args) {
//        LinkedStack<String> pile = new LinkedStack<>();
//        pile.push("cover");
//        pile.push("page1");
//        pile.push("page2");
//        System.out.println(pile);
//        System.out.println(pile.size());
//        System.out.println(pile.peek());
//        pile.pop();
//        pile.pop();
//        pile.pop();
//        System.out.println(pile);
////        pile.pop(); throws NoSuchElementException
//        LinkedQueue<String> q = new LinkedQueue<>();
//        q.enqueue("report");
//        q.enqueue("invoice");
//        q.enqueue("poster");
////        System.out.println(q); prints mem address
//        System.out.println(q.size());
//        System.out.println(q.front);
//        System.out.println(q.rear);
//        System.out.println(q.dequeue());

//        Scanner in = new Scanner(System.in);
//        int n = in.nextInt();
//        int t = in.nextInt();
//        LinkedQueue<Job> jobs = new LinkedQueue<>();
//        for (int i = 0; i < n; i++) {
//            String name = in.next();
//            int pages = in.nextInt();
//            jobs.enqueue(new Job(name, pages));
//        }
//        SLLNode<Job> p = jobs.front;
//        while (p != null) {
//            System.out.println(p.element);
//            p = p.succ;
//        }
//        int ink = 15;
//        while (!jobs.isEmpty()) {
//            if (jobs.peek().pages > ink) {
//                System.out.printf("First not printed: %s%n", jobs.front);
//                System.out.printf("Waiting: %d%n", jobs.size());
//                break;
//            }
//            Job removedJob = jobs.dequeue();
//            ink-=removedJob.pages;
//            System.out.printf("Printed: %s%n", removedJob);
//        }

//        int done = 0;
//        while(!jobs.isEmpty()){
//            Job j = jobs.dequeue();
//            if (j.pages<=t) {
//                System.out.printf("Job %s finished%n", j);
//                done++;
//            } else {
//                j.pages-=t;
//                System.out.printf("Putting %s back last%n", j);
//                jobs.enqueue(j);
//            }
//        }

//
//        Scanner in = new Scanner(System.in);
//        int n = in.nextInt();
//        int t = in.nextInt();
//        LinkedQueue<Job> jobs = new LinkedQueue<>();
//        for (int i = 0; i < n; i++) {
//            String name = in.next();
//            Job j = new Job(name);
//            int k = in.nextInt();
//            for (int d = 0; d < k; d++) {
//                String docName = in.next();
//                int pages = in.nextInt();
//                Doc doc = new Doc(docName, pages);
//                j.pile.push(doc);
//            }
//            jobs.enqueue(j);
//        }
//
//        int done = 0;
//        while (!jobs.isEmpty()) {
//            Job j = jobs.dequeue();
//            int left = t;
//            while (!j.pile.isEmpty()) {
//                if (left<=0) {
//                    break;
//                }
//                Doc top = j.pile.peek();
//                if (top.pages <= left) {
//                    left-=top.pages;
//                    j.pile.pop();
//                } else {
//                    top.pages-=left;
//                    left=0;
//                }
//            }
//            if (j.pile.isEmpty()) {
//                done++;
//                System.out.printf("%d. %s%n", done, j);
//            } else {
//                jobs.enqueue(j);
//            }
//        }

        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int t = in.nextInt();
        int m = in.nextInt();
        LinkedQueue<Task> tasks = new LinkedQueue<>();
        LinkedStack<Task> tray = new LinkedStack<>();
        for (int i = 0; i < n; i++) {
            tasks.enqueue(new Task(in.next(), in.nextInt()));
        }

        int turn = 0;
        int done = 0;
        while (!tasks.isEmpty() || !tray.isEmpty()) {
            if (tasks.isEmpty() && !tray.isEmpty()) {
                while (!tray.isEmpty()) {
                    tasks.enqueue(tray.pop());
                }
            }
            Task task = tasks.dequeue();
            if (task.pages <= t) {
                done++;
                System.out.println(done + ". " + task);
            } else {
                task.pages-=t;
                tray.push(task);
            }
            turn++;
            if (turn % m == 0) {
                while (!tray.isEmpty()) {
                    tasks.enqueue(tray.pop());
                }
            }
        }
    }
}