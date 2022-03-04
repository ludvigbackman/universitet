package org.ioopm.calculator.ast;
public abstract class Unary extends SymbolicExpression{
    private SymbolicExpression expression;

    public Unary(SymbolicExpression expression){
        super(expression);
        this.expression = expression;
        
    }


    public String toString(){
        return this.getName() + "(" + this.expression.toString() + ")";
    }



}
