package bo;

import java.util.Objects;

public abstract class Player {
    public final static int TOUCHED = 1;
    public final static int SUNK = 2;
    public final static int MISSED = 3;
    public final static int GAMEOVER = 4;
    private final int GRID_SIZE;
    private final String name;

    public Player(int GRID_SIZE, String name) {
        this.name = name;
        this.GRID_SIZE = GRID_SIZE;
    }

    public int getGridSize() {
        return this.GRID_SIZE;
    }

    public String getName() {
        return this.name;
    }

    public void playWith(Player opponent) {
        System.out.println("Connection successful !");

        gameCoroutine(this, opponent);
    }

    public void gameCoroutine(Player attacker, Player defender) {
        System.out.println("############################################################################");
        System.out.println("                    " + attacker + " VS " + defender);
        System.out.println("############################################################################");

        int resAtt;

        while (true) {
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
