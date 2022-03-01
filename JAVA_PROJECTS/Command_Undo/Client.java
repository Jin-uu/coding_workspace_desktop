package Command_Undo;

public class Client {
    public static void main(String[] args) {
        Command Button_U = new MoveUpCommand();
        Command Button_R = new MoveRightCommand();
        Command Click_M = new MoveToCommand();
        

        Character p1 = new Player("Player1");
        Character enemy1 = new Ai_Enemy("Enemy");

        Click_M.execute(p1, 3, 5);
        Click_M.undo(p1);

        Click_M.execute(enemy1, 5, 7);
        Click_M.undo(enemy1);
    }
}

