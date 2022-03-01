package Command_Move;

public abstract class Character {
    private String name;
    protected int x,y;

    public Character(String name) {
        this.name = name;
        this.x=0;
        this.y=0;
    }

    public String getName() {
        return name;
    }

    abstract void moveUp();
    abstract void moveRight();
    abstract void moveTo(int x, int y);
}
