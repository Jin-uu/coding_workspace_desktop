package Visitor_Covid;

public class MailVisitor implements Visitor {

    @Override
    public void visit(Severe severe) {
        System.out.println(">> " + severe.getName() + "님의 위험도 분류는 <중증> 입니다.");
    }

    @Override
    public void visit(Mild mild) {
        System.out.println(">> " + mild.getName() + "님의 위험도 분류는 <경증> 입니다.");
    }

    @Override
    public void visit(Asymp asymp) {
        System.out.println(">> " + asymp.getName() + "님의 위험도 분류는 <무증상> 입니다.");
    }
}
