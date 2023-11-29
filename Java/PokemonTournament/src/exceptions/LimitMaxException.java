package exceptions;

public class LimitMaxException extends Exception {
    @Override
    public String getMessage() {
        return "Le tournoi a atteint son nombre maximum de combattants.";
    }
}
