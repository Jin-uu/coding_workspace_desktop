package Command_Move;

public class MoveRightCommand extends Command {

    @Override
    void execute(Character character, int x, int y) {
        character.moveRight();
    }    
}
