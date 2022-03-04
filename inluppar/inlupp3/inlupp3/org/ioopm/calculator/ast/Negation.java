package org.ioopm.calculator.ast;


public class Negation extends Unary {
    private SymbolicExpression expression;

    public Negation(SymbolicExpression expression){
        super(expression); 
        this.expression = expression;
    }

    public String getName(){
        return "Neg";
    }
    

    public SymbolicExpression eval(Environment e) {
        SymbolicExpression expression = this.expression.eval(e);
        if (expression.isConstant()) {
            return new Constant(-1 * expression.getValue());
        } else {
            return new Negation(expression);
        }
    }

}
