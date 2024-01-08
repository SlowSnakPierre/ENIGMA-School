package bo;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;

public class PlayerWindow extends JFrame {
    private JPanel contentPane;
    private GraphicalGrid shootingGrid;
    private GraphicalNavalGrid defendingGrid;

    public PlayerWindow() {
        this("Player Name", 10);
    }

    public PlayerWindow(String name, int size) {
        this.shootingGrid = new GraphicalGrid(size);
        this.defendingGrid = new GraphicalNavalGrid(size);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setBounds(100, 100, (int) (size * 80), (int) (size * 40));
        contentPane = new JPanel();
        contentPane.setLayout(new GridLayout(1, 2));
        setContentPane(contentPane);

        JPanel panel1_shooting_grid = getShootingGrid();
        panel1_shooting_grid.setBorder(BorderFactory.createTitledBorder(null, "Shooting Grid", TitledBorder.CENTER, TitledBorder.DEFAULT_JUSTIFICATION));
        contentPane.add(panel1_shooting_grid);

        JPanel panel2_shooting_grid = defendingGrid.getGraphicalGrid();
        panel2_shooting_grid.setBorder(BorderFactory.createTitledBorder(null, "Defending Grid", TitledBorder.CENTER, TitledBorder.DEFAULT_JUSTIFICATION));
        contentPane.add(panel2_shooting_grid);
    }

    public GraphicalGrid getShootingGrid() {
        return shootingGrid;
    }

    public GraphicalNavalGrid getDefendingGrid() {
        return defendingGrid;
    }
}
