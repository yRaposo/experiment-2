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
            Dendro dendro01 = new Dendro((long) 01, "Dendro 01", 0);
            Dendro dendro02 = new Dendro((long) 02, "Dendro 02", 0);

            dendroRepository.saveAll(Arrays.asList(dendro01, dendro02));

            logger.info("Dendros carregados no banco de dados");
        };
            
    }
}
