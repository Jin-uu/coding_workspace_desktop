package COR_Dispenser;

import java.util.Scanner;

public class ChainOfResponsibility {
    private DispenseChain c1;

    public ChainOfResponsibility() {
        this.c1 = new Dollar100Dispenser();
        DispenseChain c2 = new Dollar50Dispenser();
        DispenseChain c3 = new Dollar10Dispenser();

        c1.setNextChain(c2);
        c2.setNextChain(c3);
    }

    public static void main(String[] args) {
        ChainOfResponsibility atmDispenser = new ChainOfResponsibility();
        Scanner input = null;
        while (true) {
            int amount = 0;
            System.out.printf("Enter amount to dispense >> ");

            input = new Scanner(System.in);
            amount = input.nextInt();

            if (amount == 0)
                break;
            if (amount % 10 != 0) {
                System.out.println("Amount should be multiple of 10!");
                continue;
            }
            atmDispenser.c1.dispense(new Currency(amount));
        }

        input.close();
    }
}

