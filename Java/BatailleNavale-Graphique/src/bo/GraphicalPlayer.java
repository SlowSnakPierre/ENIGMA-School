package bo;

import javax.swing.*;
import java.awt.*;

public class GraphicalPlayer extends PlayerWithGrid {
    private final GraphicalGrid shootingGrid;

    public GraphicalPlayer(GraphicalNavalGrid defendingGrid, GraphicalGrid attackingGrid, String name) {
        super(defendingGrid, name);
        this.shootingGrid = attackingGrid;
    }

    public Coordonnee chooseAttack() {
        return this.shootingGrid.getSelectedCoords();
    }

    protected void returnDefense(Coordonnee coords, int status) {
        switch (status) {
            case TOUCHED:
                JOptionPane.showMessageDialog(shootingGrid, "You have been hit at " + coords);
                break;
            case SUNK:
                JOptionPane.showMessageDialog(shootingGrid, "You have been sunk at " + coords);
                break;
            case GAMEOVER:
                JOptionPane.showMessageDialog(shootingGrid, "You have lost because you don't have any more ships after the attack at " + coords);
        }
    }

    protected void returnAttack(Coordonnee coords, int status) {
        Color color = status != MISSED ? Color.RED : Color.BLUE;
        shootingGrid.setColor(coords, color);

        switch (status) {
            case TOUCHED:
                JOptionPane.showMessageDialog(shootingGrid, "You have hit a ship at " + coords);
                break;
            case SUNK:
                JOptionPane.showMessageDialog(shootingGrid, "You have sunk a ship after a shoot at " + coords);
                break;
            case GAMEOVER:
                JOptionPane.showMessageDialog(shootingGrid, "You have won !");
        }
    }
}
