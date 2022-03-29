package Command_AI;

public abstract class Character {
    private String name;

    public Character(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    abstract void attack();
    abstract void jump();

}
