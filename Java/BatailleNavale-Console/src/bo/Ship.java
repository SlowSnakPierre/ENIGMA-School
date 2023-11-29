package bo;

public class Ship {
    String name;
    String indicator;
    int length;

    int startRow;
    int endRow;
    int startColumn;
    int endColumn;
    boolean beenPlaced;
    PlayerBoard playerBoard;

    public final int A_ASCII_VALUE = 65;
    boolean isSunk = false;

    public Ship(String name, String indicator, int length, String firstCoordinate, String secondCoordinate, PlayerBoard playerBoard) {
        this.name = name;
        this.indicator = indicator;
        this.length = length;
        this.startRow = firstCoordinate.charAt(0) - A_ASCII_VALUE;
        this.endRow = secondCoordinate.charAt(0) - A_ASCII_VALUE;
        this.startColumn = Integer.parseInt(firstCoordinate.replaceAll("[^0-9]", "")) - 1;
        this.endColumn = Integer.parseInt(secondCoordinate.replaceAll("[^0-9]", "")) - 1;
        this.playerBoard = playerBoard;
    }

    public void checkIfSunk() {
        int hitCounter = 0;
        if (startRow == endRow) {
            for (int i = startColumn; i <= endColumn; i++) {
                if (playerBoard.board[startRow][i].equals("T")) {
                    hitCounter++;
                }

            }
            if (hitCounter == this.length) {
                isSunk = true;
            }
        }
        else if (startColumn == endColumn) {
            for (int i = startRow; i <= endRow; i++) {
                if (playerBoard.board[i][startColumn].equals("T")) {
                    hitCounter++;
                }
            }
            if (hitCounter == this.length) {
                isSunk = true;
            }
        }
    }

}