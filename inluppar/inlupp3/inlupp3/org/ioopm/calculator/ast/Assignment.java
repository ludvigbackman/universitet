package org.ioopm.calculator.ast;


public class Assignment extends Binary{
    private SymbolicExpression lhs;
    private SymbolicExpression rhs;

    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs,rhs);
        this.lhs = lhs;
        this.rhs = rhs;
    }

    public String getName(){
        return "=";
    }
    
    public SymbolicExpression eval(Environment e) {
        SymbolicExpression lhs = this.lhs.eval(e);
        if (rhs.isNamedConstant()){
            throw new IllegalExpressionException("Error: cannot redefine named constant");
        }
        
        e.put(new Variable(this.rhs.toString()), lhs);
        return new Variable(this.rhs.toString());
    }

}
