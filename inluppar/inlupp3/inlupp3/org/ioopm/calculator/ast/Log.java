package org.ioopm.calculator.ast;
public class Log extends Unary {
    private SymbolicExpression expression;
    public Log(SymbolicExpression expression){
        super(expression);
        this.expression = expression;
    }
    
    public String getName() {
        return "Log";
    }


    public SymbolicExpression eval(Environment e) {
        SymbolicExpression expression = this.expression.eval(e);
        if (expression.isConstant()) {
            return new Constant(Math.log(expression.getValue()));
        } else {
            return new Log(expression);
        }
    }

}
