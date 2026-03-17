package com.example.controller;

import com.example.Model.signedstudent;
import com.example.labtracker.signedStudentRepo;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;

@Controller
public class LabTrackController {

    final signedStudentRepo repo;

    public LabTrackController(signedStudentRepo repo) {
        this.repo = repo;
    }

    @GetMapping("/sign")
    public String signPage(Model student){
        student.addAttribute("form", new signedstudent());

        return "signPage";
    }

    @PostMapping("/success")
    public String success(@ModelAttribute signedstudent Student, Model student){

        student.addAttribute("form",Student);
        repo.save(Student);

        return "success";
    }

}
