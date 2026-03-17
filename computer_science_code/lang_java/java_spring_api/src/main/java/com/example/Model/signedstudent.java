package com.example.Model;
import jakarta.persistence.*;
import java.util.Date;


@Entity
@Table(name = "LabSigns")
public class signedstudent {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;


    public void setId(Long id) {
        this.id = id;
    }

    public Long getId() {
        return id;
    }

    @Column
    private String Firstname;
    @Column
    private String Lastname;
    @Column
    private String Course;
    @Column
    private String Valencia_Mail;
    @Column
    private Date Sign_Date;
    @PrePersist
    protected void onCreate() {
        Sign_Date = new Date();
    }


    public String getFirstname() {
        return Firstname;
    }

    public void setFirstname(String firstname) {
        this.Firstname = firstname;
    }

    public String getLastname() {
        return Lastname;
    }

    public void setLastname(String lastname) {
        this.Lastname = lastname;
    }

    public String getCourse() {
        return Course;
    }

    public void setCourse(String course) {
        this.Course = course;
    }

    public String getValencia_Mail() {
        return Valencia_Mail;
    }

    public void setValencia_Mail(String valencia_Mail) {
        this.Valencia_Mail = valencia_Mail;
    }
}
