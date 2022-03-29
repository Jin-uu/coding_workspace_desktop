package Command_GButton;

public class AttackCommand extends Command {
    Player player = new Player();

    @Override
    void execute() {
        player.attack();
    }
    
}
