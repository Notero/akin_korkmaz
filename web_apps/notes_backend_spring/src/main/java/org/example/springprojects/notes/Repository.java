package org.example.springprojects.notes;

import org.springframework.stereotype.Repository;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;

@Repository
public final class repo {

    private final Map<Long,Note> storage = new ConcurrentHashMap<>();
    private final AtomicLong idIncremental = new AtomicLong(0);

    private Long generateId() {return idIncremental.incrementAndGet();}

    public Note create(Note note) {
        Objects.requireNonNull(note, "note must not be null");
        note.setId(generateId());
        note.setCreatedAt();
        note.setUpdatedAt();
        storage.put(note.getId(), note);
        return note;
    }

    public Optional<Note> findById(Long id) {
        return Optional.ofNullable(storage.get(id));
    }

    public List<Note> findAll() {
        List<Note> getAll = new ArrayList<>(storage.values());
        getAll.sort(Comparator.comparing(Note::getCreatedAt).reversed());
        return getAll;
    }

    public Optional<Note> update(Long id, Note note) {
        Objects.requireNonNull(note, "note must not be null");
        if (!storage.containsKey(id)) {
            return Optional.empty();
        }
        Note oldNote = storage.get(id);
        oldNote.changeContent(note.getContent());
        oldNote.changeTitle(note.getTitle());
        return Optional.of(oldNote);
    }

    public boolean delete(Long id) {
        return storage.remove(id) != null;
    }

}
