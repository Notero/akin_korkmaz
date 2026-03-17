package org.example.springprojects.notes;
import jakarta.validation.Valid;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.support.ServletUriComponentsBuilder;

import java.util.List;

@RestController
@RequestMapping("/api/notes")
public class NoteController {
    public final repo noteRepo;

    public NoteController(repo noteRepo) {
        this.noteRepo = noteRepo;
    }

    @PostMapping
    public ResponseEntity<Note> create(@Valid @RequestBody Note note) {
        Note newNote = noteRepo.create(note);
        var uri = ServletUriComponentsBuilder
                .fromCurrentRequest()
                .path("/{id}")
                .buildAndExpand(newNote.getId()).toUri();
        return ResponseEntity.created(uri).body(newNote);
    }

    @GetMapping
    public ResponseEntity<List<Note>> getAll() {
        List<Note> notes = noteRepo.findAll();
        return new ResponseEntity<>(notes, HttpStatus.OK);
    }

    @GetMapping("/{id}")
    public Note findTheId(@PathVariable Long id) {
        return noteRepo.findById(id).orElseThrow(()-> new customException("Note not found"));
    }


    @PutMapping("/{id}")
    public Note update(@PathVariable Long id, @Valid @RequestBody Note note) {
        return noteRepo.update(id, note).orElseThrow(() -> new customException("Note to update couldn't be Found"));
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(@PathVariable Long id) {
        return noteRepo.delete(id) ? ResponseEntity.noContent().build() : ResponseEntity.notFound().build();
    }


}
