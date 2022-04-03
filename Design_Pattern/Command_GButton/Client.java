package Command_GButton;


public class Client {
    public static void main(String[] args) {
        Command Button_A = new AttackCommand();
        Command Button_J = new JumpCommand();
        
        Button_A.execute();
        Button_J.execute();
    }
}
