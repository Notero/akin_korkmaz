package com.example.labtracker;
import com.example.Model.signedstudent;
import org.springframework.data.repository.CrudRepository;

public interface signedStudentRepo extends CrudRepository<signedstudent,Long> {
}
