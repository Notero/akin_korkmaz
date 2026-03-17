package org.example.springprojects.notes;

public record apiError(
        org.springframework.http.HttpStatus status,
        String content,
        String path,
        long timestamp
) {
}
