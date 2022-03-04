package org.ioopm.calculator.ast;
public class Subtraction extends Binary{
    private SymbolicExpression lhs = null;
    private SymbolicExpression rhs = null;

    public Subtraction(SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs,rhs);
        this.lhs = lhs;
        this.rhs = rhs;
    }

    public String getName(){
        return "-";
    }

    public int getPriority(){
        return 50;
    }

    public SymbolicExpression eval(Environment e) {
        SymbolicExpression lhs = this.lhs.eval(e);
        SymbolicExpression rhs = this.rhs.eval(e);
        if(lhs.isConstant() && rhs.isConstant()){
            return new Constant(lhs.getValue()-rhs.getValue());
        }
        else {
            return new Subtraction(lhs, rhs);
        }
    }
    
}
