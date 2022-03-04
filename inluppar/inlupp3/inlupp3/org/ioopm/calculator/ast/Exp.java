package org.ioopm.calculator.ast;

public class Exp extends Unary {
    private SymbolicExpression expression;
    public Exp(SymbolicExpression expression){
        super(expression);
        this.expression = expression;
    }

    public String getName(){
        return "Exp";
    }

    public int getPriority(){
        return 150;
    }


    public SymbolicExpression eval(Environment e) {
        SymbolicExpression expression = this.expression.eval(e);
        if (expression.isConstant()) {
            return new Constant(Math.exp(expression.getValue()));
        } else {
            return new Exp(expression);
        }
    }
}
