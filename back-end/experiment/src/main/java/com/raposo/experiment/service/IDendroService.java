package com.raposo.experiment.service;

import java.util.List;
import java.util.Optional;

import com.raposo.experiment.model.Dendro;

public interface IDendroService {

    public List<Dendro> consultaDendros();

    public List<Dendro> consultaDendrosPorNome(String nome);

    public Optional<Dendro> consultaDendroPorId(Long id);

    public Optional<Dendro> cadastrarDendro(Dendro dendro);

    public Optional<Dendro> atualizarDendro(Dendro dendro);

    public void deletarDendro(Long id);
}
