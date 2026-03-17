package com.example.guiweb;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;

@Controller
public class WebController {

    @Autowired
    Element_Repository repo;

    @GetMapping("/")
    public String StartPage(){
        return "Start";
    }

    @GetMapping("/create")
    public String create(Model model){

        model.addAttribute("submittedform", new element());

        return "Create";
    }

    @PostMapping("/success")
    public String Success(@ModelAttribute element Element, Model model){
        model.addAttribute("submittedform", Element);
        repo.save(Element);

        return "Success";
    }



}
