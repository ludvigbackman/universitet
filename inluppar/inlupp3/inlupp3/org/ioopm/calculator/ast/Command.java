package org.ioopm.calculator.ast;

public abstract class Command extends SymbolicExpression{

    public Command(){
        super();
    }

    public SymbolicExpression eval(Environment e){
        throw new RuntimeException("eval() called on command");
    }

    public boolean isCommand(){
        return true;
    }
}