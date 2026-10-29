import java.util.Scanner;

class Node<T> {
    private int value;
    private Node<T> next;
    private Node<T> prev;

    public Node(int value) {
        this.value = value;
        this.next = null;
        this.prev = null;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public Node<T> getNext() {
        return next;
    }

    public void setNext(Node<T> next) {
        this.next = next;
    }

    public Node<T> getPrev() {
        return prev;
    }

    public void setPrev(Node<T> prev) {
        this.prev = prev;
    }

    @Override
    public String toString() {
        return String.format("%s", value);
    }
}

class DLL<T> {
    private Node<T> head;
    private Node<T> tail;

    public void printAll() {
        Node<T> p = head;
        while (p!=null){
            System.out.print(p);
            if (p.getNext()!=null){
                System.out.print("<->");
            }
            p=p.getNext();
        }
    }

    public void append(int element){
        Node<T> ins = new Node<>(element);
        if (head==null){
            head = tail = ins;
        } else {
            ins.setPrev(tail);
            tail.setNext(ins);
            tail = ins;
        }
    }

    public int getSize() {
        Node<T> p = head;
        int count = 0;
        while(p!=null){
            count++;
            p=p.getNext();
        }
        return count;
    }

    public void insertFromLeft(int element, long k) {
        Node<T> ins = new Node<>(element);
        if (head == null) {
            head = tail = ins;
        } else {
            Node<T> p = head;
            for (int i = 0; i < (k-1) % getSize(); i++) {
                p=p.getNext();
                if (p==null){
                    p=head;
                }
            }
            Node<T> pNext = p.getNext();
            p.setNext(ins);
            ins.setPrev(p);
            ins.setNext(pNext);
            if (pNext!=null){
                pNext.setPrev(ins);
            } else {
                tail=ins;
            }
        }
    }

    public void insertFromRight(int element, long k) {
        Node<T> ins = new Node<>(element);
        if (head == null) {
            head = tail = ins;
        } else {
            Node<T> p = tail;
            for (int i = 0; i < (k-1) % getSize(); i++) {
                p=p.getPrev();
                if (p==null){
                    p=tail;
                }
            }
            Node<T> pNext = p.getNext();
            p.setNext(ins);
            ins.setPrev(p);
            ins.setNext(pNext);
            if (pNext!=null){
                pNext.setPrev(ins);
            } else {
                tail=ins;
            }
        }
    }

    public void skipAdd(long skip, int num) {
        Node<T> p = head;
        while(p!=null){
            for (int i = 0; i < skip; i++) {
                p=p.getNext();
                if (p == null){
                    break;
                }
            }
            if (p == null){
                break;
            }
            int value = p.getValue() + num;
            p.setValue(value);
            p=p.getNext();
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int m = in.nextInt();
        DLL<Integer> list = new DLL<>();
        for (int i = 0; i < m; i++) {
            int elem = in.nextInt();
            list.append(elem);
        }
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            int element = in.nextInt();
            String fromWhere = in.next();
            long howManyPositions = in.nextLong();
            if (fromWhere.equals("left")){
                list.insertFromLeft(element, howManyPositions);
            } else if (fromWhere.equals("right")) {
                list.insertFromRight(element, howManyPositions);
            }
        }
        list.printAll();
        System.out.println();
        long everyWhich = in.nextLong();
        int addWhat = in.nextInt();
        list.skipAdd(everyWhich, addWhat);
        list.printAll();
    }
}
