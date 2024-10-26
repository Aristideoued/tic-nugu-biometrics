package com.neurotec.samples.model;

import lombok.*;

import javax.persistence.*;
import java.awt.*;
import java.io.Serial;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@ToString
public class InitiationKit extends CommonEntity{
    @Serial
    private static final long serialVersionUID = 7348866761268888347L;

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String observations;

    @ManyToOne
    public Kit kit;
    @ManyToOne(cascade = CascadeType.ALL)
    public Ecole ecole;
}
