import java.util.Scanner;

class Node<T> {
    private T value;
    private Node<T> next;

    public Node(T value, Node<T> next) {
        this.value = value;
        this.next = next;
    }

    public T getValue() {
        return value;
    }

    public Node<T> getNext() {
        return next;
    }

    public void setValue(T value) {
        this.value = value;
    }

    public void setNext(Node<T> next) {
        this.next = next;
    }

    @Override
    public String toString() {
        return String.format("%s", value);
    }
}

class SLL<T> {
    private Node<T> head;

    public void append(T n) {
        Node<T> ins = new Node<T>(n, null);
        if (head == null) {
            head = ins;
            return;
        }
        Node<T> p = head;
        while (p.getNext() != null) {
            p = p.getNext();
        }
        p.setNext(ins);
    }

    public void printAll() {
        if (head == null) {
            System.out.print("Prazna lista!!!");
        }
        Node<T> p = head;
        while (p!=null){
            System.out.printf(String.format("%s", p));
            if (p.getNext()!=null){
                System.out.print("->");
            }
            p=p.getNext();
        }
    }

    public void removeNode(Node<T> node) {
        if (head == null) {
            return;
        }
        if (head == node) {
            head = head.getNext();
            return;
        }
        Node<T> p = head;
        while (p.getNext() != null && p.getNext() != node) {
            p = p.getNext();
        }
        if (p.getNext() == node) {
            p.setNext(node.getNext());
        }
    }

    public Node<T> getHead() {
        return head;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        SLL<Long> firstList = new SLL<>();
        for (int i = 0; i < n; i++) {
            long elem = in.nextLong();
            firstList.append(elem);
        }
        SLL<Long> secondList = new SLL<>();
        int m = in.nextInt();
        for (int i = 0; i < m; i++) {
            long elem = in.nextLong();
            secondList.append(elem);
        }
        double x = Double.parseDouble(in.next());
        SLL<String> resultList = new SLL<>();
        Node<Long> p1 = firstList.getHead();
        Node<Long> p2 = secondList.getHead();
        while (p1 != null && p2 != null) {
            long a = p1.getValue();
            long b = p2.getValue();
            Node<Long> p2Next = p2.getNext();
            if (Math.abs(a - b) > x) {
                resultList.append(String.format("Outlier %d", a));
                secondList.removeNode(p2);
            } else {
                resultList.append(String.format("%d", a));
            }
            p1 = p1.getNext();
            p2 = p2Next;
        }
        if (n > m) {
            while (p1 != null){
                resultList.append(String.format("Unchecked %d", p1.getValue()));
                p1 = p1.getNext();
            }
        }
        resultList.printAll();
        System.out.println();
        secondList.printAll();
    }
}
