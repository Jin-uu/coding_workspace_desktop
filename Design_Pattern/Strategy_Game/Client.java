package Strategy_Game;

public class Client {
    public static void main(String[] args) {
        Champion archer = new Archer("archer1");
        Champion assassin = new Assassin("assassin1");

        archer.setMovingStrategy(new RollingStrategy());
        archer.setAttackStrategy(new ArrowStrategy());

        assassin.setMovingStrategy(new InvisibleStrategy());
        assassin.setAttackStrategy(new KnifeStrategy());

        System.out.println("\nMy Champion is "+archer.getName());
        archer.move();
        archer.attack();

        System.out.println("\nMy Champion is "+assassin.getName());
        assassin.move();
        assassin.attack();
    }
}

