package bo;

public class Player {
    PlayerBoard playerBoard;
    AttackBoard attackBoard;
    String name;

    Player(String name) {
        this.playerBoard = new PlayerBoard();
        this.attackBoard = new AttackBoard();
        this.name = name;
    }
}