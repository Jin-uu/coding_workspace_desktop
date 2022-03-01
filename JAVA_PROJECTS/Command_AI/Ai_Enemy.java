package Command_AI;

public class Ai_Enemy extends Character {
    public Ai_Enemy(String name) {
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
