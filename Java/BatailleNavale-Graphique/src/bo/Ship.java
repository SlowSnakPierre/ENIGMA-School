package bo;

public class Ship {
    private Coordonnee starting;
    private Coordonnee ending;
    private Coordonnee[] affectedParts;

    private int cbAffected;

    public Ship(Coordonnee starting, int length, boolean isVertical) {
        if (length > 26 || length <= 0) {
            throw new IllegalArgumentException("Invalid length");
        } else if (starting == null) {
            throw new IllegalArgumentException("Invalid starting coordinate");
        } else {
            this.starting = starting;
            if (isVertical) {
                ending = new Coordonnee(length - 1 + starting.getRow(), starting.getColumn());
            } else {
                ending = new Coordonnee(starting.getRow(), length - 1 + starting.getColumn());
            }

            affectedParts = new Coordonnee[length];
            cbAffected = 0;
        }
    }

    @Override
    public String toString() {
        String position;
        int length;
        if (this.starting.getRow() == this.ending.getRow()) {
            position = "horizontal";
            length = this.ending.getColumn() - this.starting.getColumn() + 1;
        } else {
            position = "vertical";
            length = this.ending.getRow() - this.starting.getRow() + 1;
        }

        return "Ship("+this.starting.toString() + ", " + length + ", " + position + ")";
    }

    public Coordonnee getStarting() {
        return starting;
    }

    public Coordonnee getEnding() {
        return ending;
    }

    public boolean contains(Coordonnee coords) {
		return ((coords.getRow() >= starting.getRow() && coords.getRow() <= ending.getRow()) && (coords.getColumn() >= starting.getColumn() && coords.getColumn() <= ending.getColumn()));
    }

    public boolean touch(Ship ship) {
		int thisL_StartingRow = this.starting.getRow();
		int thisL_EndingRow = this.ending.getRow();
		int thisL_StartingColumn = this.starting.getColumn();
		int thisL_EndingColumn = this.ending.getColumn();

		boolean InRowTouch = ((thisL_StartingRow == ship.ending.getRow() + 1)
				|| (thisL_EndingRow == ship.starting.getRow() - 1) || (ship.starting.getRow() == thisL_EndingRow + 1)
				|| (ship.ending.getRow() == thisL_StartingRow - 1));
		boolean InColumnTouch = ((thisL_EndingColumn == ship.starting.getColumn() - 1)
				|| (thisL_StartingColumn == ship.ending.getColumn() + 1) || (ship.ending.getColumn() == thisL_StartingColumn - 1)
				|| (ship.starting.getColumn() == thisL_EndingColumn + 1));
		boolean SameRow = (((thisL_StartingColumn >= ship.starting.getColumn())
				&& (thisL_StartingColumn <= ship.ending.getColumn()))
				|| ((thisL_EndingColumn >= ship.starting.getColumn()) && (thisL_EndingColumn <= ship.ending.getColumn()))
				|| ((ship.starting.getColumn() >= thisL_StartingColumn) && (ship.starting.getColumn() <= thisL_EndingColumn))
				|| ((ship.ending.getColumn() >= thisL_StartingColumn) && (ship.ending.getColumn() <= thisL_EndingColumn)));
		boolean SameColumn = (((thisL_StartingRow >= ship.starting.getRow()) && (thisL_StartingRow <= ship.ending.getRow()))
				|| ((thisL_StartingRow >= ship.starting.getRow()) && (thisL_StartingRow < ship.ending.getRow()))
				|| ((ship.starting.getRow() >= thisL_StartingRow) && (ship.starting.getRow() <= thisL_EndingRow))
				|| ((ship.ending.getRow() >= thisL_StartingRow) && (ship.ending.getRow() <= thisL_EndingRow)));

        return (InRowTouch && SameRow) || (InColumnTouch && SameColumn);
    }

    public boolean overlaps(Ship ship) {
        return (ship.starting.getRow() <= this.starting.getRow() && ship.ending.getRow() >= this.starting.getRow() && ship.starting.getColumn() >= this.starting.getColumn() && ship.starting.getColumn() <= this.ending.getColumn()) || (this.starting.getRow() <= ship.starting.getRow() && this.ending.getRow() >= ship.starting.getRow() && this.starting.getColumn() >= ship.starting.getColumn() && this.starting.getColumn() <= ship.ending.getColumn());
    }

    public boolean receiveShoot(Coordonnee coords) {
		if (this.contains(coords)) {
			for (int i = 0; i < cbAffected; i++) {
				if (affectedParts[i].equals(coords)) {
					return true;
				}
			}
			cbAffected = cbAffected + 1;
			affectedParts[cbAffected - 1] = coords;
			return true;

		}
		return false;
    }

    public boolean isTouched(Coordonnee coords) {
		for (int i = 0; i < cbAffected; i++) {
			if (this.affectedParts[i].equals(coords))
				return true;
		}
		return false;
    }

    public boolean isTouched() {
		return (this.cbAffected != 0);
    }

    public boolean isSunk() {
        return this.affectedParts.length == this.cbAffected;
    }
}
