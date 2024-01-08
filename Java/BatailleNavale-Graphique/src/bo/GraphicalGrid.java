package bo;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;

class JButtonCoordonnee extends JButton {
    private Coordonnee coords;
    public boolean isLocalEnabled = true;
    public JButtonCoordonnee(Coordonnee coords) {
        this.coords = coords;
    }
    public Coordonnee getCoords() {
        return coords;
    }
    public void setLocalEnabled(boolean isLocalEnabled) {
        this.isLocalEnabled = isLocalEnabled;
    }
}

public class GraphicalGrid extends JPanel implements ActionListener {

    private JButton[][] cases;

    private Coordonnee SelectedCoords;

    public GraphicalGrid(int size) {
        try {
            UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException e) {
            e.printStackTrace();
        }

        this.setLayout(new GridLayout(size + 1, size + 1));

        this.add(new JLabel());

        for (int i = 0; i < size; i++) {
            JLabel lbl = new JLabel(String.valueOf((char) ('A' + i)));
            lbl.setHorizontalAlignment(JLabel.CENTER);
            this.add(lbl);
        }

        cases = new JButton[size][size];

        for (int i = 0; i < size; i++) {
            JLabel lbl = new JLabel(String.valueOf(i + 1));
            lbl.setHorizontalAlignment(JLabel.CENTER);
            this.add(lbl);
            for (int j = 0; j < size; j++) {
                cases[i][j] = new JButtonCoordonnee(new Coordonnee(i, j));
                this.add(cases[i][j]);
                cases[i][j].addActionListener(this);
            }
        }

        SelectedCoords = null;
    }

    public void setColor(Coordonnee coords, Color color) {
        cases[coords.getRow()][coords.getColumn()].setBackground(color);
    }

    public void setColor(Coordonnee startingCoords, Coordonnee endingCoords, Color color) {
        for (int i = startingCoords.getRow(); i <= endingCoords.getRow(); i++) {
            for (int j = startingCoords.getColumn(); j <= endingCoords.getColumn(); j++) {
                cases[i][j].setBackground(color);
            }
        }
    }

    @Override
    public Dimension getPreferredSize() {
        Dimension d = super.getPreferredSize();
        d.setSize(d.width, d.height);
        return d;
    }

    public void setClickActive(boolean active) {
        SwingUtilities.invokeLater(() -> {
            this.setEnabled(false);
            for (JButton[] row : cases) {
                for (JButton button : row) {
                    button.setEnabled(active);
                }
            }
            this.setEnabled(true);
        });
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        JButtonCoordonnee btn = (JButtonCoordonnee) e.getSource();
        this.setClickActive(false);
        SelectedCoords = btn.getCoords();
        synchronized (this) {
            this.notifyAll();
        }
    }

    public synchronized Coordonnee getSelectedCoords() {
        this.setClickActive(true);

        try {
            this.wait();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        return SelectedCoords;
    }
}