package org.ioopm.calculator.parser;

public class SyntaxErrorException extends RuntimeException {
    public SyntaxErrorException() {
        super();
    }
    public SyntaxErrorException(String msg) {
        super(msg);
    }

    public synchronized Throwable fillInStackTrace(){
        return this;
    }
}
