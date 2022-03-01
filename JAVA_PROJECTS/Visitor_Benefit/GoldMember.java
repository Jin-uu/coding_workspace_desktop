package Visitor_Benefit;

public class GoldMember implements Member {

    @Override
    public void getBenefit(Benefit benefit) {
        benefit.getBenefit(this);        
    }
}
