import java.util.*;

class Acrobat {
    long weight;
    long strength;
    int id;

    public Acrobat(long weight, long strength, int id) {
        this.weight = weight;
        this.strength = strength;
        this.id = id;
    }

    public long getSum() {
        return weight + strength;
    }
}

public class Main {
    public static void main(String[] args) {
        tower(new long[]{10, 2, 3}, new long[]{3, 5, 3});
        tower(new long[]{5}, new long[]{8});
        tower(new long[]{3, 2, 4, 1}, new long[]{2, 3, 1, 4});
        tower(new long[]{1, 4, 2, 6, 3}, new long[]{6, 1, 3, 2, 5});
        tower(new long[]{10, 1}, new long[]{1, 20});
        tower(new long[]{1000000000L, 1000000000L, 1000000000L, 1000000000L}, new long[]{1, 1, 1, 1});
    }

    // TODO: print the smallest possible maximum risk on one line,
    // then the acrobat numbers (1-based) from top to bottom on the next
    static void tower(long[] weight, long[] strength) {
        List<Acrobat> acrobats = new ArrayList<>();
        for (int i = 0; i < weight.length; i++) {
            acrobats.add(new Acrobat(weight[i], strength[i], i+1));
        }
        acrobats.sort(Comparator.comparing(Acrobat::getSum));
        long weightAbove = 0;
        long maxRisk = Long.MIN_VALUE;
        for (int i = 0; i < acrobats.size(); i++) {
            long risk = weightAbove - acrobats.get(i).strength;
            maxRisk = Math.max(maxRisk, risk);
            weightAbove+= acrobats.get(i).weight;
        }
        System.out.println(maxRisk);
        for (Acrobat acrobat : acrobats) {
            System.out.printf("%d ", acrobat.id);
        }
        System.out.println();
    }
}