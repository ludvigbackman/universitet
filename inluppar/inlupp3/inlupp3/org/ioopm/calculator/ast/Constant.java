package org.ioopm.calculator.ast;

public class Constant extends Atom{
    private double value;

    public Constant(Double value){
        super(value);
        this.value = value;
    }

    public Constant(Integer value){
        super(value);
        this.value = (double) value;
    }
    
    public boolean isConstant(){
        return true;
    }

    public boolean equals(Object other) {
        if (other instanceof Constant) {
            return this.equals((Constant) other);
        } else {
            return false;
        }
    }

    public boolean equals(Constant other) {
        /// access a private field of other!
        return this.value == other.getValue();
    }

    public double getValue(){
        return this.value;
    }

    public String getName(){
        return "Constant";
    }

    public String toString() {
        return String.valueOf(this.value);
    }

    

    public SymbolicExpression eval(Environment e){
        return new Constant(this.value);
    }

}

