// src/main/java/com/example/demo/notes/Note.java
package org.example.springprojects.notes;
import com.fasterxml.jackson.annotation.JsonProperty;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;
import lombok.Getter;
import lombok.NoArgsConstructor;

import java.time.Instant;

@Getter
@NoArgsConstructor // needed for Jackson
public class Note {

    @JsonProperty(access = JsonProperty.Access.READ_ONLY)
    private Long id;

    @NotBlank(message = "title is required")
    @Size(max = 100, message = "title must be at most 100 characters")
    private String title;

    @Size(max = 10_000, message = "content must be at most 10000 characters")
    private String content;

    @JsonProperty(access = JsonProperty.Access.READ_ONLY)
    private Instant createdAt;

    @JsonProperty(access = JsonProperty.Access.READ_ONLY)
    private Instant updatedAt;

    // Package-private setters so only your repo/service can set them
    void setId(Long id) { this.id = id; }
    void setCreatedAt() { this.createdAt = Instant.now(); }
    void setUpdatedAt() { this.updatedAt = Instant.now(); }

    public void changeTitle(String newTitle) {
        this.title = newTitle;
        this.updatedAt = Instant.now();
    }

    public void changeContent(String newContent) {
        this.content = newContent;
        this.updatedAt = Instant.now();
    }
}
