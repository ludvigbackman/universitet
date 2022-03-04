package org.ioopm.calculator.ast;

public abstract class Atom extends SymbolicExpression {

    public Atom(Object expression){
        super(expression);
    }

    public Atom(){
        super();
    }
  
}
