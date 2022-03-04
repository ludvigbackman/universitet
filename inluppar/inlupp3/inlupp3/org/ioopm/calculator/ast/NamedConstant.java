package org.ioopm.calculator.ast;

public class NamedConstant extends Atom {
    private String name;
    private double value;
    public NamedConstant(String name, Double value){
        super();
        this.name = name;
        this.value = value;
    }

    public SymbolicExpression eval(Environment env){
        //throw new IllegalExpressionException("eval() called on NamedConstant");
        return new Constant(this.value);
    }

    public double getValue(){
        return value;
    }

    public String toString(){
        return name;
    }

    public String getName(){
        return name;
    }

    public boolean isNamedConstant(){
        return true;
    }


    
}
