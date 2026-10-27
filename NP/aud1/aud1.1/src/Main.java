import java.util.Arrays;
import java.util.Scanner;

class Bank {
    private Account[] accounts;
    private int totalAccounts;
    private int capacity;

    public Bank(int capacity) {
        this.capacity = capacity;
        this.accounts = new Account[capacity];
    }

    public double totalAssets() {
        double totalBalance = 0;
        for (int i = 0; i < totalAccounts; i++) {
            totalBalance+=accounts[i].getBalance();
        }
        return totalBalance;
    }

    public void addInterest() {
        for (int i = 0; i < totalAccounts; i++) {
            if(accounts[i] instanceof InterestBearingAccount) {
                ((InterestBearingAccount) accounts[i]).addInterest();
            }
        }
    }

    public void addAccount(Account a) {
        if (totalAccounts==capacity) {
            capacity*=2;
            accounts = Arrays.copyOf(accounts, capacity);
        }
        accounts[totalAccounts++]=a;
    }

}

abstract class Account {
    private String name;
    private static int nextNumber = 1;
    private final int number;
    protected double balance;

    public Account(String name, double balance) {
        this.name = name;
        this.number = nextNumber++;
        this.balance = balance;
    }

    public double getBalance() {
        return balance;
    }

    public void deposit(double amount){
        balance+=amount;
    }

    public void withdraw(double amount){
        balance-=amount;
    }
}

interface InterestBearingAccount {
    void addInterest();
}

class InterestCheckingAccount extends Account implements InterestBearingAccount {
    protected static final double INTEREST_RATE = .03;
    public InterestCheckingAccount(String name, double balance) {
        super(name, balance);
    }

    @Override
    public void addInterest() {
        deposit(balance*INTEREST_RATE);
    }
}

class PlatinumCheckingAccount extends InterestCheckingAccount {
    public PlatinumCheckingAccount(String name, double balance) {
        super(name, balance);
    }

    @Override
    public void addInterest() {
        deposit(balance*(INTEREST_RATE*2));
    }
}

class NonInterestCheckingAccount extends Account {
    public NonInterestCheckingAccount(String name, double balance) {
        super(name, balance);
    }
}



public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Bank bank = new Bank(sc.nextInt());
        int n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            String type = sc.next();
            String name = sc.next();
            double balance = sc.nextDouble();
            if (type.equals("N")) bank.addAccount(new NonInterestCheckingAccount(name, balance));
            else if (type.equals("I")) bank.addAccount(new InterestCheckingAccount(name, balance));
            else bank.addAccount(new PlatinumCheckingAccount(name, balance));
        }
        System.out.printf("Total assets: %.2f%n", bank.totalAssets());
        bank.addInterest();
        System.out.printf("After interest: %.2f%n", bank.totalAssets());
        bank.addInterest();
        System.out.printf("After interest: %.2f%n", bank.totalAssets());
    }
}