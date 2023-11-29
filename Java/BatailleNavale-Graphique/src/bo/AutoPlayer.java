package bo;

public class AutoPlayer extends PlayerWithGrid {
    public AutoPlayer(NavalGrid grid, String name) {
        super(grid, name);
    }

    public AutoPlayer(NavalGrid grid) {
        super(grid);
    }


    protected void returnAttack(Coordonnee coords, int status) {
        System.out.println("\nAttack Result :");
        if (status == TOUCHED) {
            System.out.println(this.getName() + " >>>>> Has hit a ship after an attack at \"" + coords + "\" !");
        } else if (status == SUNK) {
            System.out.println(this.getName() + " >>>>> Has sunk a ship after an attack at \"" + coords + "\" !");
        } else if (status == MISSED) {
            System.out.println(this.getName() + " >>>>> Has missed a shoot at \"" + coords + "\" !");
        } else {
            System.out.println(this.getName() + " >>>>> Congratulations, you have won the game !");
        }
    }

    protected void returnDefense(Coordonnee coords, int status) {
        System.out.println(this.getGrid());
        System.out.println("\nDefense Result :");
        if (status == TOUCHED) {
            System.out.println(this.getName() + " >>>>> Has hit one of your ship after an attack at \"" + coords + "\" !");
        } else if (status == SUNK) {
            System.out.println(this.getName() + " >>>>> Has sunk one of your ship after an attack at \"" + coords + "\" !");
        } else if (status == MISSED) {
            System.out.println(this.getName() + " >>>>> Has missed a shoot at \"" + coords + "\" !");
        } else {
            System.out.println(this.getName() + " >>>>> Game over, you have loose the game !");
        }
    }

    public Coordonnee chooseAttack() {
        Coordonnee coords;
        while (true) {
            int row = (int)(this.getGridSize()*Math.random());
            int column = (int)(this.getGridSize()*Math.random());

            try {
                coords = new Coordonnee(row, column);
            } catch (IllegalArgumentException e) {
				System.out.println("Incorrect input, please try again. (Format : CharInt)");
				continue;
			}

			if((coords.getColumn() > this.getGridSize()) || (coords.getRow() > this.getGridSize())) {
                System.out.println("Incorrect input, please try again. (Out of grid)");
			    continue;
            }

			break;
        }

        return coords;
    }
}
