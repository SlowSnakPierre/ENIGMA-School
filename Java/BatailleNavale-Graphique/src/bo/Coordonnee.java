package bo;

public class Coordonnee {
    private int row;
    private int column;

    public Coordonnee(int row, int column) {
        if (row < 0 || row > 25 || column < 0 || column > 25) {
            throw new IllegalArgumentException("The row " + row + " and column " + column + " must be between 0 and 25");
        }
        this.row = row;
        this.column = column;
    }

    public Coordonnee(String s) {
        if (s.equals("")) {
            throw new IllegalArgumentException("The string \"" + s + "\" must not be empty");
        }

        if (s.length() > 3  || s.length() < 2) {
            throw new IllegalArgumentException("The string \"" + s + "\" must be between 2 and 3 characters long");
        }

        if (s.charAt(0) < 'A' || s.charAt(0) > 'Z') {
            throw new IllegalArgumentException("The first character of the string \"" + s + "\" must be between A and Z");
        }

        try {
            Integer.parseInt(s.substring(1));
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("The second and third characters of the string \"" + s + "\" must be integers");
        }

        if (Integer.parseInt(s.substring(1)) > 26 || Integer.parseInt(s.substring(1)) < 1) {
            throw new IllegalArgumentException("The second and third characters of the string \"" + s + "\" must be between 1 and 26");
        }

        this.column = s.charAt(0) - 'A';
        this.row = Integer.parseInt(s.substring(1)) - 1;
    }

    @Override
    public String toString() {
        return "" + (char)(this.column + 65) + (int)(this.row + 1);
    }

    public int getRow() {
        return this.row;
    }

    public int getColumn() {
        return this.column;
    }

    public boolean equals(Object obj) {
        if (!(obj instanceof Coordonnee)) {
            return false;
        }

        Coordonnee coords = (Coordonnee) obj;
        return (coords.row == this.row && coords.column == this.column);
    }

    public boolean neighbor(Coordonnee coords) {
        return (((this.column == coords.column) && ((this.row == coords.row + 1) || (this.row == coords.row - 1))) || ((this.row == coords.row) && ((this.column == coords.column+1) || (this.column == coords.column - 1))));
    }

    public int compareTo(Coordonnee coords) {
		if ((this.row == coords.row) && (this.column == coords.column)) {
            return 0;
        } else if (this.row != coords.row && this.column == coords.column) {
			return this.row - coords.row;
		} else {
			return this.column - coords.column;
        }
	}
}
