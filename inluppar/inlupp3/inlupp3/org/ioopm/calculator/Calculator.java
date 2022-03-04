package org.ioopm.calculator;

import java.io.IOException;
import java.util.InputMismatchException;
import java.util.Scanner;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

public class Calculator {
    private final Environment environment = new Environment();
    private final CalculatorParser parser = new CalculatorParser();

    private boolean running = true;

    public Calculator() {

    }

    public void printVars(Environment environment) {
        if (!environment.isEmpty()) {
            for (Variable v : environment.keySet()) {
                System.out.println(v.getIdentifier() + " = " + environment.get(v));
            }
            return;
        }
        System.out.println("No variables in the environment!");
    }

    public void run() throws IOException {
        System.out.println("Welcome to the parser!");
        Variable ans = new Variable("ans");
        int expCount = 0;
        int fullyEvaluated = 0;
        while (running) {
            System.out.print("Please enter an expression: ");
            String input = System.console().readLine();
            SymbolicExpression expression;
            try{
                expression = parser.parse(input, environment);
            } catch(SyntaxErrorException | IllegalExpressionException e){
                e.printStackTrace();
                continue;
            }
            if (expression.isCommand()) {
                if (expression instanceof Quit) {
                    System.out.println("Thank you, come again!\n" + "Total expressions entered: " + expCount + "\n"
                            + "Fully evaluated expressions: " + fullyEvaluated);
                    running = false;
                } else if (expression instanceof Vars) {
                    printVars(environment);
                } else {
                    environment.clear();
                }
            } else {
                SymbolicExpression newexp = expression.eval(this.environment);
                environment.put(ans, newexp.eval(this.environment));
                System.out.println("" + newexp.eval(this.environment));
                if (newexp.eval(environment).isConstant()) {
                    fullyEvaluated++;
                }
                expCount++;
                // System.out.println("" + environment.get(new Variable("x")).hashCode());
            }

        }
    }

    

    public static void main(String[] args) throws IOException {
        Calculator calc = new Calculator();
        calc.run();

    }

}