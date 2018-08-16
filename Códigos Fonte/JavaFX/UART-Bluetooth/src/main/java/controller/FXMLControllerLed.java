package controller;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXComboBox;
import com.jfoenix.controls.JFXToggleButton;
import java.awt.event.MouseEvent;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.beans.binding.Bindings;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import utility.Serial;

public class FXMLControllerLed implements Initializable {

    @FXML
    private JFXComboBox cmbPortas;
    @FXML
    private JFXToggleButton btnConectar;
    @FXML
    private JFXButton btnEsquerda;
    @FXML
    private JFXButton btnDireita;
    @FXML
    private JFXButton btnCima;
    @FXML
    private JFXButton btnBaixo;
    @FXML
    private JFXButton btnHome;

    private final Serial serial = new Serial();
    private final BooleanProperty conexao = new SimpleBooleanProperty(false);


    @FXML
    private void btnUnclick() {
        serial.write("0");
    }

    @FXML
    private void btnClick(Event e) {
        JFXButton btn = (JFXButton) e.getSource();
        switch (btn.getId()) {
            case "btnEsquerda":
                serial.write("4");
                break;
            case "btnDireita":
                serial.write("2");
                break;
            case "btnCima":
                serial.write("1");
                break;
            case "btnBaixo":
                serial.write("3");
                break;
            case "btnHome":
                serial.write("0");
                break;
        }
    }

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        cmbPortas.setItems(FXCollections.observableList(serial.detectPort()));

        cmbPortas.getSelectionModel().selectedItemProperty().addListener(
                (observable, oldValue, newValue) -> {
                    serial.setArdPort((String) newValue);
                });
        cmbPortas.getSelectionModel().selectFirst();
        cmbPortas.disableProperty().bind(conexao);

        btnConectar.selectedProperty().addListener(
                (observable, oldValue, newValue) -> {
                    if (newValue) {
                        if (startSerial()) {
                            btnConectar.setText("Desconectar");
                        } else {
                            btnConectar.setSelected(false);
                        }
                    } else {
                        stopSerial();
                        btnConectar.setText("Conectar");
                    }
                });
        serial.getLine().addListener(
                (observable, oldValue, newValue) -> {
                    System.out.println(newValue);
                });

        btnEsquerda.disableProperty().bind(conexao.not());
        btnDireita.disableProperty().bind(conexao.not());
        btnCima.disableProperty().bind(conexao.not());
        btnBaixo.disableProperty().bind(conexao.not());
        btnHome.disableProperty().bind(conexao.not());
    }

    private boolean startSerial() {
        conexao.set(serial.connect());
        return conexao.get();
    }

    private void stopSerial() {
        if (conexao.get()) {
            serial.disconnect();
            conexao.set(false);
            System.out.println("Finalizando conexão");
        }
    }
}
