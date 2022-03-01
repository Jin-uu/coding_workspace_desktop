package Command_Undo;

public class MoveToCommand extends Command {
    @Override
    void execute(Character character, int x, int y) {
        character.moveTo(x, y);
    }
}
