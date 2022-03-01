package NoStrategy_Game;

public class Archer extends Champion {
    public Archer(String name) { super(name); }

    @Override
    public void attack() {
        System.out.println(">>Arrow Attack!!");
    }

    @Override
    public void move() {
        System.out.println(">>Rolling!!");
    }    
}
