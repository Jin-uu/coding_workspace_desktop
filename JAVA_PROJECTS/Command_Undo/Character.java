package Command_Undo;

public abstract class Character {
    private String name;
    protected int x,y;
    protected int before_x, before_y;

    public Character(String name) {
        this.name = name;
        this.x=0;
        this.y=0;
        this.before_x=0;
        this.before_y=0;
    }

    public String getName() {
        return name;
    }

    abstract void moveUp();
    abstract void moveRight();
    abstract void moveTo(int x, int y);
}
