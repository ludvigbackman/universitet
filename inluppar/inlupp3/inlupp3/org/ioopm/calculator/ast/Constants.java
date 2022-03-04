package org.ioopm.calculator.ast;

import java.util.*;

public class Constants {
    public static final HashMap<String, Double> namedConstants = new HashMap<>();

    static {
        Constants.namedConstants.put("pi", Math.PI);
        Constants.namedConstants.put("e",  Math.E);
        Constants.namedConstants.put("L", 6.022140857 * Math.pow(10,23));
        
    }
}