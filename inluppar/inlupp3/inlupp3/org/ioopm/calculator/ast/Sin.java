package org.ioopm.calculator.ast;
public class Sin extends Unary {
    private SymbolicExpression expression;

    public Sin(SymbolicExpression expression){
        super(expression);
        this.expression = expression;
    }
    
    public String getName() {
        return "Sin";
    }

    public SymbolicExpression eval(Environment e) {
        SymbolicExpression expression = this.expression.eval(e);
        if (expression.isConstant()) {
            return new Constant(Math.sin(expression.getValue()));
        } else {
            return new Sin(expression);
        }
    }

}
