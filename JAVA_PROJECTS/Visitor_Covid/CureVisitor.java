package Visitor_Covid;

public class CureVisitor implements Visitor {

    @Override
    public void visit(Severe severe) {
        System.out.println(">> "+severe.getName()+"님, 즉시 가까운 병원으로 이동해 주세요!");
    }

    @Override
    public void visit(Mild mild) {
        if(mild.getTemperature() < 37.5){
            System.out.println(">> "+mild.getName()+"님, 증상을 지켜보고 악화되면 병원에서 치료를 받으세요.");
        }
        else{
            System.out.println(">> "+mild.getName()+"님, 병원으로 이동해 치료를 받으세요.");
        }       
    }
    
    @Override
    public void visit(Asymp asymp) {
        System.out.println(">> "+asymp.getName()+"님, 집에서 충분한 휴식을 취하세요.");
    }    
}
