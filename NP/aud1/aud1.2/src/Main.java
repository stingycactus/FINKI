import java.util.Scanner;

abstract class Alien {
    private int health;
    private String name;

    public void setHealth(int health) {
        this.health = health;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getHealth() {
        return health;
    }

    public String getName() {
        return name;
    }

    public Alien(int health, String name) {
        this.health = health;
        this.name = name;
    }

    abstract int getDamage();
}

class SnakeAlien extends Alien {
    private static final int DAMAGE = 10;
    public SnakeAlien(int health, String name) {
        super(health, name);
    }

    @Override
    int getDamage() {
        return DAMAGE;
    }
}

class OgreAlien extends Alien {
    private static final int DAMAGE = 6;

    public OgreAlien(int health, String name) {
        super(health, name);
    }

    @Override
    int getDamage() {
        return DAMAGE;
    }
}

class MarshmallowManAlien extends Alien {
    private static final int DAMAGE = 1;

    public MarshmallowManAlien(int health, String name) {
        super(health, name);
    }

    @Override
    int getDamage() {
        return DAMAGE;
    }
}

class AlienPack {
    private Alien[] aliens;

    public AlienPack(int numAliens) {
        aliens = new Alien[numAliens];
    }

    public void addAlien(Alien newAlien, int index) {
        aliens[index] = newAlien;
    }

    public Alien[] getAliens() {
        return aliens;
    }

    public int calculateDamage() {
        int damage = 0;
        for (int i = 0; i < aliens.length; i++) {
            if (aliens[i]==null) {
                continue;
            }
            damage+=aliens[i].getDamage();
        }
        return damage;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        AlienPack pack = new AlienPack(sc.nextInt());
        int n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            String type = sc.next();
            String name = sc.next();
            int health = sc.nextInt();
            int index = sc.nextInt();
            if (type.equals("S")) pack.addAlien(new SnakeAlien(health, name), index);
            else if (type.equals("O")) pack.addAlien(new OgreAlien(health, name), index);
            else pack.addAlien(new MarshmallowManAlien(health, name), index);
        }
        System.out.println("Total damage: " + pack.calculateDamage());
    }
}