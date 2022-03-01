package Command_Undo;

public class MoveUpCommand extends Command {

    @Override
    void execute(Character character, int x, int y) {
        character.moveUp();
    }
}
