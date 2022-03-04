package org.ioopm.calculator.ast;

public abstract class SymbolicExpression {
    private String[] subExpressions;
    
    public SymbolicExpression(Object... subExpressions) {
        this.subExpressions = new String[subExpressions.length];
        for (int i = 0; i < subExpressions.length; ++i) {
            this.subExpressions[i] = subExpressions[i].toString();
        }
    }

    public SymbolicExpression(){

    }


    public boolean isConstant(){
        return false;
        // need another isConstant method "somewhere else"
    }

    public String getName(){
        throw new RuntimeException("getName() called on expression with no operator");
    }

    public boolean equals(){
        throw new RuntimeException("equals() called on expression with no evaluated value");
    }

    public double getValue(){
        throw new RuntimeException("getValue() called on expression with no value");
    }

    public int getPriority(){
        return 0;
    }

    public boolean isCommand(){
        return false;
    }

    public boolean isNamedConstant(){
        return false;
    }

    
    
    public abstract SymbolicExpression eval(Environment e);


    /// Returns e.g., "Constant(42)" if name is "Constant" and subExpressions is ["42"]
    public String toString(/*String msg*/) {
        StringBuilder sb = new StringBuilder();
        sb.append(this.getName());
        sb.append("(");
        for (int i = 0; i < this.subExpressions.length; ++i) {
            sb.append(this.subExpressions[i]);
            if (i + 1 < subExpressions.length) {
                sb.append(" " + this.getName() + " ");
            }
        }
        sb.append(")");
        return sb.toString(); 
    }
}