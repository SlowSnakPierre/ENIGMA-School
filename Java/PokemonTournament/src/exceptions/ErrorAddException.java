package exceptions;

public class ErrorAddException extends Exception {
    @Override
    public String getMessage() {
        return "Erreur lors de l'ajout du combattant.";
    }
}
