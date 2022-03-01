package Command_AI;

public class JumpCommand extends Command {
    @Override
    void execute(Character character) {
        character.jump();
    }
}
