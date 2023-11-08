package bo;

import java.util.Arrays;

public class AttackBoard {

    public final int BOARD_SIZE = 10;

    public final int A_ASCII_VALUE = 65;
    public String[][] board = new String[BOARD_SIZE][BOARD_SIZE];

    public AttackBoard() {
        for (String[] row: board) {
            Arrays.fill(row, "~");
        }
    }

    public void attack(String attackCoordinate, String attackedSymbol) {
        int row = attackCoordinate.charAt(0) - A_ASCII_VALUE;
        int column = Integer.parseInt(attackCoordinate.replaceAll("[^0-9]", "")) - 1;
        board[row][column] = attackedSymbol;
    }

    public void printAttackBoard() {
        System.out.println("  1 2 3 4 5 6 7 8 9 10");
        int asciiValue = A_ASCII_VALUE;
        for (int i = 0; i < BOARD_SIZE; i++) {
            System.out.print((char) asciiValue + " ");
            asciiValue++;
            for (int j = 0; j < BOARD_SIZE; j++) {
                System.out.print(board[i][j] + " ");
                if (j == BOARD_SIZE - 1) {
                    System.out.print("\n");
                }
            }
        }
    }

}