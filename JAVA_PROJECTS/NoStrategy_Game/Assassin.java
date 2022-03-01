package NoStrategy_Game;

public class Assassin extends Champion {
    public Assassin(String name) { super(name); }

    @Override
    public void attack() {
        System.out.println(">>Knife Attack!!");
    }

    @Override
    public void move() {
        System.out.println(">>Invisible Moving!!");
    }    
}
