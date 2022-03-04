package org.ioopm.calculator.ast;


public class Division extends Binary {
    private SymbolicExpression lhs;
    private SymbolicExpression rhs;
    public Division(SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs,rhs);
        this.lhs = lhs;
        this.rhs = rhs;
    }
    
    public String getName(){
        return "/";
    }

    public int getPriority(){
        return 100;
    }


    public SymbolicExpression eval(Environment e) {
        SymbolicExpression lhs = this.lhs.eval(e);
        SymbolicExpression rhs = this.rhs.eval(e);
        if(rhs.getValue() == 0){
            throw new RuntimeException("Division with zero");
        }

        if(lhs.isConstant() && rhs.isConstant()){
            return new Constant(lhs.getValue()  / rhs.getValue());
        }
        else {
            return new Division(lhs, rhs);
        }
    }


}
