package bo;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Objects;

public class PlayerBoard {
    final int BOARD_SIZE = 10;
    public final int A_ASCII_VALUE = 65;
    public ArrayList<Ship> ships;
    public String[][] board = new String[BOARD_SIZE][BOARD_SIZE];

    public HashSet<String> sunkenShips;

    public PlayerBoard() {
        for (String[] row: board) {
            Arrays.fill(row, "~");
        }
        this.ships = new ArrayList<>();
        this.sunkenShips = new HashSet<>();
    }

    public void printPlayerBoard() {
        System.out.println("  1 2 3 4 5 6 7 8 9 10");
        int asciiValue = 65;
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

    public void placeShip(Ship ship, String firstCoordinate, String secondCoordinate) {
        int startRow = firstCoordinate.charAt(0) - A_ASCII_VALUE;
        int endRow = secondCoordinate.charAt(0) - A_ASCII_VALUE;
        int startColumn = Integer.parseInt(firstCoordinate.replaceAll("[^0-9]", "")) - 1;
        int endColumn = Integer.parseInt(secondCoordinate.replaceAll("[^0-9]", "")) - 1;

        if (startRow > endRow) {
            int temp = startRow;
            startRow = endRow;
            endRow = temp;
        }
        if (startColumn > endColumn) {
            int temp = startColumn;
            startColumn = endColumn;
            endColumn = temp;
        }

        if (startRow == endRow) {
            for (int i = startColumn; i <= endColumn; i++) {
                board[startRow][i] = ship.indicator;
            }
        }
        else if (startColumn == endColumn) {
            for (int i = startRow; i <= endRow; i++) {
                board[i][startColumn] = ship.indicator;
            }
        }
    }

    public String checkAttack(String attackCoordinate) {
        int row = attackCoordinate.charAt(0) - A_ASCII_VALUE;
        int column = Integer.parseInt(attackCoordinate.replaceAll("[^0-9]", "")) - 1;
        if (Objects.equals(board[row][column], "C") || Objects.equals(board[row][column], "c") || Objects.equals(board[row][column], "S") || Objects.equals(board[row][column], "D") || Objects.equals(board[row][column], "B")) {
            System.out.println("A ship has been hit!");
            board[row][column] = "T";
            return "T";
        }
        else {
            System.out.println("Attack missed!");
            board[row][column] = "W";
            return "W";
        }
    }

    public boolean CheckGameOver() {
        int sunkCounter = 0;
        for (Ship ship : ships) {
            ship.checkIfSunk();
            if (ship.isSunk) {
                sunkCounter++;
                sunkenShips.add(ship.name);
            }
        }
        return sunkCounter == 5;

    }

}