package Command_Undo;

public abstract class Command {    
    abstract void execute(Character character, int x, int y);
    
    public void undo(Character character) {
        character.moveTo(character.before_x, character.before_y);
    }
}
