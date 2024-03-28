package com.raposo.experiment.service;

import java.util.List;
import java.util.Optional;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.raposo.experiment.model.Dendro;
import com.raposo.experiment.model.IDendroRepository;

@Service
public class DendroService implements IDendroService {

    public Logger getLogger() {
        return this.logger;
    }

    public void setLogger(Logger logger) {
        this.logger = logger;
    }

    public IDendroRepository getDendroRepository() {
        return this.dendroRepository;
    }

    public void setDendroRepository(IDendroRepository dendroRepository) {
        this.dendroRepository = dendroRepository;
    }

    Logger logger = LogManager.getLogger(getClass());

    @Autowired
    IDendroRepository dendroRepository;

    @Override
    public List<Dendro> consultaDendros() {
        logger.info("Consultando todos os Dendros");

        return dendroRepository.findAll();
    }

    @Override
    public List<Dendro> consultaDendrosPorNome(String nome) {
        logger.info("Consultando Dendros por nome");

        return dendroRepository.findByName(nome);
    }

    @Override
    public Optional<Dendro> consultaDendroPorId(Long id) {
        logger.info("Consultando Dendro por id");

        return dendroRepository.findById(id);
    }

    @Override
    public Optional<Dendro> cadastrarDendro(Dendro dendro) {
        logger.info("Cadastrando Dendro");

        return Optional.of(dendroRepository.save(dendro));
    }

    @Override
    public Optional<Dendro> atualizarDendro(Dendro dendro) {
        logger.info("Atualizando Dendro");

        return dendroRepository.findById(dendro.getId()).map(d -> {
            d.setPosition(dendro.getPosition());
            
            return dendroRepository.save(d);
        });
    }

    @Override
    public void deletarDendro(Long id) {
        logger.info("Deletando Dendro");

        dendroRepository.deleteById(id);
    }
}
