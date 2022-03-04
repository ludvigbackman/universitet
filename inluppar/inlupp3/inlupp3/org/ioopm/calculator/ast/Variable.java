package org.ioopm.calculator.ast;
public class Variable extends Atom{
    private String identifier;
    //private SymbolicExpression expression;

    public Variable(String identifier){
        super(identifier);
        this.identifier = identifier;
    }

    public String getName(){
        return "Variable";
    }

    public boolean equals(Object other) {
        if (other instanceof Variable) {
            return this.equals((Variable) other);
        } else {
            return false;
        }
    }

    public boolean equals(Variable other) {
        /// access a private field of other!
        return this.identifier == other.getIdentifier();
    }

    public String toString() {
        return this.identifier;
    }

    public String getIdentifier(){
        return this.identifier;
    }

    public int hashCode(){
        return this.identifier.hashCode();
    }

    private boolean envContains(Environment e){
        for(Variable v : e.keySet()){
            if(v.identifier.equals(this.identifier)){
                return true;
            }
        }
        return false;

    }

    public SymbolicExpression eval(Environment e){
        if(envContains(e)){
            for(Variable v : e.keySet()){
                if(v.getIdentifier().equals(this.identifier)){
                    return e.get(v);
                }
            }
            return e.get(this);
        }
        return this;
    }

}
