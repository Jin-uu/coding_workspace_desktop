package NoStrategy_Game;

public class Client {
    public static void main(String[] args) {
        Champion archer = new Archer("archer");
        Champion assassin = new Assassin("assassin");

        System.out.println("\nMy Champion is "+archer.getName());
        archer.move();
        archer.attack();

        System.out.println("\nMy Champion is "+assassin.getName());
        assassin.move();
        assassin.attack();
    }
}

