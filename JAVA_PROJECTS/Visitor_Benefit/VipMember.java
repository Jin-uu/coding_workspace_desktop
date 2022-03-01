package Visitor_Benefit;

public class VipMember implements Member{

    @Override
    public void getBenefit(Benefit benefit) {
        benefit.getBenefit(this);        
    }
}
