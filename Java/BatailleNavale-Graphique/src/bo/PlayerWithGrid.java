package bo;

public abstract class PlayerWithGrid extends Player {
    private NavalGrid grid;

    public PlayerWithGrid(NavalGrid grid, String name) {
        super(grid.getSize(), name);
        this.grid = grid;
    }

    public PlayerWithGrid(NavalGrid grid) {
        super(grid.getSize());
        this.grid = grid;
    }

    public int receiveAttack(Coordonnee coords) {
        grid.receiveShoot(coords);

        if (grid.loose()) {
            return Player.GAMEOVER;
        }

        if (grid.isSunk(coords)) {
            return Player.SUNK;
        }

        if (grid.isTouched(coords)) {
            return Player.TOUCHED;
        }

        return Player.MISSED;
    }

    public NavalGrid getGrid() {
        return grid;
    }
}
