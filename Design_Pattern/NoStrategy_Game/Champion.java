package NoStrategy_Game;

public abstract class Champion {
    private String name;
    
    Champion(String name){ this.name = name; }
    public String getName() { return name; }

    public abstract void attack();
    public abstract void move();
}

