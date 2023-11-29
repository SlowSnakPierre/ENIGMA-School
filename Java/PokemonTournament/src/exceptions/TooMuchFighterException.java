package exceptions;

public class TooMuchFighterException extends Exception {
    @Override
    public String getMessage() {
        return "Trop de combattant dans le tournoi.";
    }
}
