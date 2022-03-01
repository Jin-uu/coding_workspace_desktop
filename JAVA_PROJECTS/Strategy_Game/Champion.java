package Strategy_Game;

public abstract class Champion {
    private String name;
    private AttackStrategy attackStrategy;
    private MovingStrategy movingStrategy;

    public Champion(String name) { this.name = name; }
    public String getName() { return name; }
    public void attack() { attackStrategy.attack(); }
    public void move() { movingStrategy.move(); }

    public void setAttackStrategy( AttackStrategy attackStrategy ){
        this.attackStrategy = attackStrategy;
    }    
    public void setMovingStrategy( MovingStrategy movingStrategy){
        this.movingStrategy = movingStrategy;
    }    
}
