package Command_AI;

public class Player extends Character {
    public Player(String name) {
        super(name);
    }

    @Override
    void attack() {
        System.out.println(">> " + getName() + "'s attack!");
    }

    @Override
    void jump() {
        System.out.println(">> " + getName() + "'s jump!");
    }
}
