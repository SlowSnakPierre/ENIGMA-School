package exceptions;

public class NbFighterException extends Exception {
    @Override
    public String getMessage() {
        return "Nombre de combattant invalide. Il faut obligatoirement un nombre de combattant d'une puissance de 2.";
    }
}
