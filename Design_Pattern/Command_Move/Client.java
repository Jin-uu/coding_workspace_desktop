package Command_Move;

public class Client {
    public static void main(String[] args) {
        Command Button_U = new MoveUpCommand();
        Command Button_R = new MoveRightCommand();
        Command Click_M = new MoveToCommand();
        

        Character p1 = new Player("Player1");
        Character enemy1 = new Ai_Enemy("Enemy");

        Button_U.execute(p1,0,0);
        Button_R.execute(p1,0,0);

        Button_U.execute(enemy1,0,0);
        Button_R.execute(enemy1,0,0);

        Click_M.execute(p1, 3, 5);
        Click_M.execute(enemy1, 5, 7);
    }
}
