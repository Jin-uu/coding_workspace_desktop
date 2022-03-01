package Command_GButton;

public class JumpCommand extends Command {
    Player player = new Player();

    @Override
    void execute() {
        player.jump();
    }
    
}
