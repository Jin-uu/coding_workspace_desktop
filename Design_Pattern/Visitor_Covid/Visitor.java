package Visitor_Covid;

public interface Visitor {
    void visit(Severe severe);
    void visit(Mild mild); 
    void visit(Asymp asymp);
}
