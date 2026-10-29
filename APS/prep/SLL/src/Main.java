import java.util.NoSuchElementException;

class Node<T> {
    private T value;
    private Node<T> next;

    public void setNext(Node<T> next) {
        this.next = next;
    }

    public T getValue() {
        return value;
    }

    public Node<T> getNext() {
        return next;
    }

    public Node(T value, Node<T> next) {
        this.value = value;
        this.next = next;
    }

    @Override
    public String toString() {
        return String.format("Node with value: %s", value);
    }

    public static <T> void printAll(Node<T> head){
        Node<T> p = head;
        while(p!=null){
            System.out.println(p);
            p = p.getNext();
        }
    }

    public static <T> Node<T> addToFront(Node<T> head, T value){
        Node<T> newNode = new Node<>(value, head);
        return newNode;
    }

    public static <T> Node<T> addToEnd(Node<T> head, T value){
        Node<T> endNode = new Node<>(value, null);
        if (head == null) {
            return endNode;
        }
        Node<T> p = head;
        while (p.getNext()!=null){
            p=p.getNext();
        }
        p.setNext(endNode);
        return head;
    }

    public static <T> Node<T> addToMiddle(Node<T> head, T value){
        Node<T> middleNode = new Node<>(value, null);
        int nodeCount = length(head);
        Node<T> p = head;
        for (int i = 0; i < (nodeCount-1)/2; i++) {
            p = p.getNext();
        }
        middleNode.setNext(p.getNext());
        p.setNext(middleNode);
        return head;
    }

    public static <T> int length(Node<T> head){
        int nodeCount = 0;
        Node<T> p = head;
        while(p!=null){
            nodeCount++;
            p = p.getNext();
        }
        return nodeCount;
    }

    public static <T extends Number> double sum(Node<T> head) {
        double sum = 0;
        Node<T> p = head;
        while (p != null) {
            sum += p.getValue().doubleValue();
            p = p.getNext();
        }
        return sum;
    }

    public static <T> boolean contains(Node<T> head, T value) {
        Node<T> p = head;
        while(p!=null) {
            if (p.getValue().equals(value)){
                return true;
            }
            p= p.getNext();
        }
        return false;
    }

    public static <T> void printReverse(Node<T> head) {
        if (head==null){
            return;
        }
        System.out.printf("forwards: %s ", head.getValue());
        printReverse(head.next);
        System.out.printf("backwards: %s ", head.getValue());
    }

}

class SLL<T> {
    private Node<T> head;
    private int size;

    public void addFirst(T value) {
        head = Node.addToFront(head, value);
        size++;
    }
    public void addLast(T value) {
        head = Node.addToEnd(head, value);
        size++;
    }
    public int size() {
        return size;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        Node<T> p = head;
        while (p != null) {
            sb.append(p.getValue());
            if (p.getNext() != null) {
                sb.append(" -> ");
            }
            p = p.getNext();
        }
        return sb.toString();
    }

    public int search(T x) {
        Node<T> p = head;
        for (int i = 0; i < size(); i++) {
            if (p.getValue().equals(x)){
                return i;
            }
            p=p.getNext();
        }
        return -1;
    }

    public Node<T> get(int index) {
        Node<T> p = head;
        for (int i = 0; i < index; i++) {
            p=p.getNext();
        }
        return p;
    }

    public void removeFirst(){
        if (head == null) {
            throw new NoSuchElementException();
        }
        head = head.getNext();
        size--;
    }

    public void removeLast(){
        if (head == null) {
            throw new NoSuchElementException();
        }
        if (head.getNext() == null) {
            head = null;
            size--;
        }
        Node<T> p = head;
        while (p.getNext().getNext() != null) {
            p = p.getNext();
        }
        p.setNext(null);
        size--;
    }

    public void remove (T x) {
        if (head == null) {
            throw new NoSuchElementException();
        }
        if (head.getValue().equals(x)) {
            head = head.getNext();
            size--;
        }
        Node<T> p = head;
        while (p.getNext()!=null && !p.getNext().getValue().equals(x)){
            p = p.getNext();
        }
        if (p.getNext() != null) {
            p.setNext(p.getNext().getNext());
            size--;
        }
    }

    public void insertAt(int index, T x){
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException();
        }
        if (index == 0) { // covers null too since we check if the index is valid first, empty list only has index 0
            head = new Node<>(x, head);
            size++;
            return;
        }
        Node<T> curr = head;
        for (int i = 0; i < index - 1; i++) { // 0, 1, 2
            curr = curr.getNext();  // for index 1 curr points to 0 -> 0, x, 1, 2
        }
        Node<T> n = new Node<>(x, curr.getNext());
        curr.setNext(n);
        size++;
    }

}

public class Main {
    public static void main(String[] args) {

    }
}