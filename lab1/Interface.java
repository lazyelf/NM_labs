package com.lazyelf;

import com.lazyelf.errorsAnalysis.ErrorsAnalysis;

import javax.swing.*;
import java.awt.event.*;

public class Interface extends JDialog {
    //Elements of container
    private JPanel contentPane;
    private JTextField f_x1;
    private JTextField f_x2;
    private JTextField f_x3;
    private JTextField amount1;
    private JTextField amount2;
    private JTextField amount3;
    private JButton calculateButton;
    private JTextArea f_value1;
    private JTextArea absolute1;
    private JTextArea relate1;
    private JTextArea f_value2;
    private JTextArea absolute2;
    private JTextArea relate2;

    public Interface() {
        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(calculateButton);

        calculateButton.addActionListener(e -> onOK());

        // call onCancel() when cross is clicked
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                onCancel();
            }
        });

        // call onCancel() on ESCAPE
        contentPane.registerKeyboardAction(e -> onCancel(),
                KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0),
                JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);
    }

    /**Press on button --> calculate errors*/
    private void onOK() {

        //Containers for saving values of arguments and amount of exact digits
        double x1, x2, x3;
        int amount1_, amount2_, amount3_;

        //Task b
        final double dx = 20 * 0.001;

        //Get values from form
        x1 = Double.parseDouble(f_x1.getText());
        x2 = Double.parseDouble(f_x2.getText());
        x3 = Double.parseDouble(f_x3.getText());
        amount1_ = Integer.parseInt(amount1.getText());
        amount2_ = Integer.parseInt(amount2.getText());
        amount3_ = Integer.parseInt(amount3.getText());

        //Calculate errors
        ErrorsAnalysis a = new ErrorsAnalysis(x1, amount1_, x2, amount2_, x3, amount3_);
        ErrorsAnalysis b = new ErrorsAnalysis(x1, x2, x3, dx);

        //Make string to show on form
        String value = String.format("%.3f", a.getFValue());
        String errorA1 = String.format("%.3e", a.getAbsolute());
        String errorA2 = String.format("%.3e", b.getAbsolute());
        String errorR1 = String.format("%.3e", a.getRelate());
        String errorR2 = String.format("%.3e", b.getRelate());


        //Show results
        f_value1.append(value);
        absolute1.append(errorA1);
        relate1.append(errorR1);
        f_value2.append(value);
        absolute2.append(errorA2);
        relate2.append(errorR2);


        //dispose();
    }

    private void onCancel() {
        dispose();
    }
}
