package org.example.springprojects.notes;

public class customException extends RuntimeException {
    public customException(String message) {
        super(message);
    }
}
