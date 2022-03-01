package Command_AI;

public class AttackCommand extends Command {
    @Override
    void execute(Character character) {
        character.attack();
    }    
}
