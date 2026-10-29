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

public class Main {
    public static void main(String[] args) {
        Node<Integer> head = null;
        head = Node.addToFront(head, 3);
        head = Node.addToFront(head, 2);
        head = Node.addToFront(head, 1);        // 1 2 3
        Node.printAll(head);

        head = Node.addToEnd(head, 4);          // 1 2 3 4
        head = Node.addToMiddle(head, 9);       // 1 2 9 3 4
        Node.printAll(head);

        System.out.println(Node.length(head));        // 5
        System.out.println(Node.sum(head));           // 19
        System.out.println(Node.contains(head, 9));   // true
        System.out.println(Node.contains(head, 7));   // false
        Node.printReverse(head);                      // 4 3 9 2 1
        System.out.println();

        Node<String> words = null;
        words = Node.addToEnd(words, "a");
        words = Node.addToEnd(words, "b");
        words = Node.addToMiddle(words, "x");   // a x b
        Node.printAll(words);
    }
}