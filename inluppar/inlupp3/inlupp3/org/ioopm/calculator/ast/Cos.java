package org.ioopm.calculator.ast;

public class Cos extends Unary{
    private SymbolicExpression expression;
    public Cos(SymbolicExpression expression){
        super(expression);
        this.expression = expression;
    }
    
    public String getName() {
        return "Cos";
    }


    public SymbolicExpression eval(Environment e) {
        SymbolicExpression expression = this.expression.eval(e);
        if (expression.isConstant()) {
            return new Constant(Math.cos(expression.getValue()));
        } else {
            return new Cos(expression);
        }
    }

}
