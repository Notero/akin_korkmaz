package org.example.springprojects.notes;

import jakarta.servlet.http.HttpServletRequest;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;

import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;

@ControllerAdvice
public class RestExceptionHandler {

    @ExceptionHandler({NullPointerException.class})
    public ResponseEntity<apiError> handleNull(HttpServletRequest request, Exception ex) {
        apiError body = new apiError(HttpStatus.INTERNAL_SERVER_ERROR,ex.getMessage(),request.getRequestURI(), System.currentTimeMillis());
        return new ResponseEntity<>(body, HttpStatus.INTERNAL_SERVER_ERROR);
    }

    @ExceptionHandler({customException.class})
    public ResponseEntity<apiError> handleRuntime(HttpServletRequest request, Exception ex) {
        apiError body = new apiError(HttpStatus.INTERNAL_SERVER_ERROR,ex.getMessage(),request.getRequestURI(), System.currentTimeMillis());
        return new ResponseEntity<>(body, HttpStatus.INTERNAL_SERVER_ERROR);
    }


}
