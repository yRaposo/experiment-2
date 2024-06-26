package com.raposo.experiment.controller;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.util.Assert;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PatchMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.raposo.experiment.model.Dendro;
import com.raposo.experiment.model.Resposta;
import com.raposo.experiment.service.IDendroService;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.transaction.Transactional;

@RestController
@RequestMapping("/api/v1/")
@CrossOrigin(origins = "*")
public class APIDendroController {

    Logger logger = LogManager.getLogger(getClass());

    @Autowired
    IDendroService dendroService;

    @GetMapping("dendro")
    @Transactional
    public ResponseEntity<Object> consultaDendro() {
        logger.info("Consultando Dendro");

        return ResponseEntity.status(HttpStatus.OK).body(dendroService.consultaDendros());
    }

    @GetMapping("dendro/{id}")
    @Transactional
    public ResponseEntity<Object> consultaPorId(@PathVariable Long id) {
        logger.info("Consultando Dendro por id");

        return ResponseEntity.status(HttpStatus.OK).body(dendroService.consultaDendroPorId(id));
    }

    @GetMapping(value = "dendro", params = "nome")
    @Transactional
    public ResponseEntity<Object> consultaPorNome(@RequestParam(value = "nome") String nome) {
        logger.info("Consultando Dendro por nome");

        return ResponseEntity.status(HttpStatus.OK).body(dendroService.consultaDendrosPorNome(nome));
    }

    @PostMapping("dendro")
    @Transactional
    public ResponseEntity<Object> cadastrarDendro(@RequestBody Dendro dendro) {
        logger.info("Cadastrando Dendro");

        return ResponseEntity.status(HttpStatus.OK).body(dendroService.cadastrarDendro(dendro));
    }

    @PatchMapping("dendro/{id}")
    @Transactional
    public ResponseEntity<Object> atualizarDendro(@PathVariable Long id,@RequestBody Dendro dendro) {
        logger.info("Atualizando Dendro");

        Assert.notNull(id, "Id não pode ser nulo");

        dendro.setId(id);

        return ResponseEntity.status(HttpStatus.OK).body(dendroService.atualizarDendro(dendro));
    }

    @DeleteMapping("dendro/{id}")
    @Transactional
    public ResponseEntity<Object> deletarDendro(@PathVariable Long id, HttpServletRequest req) {
        logger.info("Deletando Dendro");

        dendroService.deletarDendro(id);

        Resposta resposta = new Resposta();

        resposta.setMensagem("Dendro deletado com sucesso");
        resposta.setStatus(HttpStatus.OK);
        resposta.setCaminho(req.getRequestURI().toString());
        resposta.setMetodo(req.getMethod());

        return ResponseEntity.status(HttpStatus.OK).body(resposta);
    }
}