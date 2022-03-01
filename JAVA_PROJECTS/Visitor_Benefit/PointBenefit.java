package Visitor_Benefit;

public class PointBenefit implements Benefit {

    @Override
    public void getBenefit(GoldMember member) {
        System.out.println(">> Discount for Gold Member");        
    }

    @Override
    public void getBenefit(VipMember member) {
        System.out.println(">> Discount for Vip Member");                
    }
    
}
