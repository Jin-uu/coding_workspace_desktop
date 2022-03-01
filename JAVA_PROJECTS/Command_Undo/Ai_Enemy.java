package Command_Undo;

public class Ai_Enemy extends Character {
    public Ai_Enemy(String name) {
        super(name);
    }

    @Override
    void moveUp() {
        this.before_y = this.y;
        this.y++;
        System.out.println(">> " + getName() + " moves to ("+ this.x + " , " + this.y+")");
    }

    @Override
    void moveRight() {
        this.before_x = this.x;
        this.x++;
        System.out.println(">> " + getName() + " moves to ("+ this.x + " , " + this.y+")");
    }

    @Override
    void moveTo(int x, int y) {
        this.before_x = this.x;
        this.before_y = this.y;
        this.x = x;
        this.y = y;
        System.out.println(">> " + getName() + " moves to ("+ this.x + " , " + this.y+")");
    }
}
