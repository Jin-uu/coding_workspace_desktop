package Visitor_Covid;

public class Severe implements Patient {
    private final String name;
    private final double temperature;

    public Severe(String name, double temperature){
        this.name = name;
        this.temperature = temperature;
    }

    public String getName(){ return name; }
    public double getTemperature() { return temperature; }

    @Override
    public void getCure(Visitor visitor) {
        visitor.visit(this); 
    }
}
