package Command_Move;

public class Player extends Character {
    public Player(String name) {
        super(name);
    }

    @Override
    void moveUp() {
        this.y++;
        System.out.println(">> " + getName() + " moves to ("+ this.x + " , " + this.y+")");
    }

    @Override
    void moveRight() {
        this.x++;
        System.out.println(">> " + getName() + " moves to ("+ this.x + " , " + this.y+")");
    }

    @Override
    void moveTo(int x, int y) {
        this.x = x;
        this.y = y;
        System.out.println(">> " + getName() + " moves to ("+ this.x + " , " + this.y+")");
    }
}
