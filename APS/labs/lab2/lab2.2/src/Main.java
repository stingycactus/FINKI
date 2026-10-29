import java.util.Scanner;

// One node of a doubly linked list: a value plus arrows in both directions.
class Node<T> {
    private T value;
    private Node<T> prev;   // the node to the left (null for the first node)
    private Node<T> next;   // the node to the right (null for the last node)

    public Node(T value, Node<T> prev, Node<T> next) {
        this.value = value;
        this.prev = prev;
        this.next = next;
    }

    public T getValue() { return value; }
    public void setValue(T value) { this.value = value; }
    public Node<T> getPrev() { return prev; }
    public void setPrev(Node<T> prev) { this.prev = prev; }
    public Node<T> getNext() { return next; }
    public void setNext(Node<T> next) { this.next = next; }

    @Override
    public String toString() {
        return String.format("%s", value);
    }
}

// A normal (NOT circular) doubly linked list: it knows its first node, its last node and its length.
class DLL<T> {
    private Node<T> head;   // first node
    private Node<T> tail;   // last node
    private int size = 0;   // current number of nodes (needed for the circular counting)

    public Node<T> getHead() { return head; }

    // Add a value at the end of the list.
    public void append(T value) {
        Node<T> ins = new Node<>(value, null, null);
        if (head == null) {          // empty list: the new node is both first and last
            head = tail = ins;
        } else {
            ins.setPrev(tail);       // new node points back at the old last node
            tail.setNext(ins);       // old last node points forward at the new node
            tail = ins;              // the new node is now the last node
        }
        size++;
    }

    // Insert a new node with this value right AFTER node p (4 arrows).
    public void insertAfter(Node<T> p, T value) {
        Node<T> ins = new Node<>(value, null, null);
        Node<T> pNext = p.getNext();     // save the node after p BEFORE changing p's arrow
        ins.setPrev(p);                  // ins <- p
        ins.setNext(pNext);              // ins -> pNext (null if p was last, which is fine)
        p.setNext(ins);                  // p -> ins
        if (pNext != null) {
            pNext.setPrev(ins);          // pNext <- ins
        } else {
            tail = ins;                  // p was the last node, so ins is the new last node
        }
        size++;
    }

    // Find the node selected by circular counting, then insert the element after it.
    public void insert(T element, String fromWhere, int k) {
        // Counting starts at 1 on the start node, so the target is k-1 moves away.
        // Every full lap (size moves) brings you back to the start, so only the remainder matters.
        int steps = (k - 1) % size;

        Node<T> p;
        if (fromWhere.equals("left")) {
            p = head;                    // count from the first node, moving right
            for (int i = 0; i < steps; i++) {
                p = p.getNext();
            }
        } else {
            p = tail;                    // count from the last node, moving left
            for (int i = 0; i < steps; i++) {
                p = p.getPrev();
            }
        }
        insertAfter(p, element);         // always insert AFTER (to the right), for both directions
    }

    // Required format: 1<->2<->3, or Prazna lista!!! for an empty list.
    @Override
    public String toString() {
        if (head == null) {
            return "Prazna lista!!!";
        }
        StringBuilder sb = new StringBuilder();
        Node<T> p = head;
        while (p != null) {
            sb.append(p);
            if (p.getNext() != null) {
                sb.append("<->");
            }
            p = p.getNext();
        }
        return sb.toString();
    }
}

public class Main {

    // Final command: skip everyWhich nodes, add addWhat to the next one,
    // continue after it, and stop at the end of the list (no wrapping).
    // It is static in Main (not in DLL<T>) because it does + on the values, which needs Integer, not T.
    public static void skipAndAdd(DLL<Integer> list, int everyWhich, int addWhat) {
        Node<Integer> p = list.getHead();
        while (p != null) {
            for (int i = 0; i < everyWhich && p != null; i++) {
                p = p.getNext();                     // skip one node
            }
            if (p == null) {
                break;                               // fell off the end while skipping: done
            }
            p.setValue(p.getValue() + addWhat);      // change the node we landed on
            p = p.getNext();                         // next round starts after it
        }
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        // Initial list: M, then M elements.
        int m = in.nextInt();
        DLL<Integer> list = new DLL<>();
        for (int i = 0; i < m; i++) {
            list.append(in.nextInt());
        }

        // N insertion commands: element fromWhere howManyPositions
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            int element = in.nextInt();
            String fromWhere = in.next();   // "left" or "right"
            int k = in.nextInt();
            list.insert(element, fromWhere, k);
        }
        System.out.println(list);           // first output line: after all insertions

        // Final command: everyWhich addWhat
        int everyWhich = in.nextInt();
        int addWhat = in.nextInt();
        skipAndAdd(list, everyWhich, addWhat);
        System.out.println(list);           // second output line: after the final command
    }
}