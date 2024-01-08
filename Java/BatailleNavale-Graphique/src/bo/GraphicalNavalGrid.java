package bo;

import java.awt.*;

public class GraphicalNavalGrid extends NavalGrid {
    private GraphicalGrid grid;

    public GraphicalNavalGrid(int size) {
        super(size, 5);
        this.grid = new GraphicalGrid(size);
        this.grid.setClickActive(false);

    }

    public GraphicalGrid getGraphicalGrid() {
        return grid;
    }

    public boolean addShip(Ship ship) {
        if (super.addShip(ship)) {
            this.grid.setColor(ship.getStarting(), ship.getEnding(), Color.GRAY);
            return true;
        } else {
            return false;
        }
    }

    public boolean receiveShoot(Coordonnee coords) {
        if (super.receiveShoot(coords)) {
            this.grid.setColor(coords, Color.RED);
            return true;
        } else {
            this.grid.setColor(coords, Color.GREEN);
            return false;
        }
    }
}
