package bo;

import java.util.Scanner;

public class TextualPlayer extends PlayerWithGrid {
    public TextualPlayer(NavalGrid grid, String name) {
        super(grid, name);
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
        boolean incorrect = true;
        Coordonnee attackCoords = null;
        while (incorrect) {
            System.out.println("Where do you want to shoot ? ");
            Scanner sc = new Scanner(System.in);
            String s = sc.next();
            try {
                attackCoords = new Coordonnee(s);
            } catch (IllegalArgumentException e) {
                System.out.println("Incorrect input, please try again. (Format : CharInt)");
                continue;
            }

            if ((attackCoords.getColumn() > this.getGridSize()) || (attackCoords.getRow() > this.getGridSize())) {
                System.out.println("Incorrect input, please try again. (Out of grid)");
                continue;
            }

            incorrect = false;
        }
        return attackCoords;
    }
}
