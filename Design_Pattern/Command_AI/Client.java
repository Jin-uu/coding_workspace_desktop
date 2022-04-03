package Command_AI;

public class Client {
    public static void main(String[] args) {
        Command Button_A = new AttackCommand();
        Command Button_J = new JumpCommand();

        Character p1 = new Player("Player1");
        Character enemy1 = new Ai_Enemy("Enemy");

        Button_A.execute(p1);
        Button_J.execute(p1);

        Button_A.execute(enemy1);
        Button_J.execute(enemy1);
    }
}
