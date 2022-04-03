package Visitor_Benefit;

public class Client {
    public static void main(String[] args) {
        Member goldMember = new GoldMember();
        Member vipMember = new VipMember();
        Benefit pointBenefit = new PointBenefit();
        Benefit discountBenefit = new DiscountBenefit();

        goldMember.getBenefit(pointBenefit);
        vipMember.getBenefit(pointBenefit);

        goldMember.getBenefit(discountBenefit);
        vipMember.getBenefit(discountBenefit);        
    }
}
