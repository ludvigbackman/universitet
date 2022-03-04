package org.ioopm.calculator.ast;

public abstract class Binary extends SymbolicExpression{
    private SymbolicExpression lhs = null;
    private SymbolicExpression rhs = null;

    public Binary(SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs,rhs);
        this.lhs = lhs;
        this.rhs = rhs;
    }
    
    public Binary(){
        super();
    }
    
    public String toString(){
        int lp = lhs.getPriority();
        int rp = rhs.getPriority();
        int tp = this.getPriority();
        
        StringBuilder sb = new StringBuilder();
        if (lp < tp && lp != 0)
        {
            sb.append("(" + lhs.toString() + ")");
        }
        else{
            sb.append(lhs.toString());
        }
        sb.append(" " + this.getName() + " ");
        if (rp < tp && rp != 0)
        {
            sb.append("(" + rhs.toString() + ")");
        }
        else{
            sb.append(rhs.toString());
        }
        return sb.toString();
        
    }

    // if(this.priority() > lhs.priority && this.priority > rhs.priority 
}
