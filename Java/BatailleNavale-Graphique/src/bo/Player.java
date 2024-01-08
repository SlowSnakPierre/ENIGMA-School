package bo;

import javax.swing.*;
import java.util.Objects;

public abstract class Player {
    public final static int TOUCHED = 1;
    public final static int SUNK = 2;
    public final static int MISSED = 3;
    public final static int GAMEOVER = 4;

    private Player opponent;
    private int GRID_SIZE;
    private String name;

    public Player(int GRID_SIZE, String name) {
        this.name = name;
        this.GRID_SIZE = GRID_SIZE;
    }

    public Player(int GRID_SIZE) {
        this.GRID_SIZE = GRID_SIZE;
        this.name = "Default Player";
    }

    public int getGridSize() {
        return this.GRID_SIZE;
    }

    public String getName() {
        return this.name;
    }

    public void playWith(Player opponent) {
        this.opponent = opponent;
        opponent.opponent = this;
        System.out.println("Connection successful !");

        gameCoroutine(this, opponent);
    }

    public void gameCoroutine(Player attacker, Player defender) {
        System.out.println("############################################################################");
        System.out.println("                    " + attacker + " VS " + defender);
        System.out.println("############################################################################");

        int resAtt = 0;
        int resDef = 0;

        while (resAtt != GAMEOVER || resDef != GAMEOVER) {
            Coordonnee cAtt = attacker.chooseAttack();

            resAtt = defender.receiveAttack(cAtt);

            attacker.returnAttack(cAtt, resAtt);
            defender.returnDefense(cAtt, resAtt);

            if (resAtt == GAMEOVER) {
                break;
            }

            Player x = attacker;
            attacker = defender;
            defender = x;
        }
    }

    protected abstract void returnAttack(Coordonnee coords, int status);
    protected abstract void returnDefense(Coordonnee coords, int status);

    public abstract Coordonnee chooseAttack();
    public abstract int receiveAttack(Coordonnee coords);

    @Override
    public String toString() {
        return !Objects.equals(this.name, "") ? this.name : "Default Player";
    }
}
