
import org.ioopm.calculator.ast.*;

public class Test {

    public static void testPrinting(String expected, SymbolicExpression e) {
        if (expected.equals("" + e)) {
            System.out.println("Passed: " + e);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }
/*
    public static void testEvaluating(SymbolicExpression expected, SymbolicExpression e) {
        SymbolicExpression r = e.eval();
        if (r.equals(expected)) {
            System.out.println("Passed: " + e + " = " + r);
        }else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }
*/
    public static void testEvaluating(SymbolicExpression expected, SymbolicExpression e, Environment env) {
        SymbolicExpression r = e.eval(env);
        if (r.equals(expected)) {
            System.out.println("Passed: " + e + " = " + r);
        }else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }

    public static void main(String [] args){
        Environment env = new Environment();
        SymbolicExpression v = new Variable("x");
        SymbolicExpression v2 = new Variable("x");

        SymbolicExpression c1 = new Constant(42);
        SymbolicExpression c2 = new Constant(84);
        SymbolicExpression c3 = new Constant(5);
        SymbolicExpression c4 = new Constant(10);
        SymbolicExpression c5 = new Constant(100);
        SymbolicExpression c6 = new Constant(2);
        SymbolicExpression a1 = new Addition(new Constant(5), new Constant(37));
        SymbolicExpression a2 = new Addition(a1,c1);
        SymbolicExpression s1 = new Subtraction(c2, c1);
        SymbolicExpression x = new Multiplication(c3, new Addition(c4, c4));
        SymbolicExpression cos = new Cos(new Constant(0));
        SymbolicExpression a = new Addition(c3, c3);
        SymbolicExpression m = new Multiplication(cos, c6);
        SymbolicExpression d = new Division(m, a);
        
        SymbolicExpression q = new Negation(d);

        SymbolicExpression c7 = new Constant(-0.2);

        SymbolicExpression assignment = new Assignment(q, v);
        assignment.eval(env);
        SymbolicExpression assignment2 = new Assignment(c4, v2);
        assignment2.eval(env);
        System.out.println("v = " + v.hashCode() + "\nv2 = " + v2.hashCode());

        SymbolicExpression m2 = new Multiplication(c4, v);
        SymbolicExpression a3 = new Addition(m2, c3);
        
        
        
        testEvaluating(c1, a1, env);
        testEvaluating(c2, a2, env);
        testEvaluating(c1, s1, env);
        testEvaluating(c5, x, env);
        testEvaluating(c7, q, env);
        testEvaluating(c4, v, env);
        testEvaluating(new Constant(105), a3, env);
    }
}