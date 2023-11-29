package exceptions;

public class ZeroFighterException extends Exception {
    @Override
    public String getMessage() {
        return "Nombre de combattant invalide. Il faut obligatoirement un nombre de combattant suppérieur à 0.";
    }
}
