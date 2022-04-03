package Visitor_Covid;

public class Client {
    public static void main(String[] args) {
        Patient[] patients = new Patient[] {
            new Severe("박진우", 38.5),
            new Mild("곽규한", 37),
            new Mild("박상준", 38.5),
            new Asymp("홍산", 36.5)
        };

        Visitor mailVisitor = new MailVisitor();
        Visitor cureVisitor = new CureVisitor();

        for(Patient patient : patients){
            patient.getCure(mailVisitor);
            patient.getCure(cureVisitor);
            System.out.println();
        }      
    }    
}
