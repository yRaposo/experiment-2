package com.raposo.experiment.service;

import java.util.Arrays;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import com.raposo.experiment.model.Dendro;
import com.raposo.experiment.model.IDendroRepository;

@Configuration
public class LoadDatabase {
    Logger logger = LogManager.getLogger(this.getClass());

    @Bean
    CommandLineRunner initDatabase(IDendroRepository dendroRepository) {
        return args -> {
            Dendro dendro01 = new Dendro("01", "Dendro 01", 0.5, 0.5, 0.5);
            Dendro dendro02 = new Dendro("02", "Dendro 02", 45.5, 45.5, 45.5);
            Dendro dendro03 = new Dendro("03", "Dendro 03", 90.5, 90.5, 90.5);
            Dendro dendro04 = new Dendro("04", "Dendro 04", 180.5, 180.5, 180.5);

            dendroRepository.saveAll(Arrays.asList(dendro01, dendro02, dendro03, dendro04));

            logger.info("Dendros carregados no banco de dados");
        };
            
    }
}
